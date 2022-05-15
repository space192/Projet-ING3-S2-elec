#include "lib.hpp"
#include "ADC.hpp"
#include "EPROM.hpp"
#include "Gaussian.hpp"

arduinoFFT FFT = arduinoFFT();
double vReal[SAMPLES];
double vImag[SAMPLES];
byte sampleTaken = 0;
byte peak;
bool conditionLed = true;
//Adafruit_SSD1306 display(-1);
double average;
String temp;
double vRealTemp;
double vRealTemp2;
byte compteur = 0;
byte dB = 30;
Gaussian tabR[K];
bool clap = false;
byte dB1 = 30;
byte dB2 = 30;
byte oldNote = 0;
byte newNote = 0;
bool conditionEnre = false;
byte sequence[10];
byte noteEcrite = 0;
/*double U[K] = {0.0, 0.0, 0.0};
double S[K] = {0.0, 0.0, 0.0};
double W[K] = {0.0, 0.0, 0.0};
int counterU = 0;*/



void setup()
{

  Serial.begin(115200);
  Ecrire();
  recuperer();
  cli();
  ADC_setup();
  //initializeDisplay(display);
  //affichageLED(display, -1);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(5, OUTPUT);
  sei();
  //display.display();
}

void loop()
{
  if((!digitalRead(button2)))
  {
    conditionLed = !conditionLed;
    delay(500);
  }
  if (!digitalRead(button1))
  {
    jouer();
  }
  compteur = 0;
  vRealTemp2 = 0;
  for (byte i = 0; i < SAMPLES; i++)
  {
    ADC_startConvert();
    while (!ADC_available());
    vReal[i] = ADC_read() - 322.45;
    vImag[i] = 0;
    if (vReal[i] > 355)
    {
      compteur += 1;
      vRealTemp2 += vReal[i];
    }
  }
  dB2 = dB1;
  dB1 = dB;
  vRealTemp2 = vRealTemp2 / (double)compteur;
  dB = (170.0 * log(vRealTemp2) - 973.0);
  Serial.print("A");
  Serial.println(dB);
  if(((dB1 - dB)+(dB1 - dB2)> 15  ) && (conditionLed == true))
  {
    clap = !clap;
    digitalWrite(LED1, clap);
    digitalWrite(LED2, clap);
    digitalWrite(LED3, clap);

    if (clap)
    {
      //affichageLED(display, 1);
      //affichageLED(display, 2);
      //affichageLED(display, 3);
    }
    else
    {
      //affichageLED(display, 7);
    }
  }

  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
  //display.fillRect(0, 12, display.width(), display.height() - 13, BLACK);
  for (byte i = 2; i < (SAMPLES / 2); i++)
  {
    //Serial.println(vReal[i]);
    peak = map(vReal[i], 0, 600, 0, 52);
    //display.fillRect(i * 4, abs(52 - peak) + 12, 3, peak, WHITE);
    if(i<10)
    {
      Serial.print('9');
      Serial.print(i);
      Serial.println(peak);
    }
    else{
      Serial.print(i);
      Serial.println(peak);
    }
  }
  if (!digitalRead(button3))
  {
    GMM_ALGORITHM(vReal, tabR);
    for (byte i = 0; i < K; i++)
    {
      // U[i] += tabR[i].getu();
      // S[i] += tabR[i].getsigma();
      // W[i] += tabR[i].getWeight();
      Serial.println("u" + String(tabR[i].getu()));
      Serial.println("s" + String(tabR[i].getsigma()));
      Serial.println("w" + String(tabR[i].getWeight()));
    }
    //counterU++;
    switch (KullbackLeiblerDivergence(tabR))
    {
    case 1:
      digitalWrite(LED1, !digitalRead(LED1));
      break;
    case 2:
      digitalWrite(LED2, !digitalRead(LED2));
      break;
    case 3:
      digitalWrite(LED3, !digitalRead(LED3));
      break;
    }
  }
  /*else
  {
    if (counterU != 0)
    {
      for (byte i = 0; i < K; i++)
      {
        Serial.println(U[i] / (double)counterU);
        Serial.println(S[i] / (double)counterU);
        Serial.println(W[i] / (double)counterU);
      }
    }
    counterU = 0;
    for (byte i = 0; i < K; i++)
    {
      U[i] = 0.0;
      S[i] = 0.0;
      W[i] = 0.0;
    }
  }*/
      //display.drawRect(0, display.height() - (dB - 30) / 4.4, 8, (dB - 30) / 4.4, WHITE);

  /*if (!digitalRead(button1))
  {
    conditionEnre = true;
  }

  if(conditionEnre)
  {
    if(newNote != oldNote)
    {
      sequence[noteEcrite] = newNote;
      oldNote = newNote;
      noteEcrite ++;
      if(noteEcrite == 10)
      {

          conditionEnre = false;
          noteEcrite = 0;
      }
    }


  }*/
  //display.display();
}
