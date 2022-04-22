#include "lib.hpp"
#include "ADC.hpp"

arduinoFFT FFT = arduinoFFT();
double vReal[SAMPLES];
double vImag[SAMPLES];
byte peak;
long maxpeak;
char buf[5];
Adafruit_SSD1306 display(-1);


void setup()
{
  ADC_enable();
  ADC_setADLAR(10);
  ADC_setPrescaler(32);
  ADC_setReference(ADC_VCC);
  setAnalogMux(ADC_A0);
  byte x = 0;
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.fillRect(0, 0, display.width(), 11, WHITE);
  display.setTextColor(BLACK);
 
  x = 16; display.setCursor(x, 2);
  display.print(F("AUDIO"));
  x = 52; display.setCursor(x, 2); 
  display.print(F("SPECTROMETER"));

  for (byte i = 0; i < (SAMPLES/2)-1; i++) {
      //display.drawFastHLine(i * 4 + 1, display.height() - 1, 3, WHITE);
      display.drawFastHLine(i*4+1 , display.height() - 1, 3, WHITE);
    } 
  display.setTextColor(WHITE);   
  display.display();
  // pinMode(led, OUTPUT);
}

void loop()
{

  for (byte i = 0; i < SAMPLES; i++)
  {
    ADC_startConvert();
    while (!ADC_available());
    vReal[i] = ADC_read();
    vImag[i] = 0;
  }
  FFT.DCRemoval();
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
  display.fillRect(0, 12, display.width(), display.height() - 13, BLACK);
  for (byte i = 0; i < (SAMPLES/2) - 1; i++) {
    peak = map(vReal[i], 0, 1024, 0, 52);
    //display.fillRect(i * 4 + 1, abs(52 - peak) + 12, 3, peak, WHITE);
    display.fillRect(i*4+1, abs(52 - peak) + 12, 3, peak, WHITE);
  }
  /*maxpeak= FFT.MajorPeak(vReal, SAMPLES, 5000);
  sprintf(buf,"%04li",maxpeak);
  display.setCursor(72,16);
  display.print(F("Peak:"));
  display.print(buf);*/
  display.display();
}