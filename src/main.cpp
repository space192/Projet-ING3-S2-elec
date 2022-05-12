#include "lib.hpp"
#include "ADC.hpp"
#include "EPROM.hpp"

arduinoFFT FFT = arduinoFFT();
double vReal[SAMPLES];
double vImag[SAMPLES];
byte sampleTaken = 0;
byte peak;
Adafruit_SSD1306 display(-1);
double average;
String temp;
double vRealTemp;
double vRealTemp2;
byte compteur =0;
double dB = 0;
double power;




void setup()
{
  Serial.begin(115200);
  //Ecrire();
  //recuperer();
  //Serial.begin(9600);
  cli();
  ADC_setup();
  initializeDisplay(display);
  //affichageLED(display);
  pinMode(button,INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(A0, INPUT);
  pinMode(5, OUTPUT);
  sei();
  display.display();
  
}

/*ISR(ADC_vect)
{
  if(sampleTaken < SAMPLES)
  {
    vReal[sampleTaken] = ADC_read() - 322.45;
    vImag[sampleTaken] = 0.0;
    vRealTemp = vReal[sampleTaken];

    if(vRealTemp > 363.55)
    {
      //Serial.println(vReal[sampleTaken]);
    }
    
    sampleTaken++;
  }
  else
  {
    sampleTaken = 0;

    //Serial.println("\n\n");
    change = true;
  }
}*/

void loop()
{
    if(!digitalRead(button))
    {
      ADC_disable();
      //jouer();
      ADC_setup();
      ADC_startConvert();
    }
    for(byte i = 0 ; i <SAMPLES ;i++)
    {
      ADC_startConvert();
      while(!ADC_available());
      vReal[i] = ADC_read() - 322.45;
      vImag[i] = 0;
    }
        compteur = 0;
        power =0;
        dB=0;
        for(int i=0 ; i < SAMPLES ;i++)
        {
          power += pow(vReal[i],2);
          if(vReal[i] > 350.0)
          {
            compteur += 1;
            vRealTemp2 += vReal[i];
            
            
          }
          
        }
        vRealTemp2 = vRealTemp2/compteur;
        dB = 800*log(vRealTemp2) - 4700;
        //Serial.println(vRealTemp2);
        // Serial.print("A");
         Serial.println(dB);
        //Serial.println(power);
        if(dB > 150)
        {
          digitalWrite(LED1,!digitalRead(LED1));
          digitalWrite(LED2,!digitalRead(LED2));
          digitalWrite(LED3,!digitalRead(LED3));
        }
        FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
        FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
        FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
        
        //display.fillRect(0, 12, display.width(), display.height() - 13, BLACK);
        for (byte i = 0; i < (SAMPLES/2); i++) {
          //Serial.println(vReal[i]);
          peak = map(vReal[i], 0, 600, 0, 52);
          //display.fillRect(i*4, abs(52 - peak) + 12, 3, peak, WHITE);
          // if(i<10)
          // {
          //   Serial.print('9');
          //   Serial.print(i);
          //   Serial.println(peak);
          // }
          // else{
          //   Serial.print(i);
          //   Serial.println(peak);
          // }
        }
        //Serial.println("\n\n\n");
        /*average = difference(vReal);
        if(average >= 0.90)
        {
          digitalWrite(LED1, !digitalRead(LED1));
          delay(500);
        }*/
        display.display();
  //}
}