#include "lib.hpp"
#include "ADC.hpp"
arduinoFFT FFT = arduinoFFT();
double vReal[SAMPLES];
double vImag[SAMPLES];
byte sampleTaken = 0;
byte peak;
bool change = false;
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
  ADC_setPrescaler(64);
  ADC_setReference(ADC_VCC);
  setAnalogMux(ADC_A0);
  ADC_enable();
  initializeDisplay(display);
  affichageLED(display);
  pinMode(button,INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(A0, INPUT);
  sei();
  display.display();
  ADC_startConvert();
}

ISR(ADC_vect)
{
  if(sampleTaken < SAMPLES)
  {
    vReal[sampleTaken] = ADC_read() - 322.45;
    vImag[sampleTaken] = 0.0;
    sampleTaken++;
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
        FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
        FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
        FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
        
        display.fillRect(0, 12, display.width(), display.height() - 13, BLACK);
        for (byte i = 0; i < (SAMPLES/2); i++) {
          //Serial.println(vReal[i]);
          peak = map(vReal[i], 0, 500, 0, 52);
          display.fillRect(i*4, abs(52 - peak) + 12, 3, peak, WHITE);
        }
        //Serial.println("\n\n\n");
        average = difference(vReal);
        if(average >= 0.90)
        {
          digitalWrite(LED1, !digitalRead(LED1));
          delay(500);
        }
        change = false;
        sei();
        display.display();
      }
  //}
}