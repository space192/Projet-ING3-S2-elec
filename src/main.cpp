#include "lib.hpp"
#include "ADC.hpp"
arduinoFFT FFT = arduinoFFT();
double vReal[SAMPLES];
double vImag[SAMPLES];
byte sampleTaken = 0;
byte peak;
bool change = false;
long maxpeak;
char buf[5];
Adafruit_SSD1306 display(-1);
double average;



void setup()
{
  cli();
  Serial.begin(9600);
  ADC_disable();
  ADC_freeRunning();
  ADC_AutoStart();
  ActivateIntteruptADC();
  ADC_setADLAR(10);
  ADC_setPrescaler(32);
  ADC_setReference(ADC_VCC);
  setAnalogMux(ADC_A0);
  ADC_enable();
  initializeDisplay(display);
  affichageLED(display);
  display.display();
  pinMode(button,INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(A0, INPUT);
  sei();
  ADC_startConvert();
  
}

ISR(ADC_vect)
{
  if(sampleTaken < SAMPLES)
  {
    vReal[sampleTaken] = ADC_read() - 322.45;
    vImag[sampleTaken] = 0.0;
    sampleTaken++;
    //Serial.println(vReal[sampleTaken]);
  }
  else
  {
    sampleTaken = 0;
    change = true;
  }
}

void loop()
{
    //if(!digitalRead(button))
    //{
      if(change)
      {
        cli();
        /*for (byte i = 0; i < SAMPLES; i++)
        {
          ADC_startConvert();
          while (!ADC_available());
          vReal[i] = ADC_read() - 322.45;
          //vReal[i] = 
          //vReal[i] = analogRead(A0)- 322.45;
          vImag[i] = 0;
        }*/
        FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
        FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
        FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
        
        display.fillRect(0, 12, display.width(), display.height() - 13, BLACK);
        for (byte i = 0; i < (SAMPLES/2)-1; i++) {
          //Serial.println(vReal[i]);
          //Serial.println(",");
          peak = map(vReal[i], 0, 1023, 0, 52);
          //display.fillRect(i * 4 + 1, abs(52 - peak) + 12, 3, peak, WHITE);
          display.fillRect(i*4+1, abs(52 - peak) + 12, 3, peak, WHITE);
        }
        
        average = difference(vReal);
        //Serial.println(average);
        if(average >= 0.90)
        {
          digitalWrite(LED1, !digitalRead(LED1));
          delay(500);
        }
        //Serial.println("\n\n\n");
        change = false;
        sei();
        display.display();
      }
  //}
}