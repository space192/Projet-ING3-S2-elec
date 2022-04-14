#include <Arduino.h>
#include <Wire.h>
#include <avr/io.h>
#include <arduinoFFT.h>
#include <Adafruit_SSD1306.h>
#define SAMPLES 64
enum ADC_modes
{
  ADC_A0,
  ADC_A1,
  ADC_A2,
  ADC_A3,
  ADC_A4,
  ADC_A5,
  ADC_A6,
  ADC_A7,
  ADC_SENSOR,
  ADC_1V1,
  ADC_GND,
  ADC_AREF,
  ADC_VCC,
};

arduinoFFT FFT = arduinoFFT();
double vReal[SAMPLES];
double vImag[SAMPLES];
byte peak;
long maxpeak;
char buf[5];
Adafruit_SSD1306 display(-1);

void ADC_startConvert()
{
  cli();
  ADCSRA |= (1 << ADSC);
  sei();
}

unsigned int ADC_read()
{
  // Serial.println(ADCH, BIN);
  // Serial.println(ADCL, BIN);
  return ADC;
}

uint8_t ADC_read8(void)
{
  return ADCH;
}

boolean ADC_available()
{
  if (ADCSRA & (1 << ADSC))
  { // if flag set - convert in process
    return false;
  }
  else
  { // convert complete
    return true;
  }
}

unsigned int ADC_readWhenAvailable()
{
  while (ADCSRA & (1 << ADSC))
    ;
  return ADC;
}

uint8_t ADC_read8WhenAvailable(void)
{
  while (ADCSRA & (1 << ADSC))
    ;
  return ADCH;
}

void ADC_enable()
{
  cli();
  ADCSRA |= (1 << ADEN);
  sei();
}

void ADC_disable()
{
  cli();
  ADCSRA &= (0 << ADEN);
  sei();
}

void setAnalogMux(ADC_modes mux)
{
  cli();
  switch (mux)
  {
  case ADC_A0:
    ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0));
    break;
  case ADC_A1:
    ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1));
    ADMUX |= (1 << MUX0);
    break;
  case ADC_A2:
    ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX0));
    ADMUX |= (1 << MUX1);
    break;
  case ADC_A3:
    ADMUX &= ~((1 << MUX3) | (1 << MUX2));
    ADMUX |= ((1 << MUX1) | (1 << MUX0));
    break;
  case ADC_A4:
    ADMUX &= ~((1 << MUX3) | (1 << MUX1) | (1 << MUX0));
    ADMUX |= (1 << MUX2);
    break;
  case ADC_A5:
    ADMUX &= ~((1 << MUX3) | (1 << MUX1));
    ADMUX |= ((1 << MUX2) | (1 << MUX0));
    break;
  case ADC_A6:
    ADMUX &= ~((1 << MUX3) | (1 << MUX0));
    ADMUX |= ((1 << MUX2) | (1 << MUX1));
    break;
  case ADC_A7:
    ADMUX &= ~((1 << MUX3));
    ADMUX |= ((1 << MUX2) | (1 << MUX1) | (1 << MUX0));
    break;
  case ADC_SENSOR:
    ADMUX &= ~((1 << MUX2) | (1 << MUX1) | (1 << MUX0));
    ADMUX |= (1 << MUX3);
    break;
  case ADC_GND:
    ADMUX |= ((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0));
    break;
  case ADC_1V1:
    ADMUX &= ~((1 << MUX0));
    ADMUX |= ((1 << MUX3) | (1 << MUX2) | (1 << MUX1));
    break;
  }
  sei();
}

void ADC_setPrescaler(byte prescl)
{
  cli();
  switch (prescl)
  {
  case 2:
    ADCSRA &= ~((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));
    break;
  case 4:
    ADCSRA &= ~((1 << ADPS2) | (1 << ADPS0));
    ADCSRA |= (1 << ADPS1);
    break;
  case 8:
    ADCSRA &= ~((1 << ADPS2));
    ADCSRA |= ((1 << ADPS1) | (1 << ADPS0));
    break;
  case 16:
    ADCSRA &= ~((1 << ADPS1) | (1 << ADPS0));
    ADCSRA |= (1 << ADPS2);
    break;
  case 32:
    ADCSRA &= ~((1 << ADPS1));
    ADCSRA |= ((1 << ADPS2) | (1 << ADPS0));
    break;
  case 64:
    ADCSRA &= ~((1 << ADPS0));
    ADCSRA |= ((1 << ADPS2) | (1 << ADPS1));
    break;
  case 128:
    ADCSRA |= ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));
    break;
  }
  sei();
}

void ADC_setReference(ADC_modes ref)
{
  cli();
  switch(ref)
  {
  case ADC_1V1:
    ADMUX |= ((1 << REFS1) | (1 << REFS0));
    break;
  case ADC_AREF:
    ADMUX &= ((0 << REFS1) | (0 << REFS0));
    break;
  case ADC_VCC:
    ADMUX &= (0 << REFS1);
    ADMUX |= (1 << REFS0);
    break;
  }
  sei();
}
void ADC_setADLAR(int nbBit)
{
  cli();
  switch (nbBit)
  {
  case 8:
    ADMUX |= (1 << ADLAR);
    break;
  case 10:
    ADMUX &= (0 << ADLAR);
    break;
  }
  sei();
}
void setup()
{
  ADC_enable();
  ADC_setADLAR(10);
  ADC_setPrescaler(32);
  ADC_setReference(ADC_1V1);
  setAnalogMux(ADC_A0);
  byte x = 0;
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();   
  display.fillRect(0, 0, display.width() - 2, 11, WHITE);
  display.setTextColor(BLACK);
 
  x = 16; display.setCursor(x, 2);
  display.print(F("AUDIO"));
  x = 52; display.setCursor(x, 2); 
  display.print(F("SPECTROMETER"));

  for (byte i = 0; i < SAMPLES / 2 - 1; i++) {
      display.drawFastHLine(i * 4 + 1, display.height() - 1, 3, WHITE);
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
  display.fillRect(0, 12, display.width() - 2, display.height() - 13, BLACK);
  for (byte i = 0; i < SAMPLES / 2 - 1; i++) {        
    peak = map(vReal[i+2], 0, 1024, 0, 52);    
    display.fillRect(i * 4 + 1, abs(52 - peak) + 12, 3, peak, WHITE);
  }  
  maxpeak= FFT.MajorPeak(vReal, SAMPLES, 5000);  
   
  sprintf(buf,"%04li",maxpeak);  
  display.setCursor(72,16);
  display.print(F("Peak:"));
  display.print(buf);  
  display.display();
}