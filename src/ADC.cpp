#include "ADC.hpp"

void ADC_startConvert()
{
  cli();
  ADCSRA |= (1 << ADSC);
  sei();
}

unsigned int ADC_read()
{
  return ADC;
}

uint8_t ADC_read8(void)
{
  return ADCH;
}

boolean ADC_available()
{
  if (ADCSRA & (1 << ADSC))
  {
    return false;
  }
  else
  {
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