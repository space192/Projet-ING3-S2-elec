#include <Arduino.h>

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

void ADC_startConvert();
unsigned int ADC_read();
uint8_t ADC_read8(void);
boolean ADC_available();
unsigned int ADC_readWhenAvailable();
uint8_t ADC_read8WhenAvailable(void);
void ADC_enable();
void ADC_disable();
void setAnalogMux(ADC_modes mux);
void ADC_setPrescaler(byte prescl);
void ADC_setReference(ADC_modes ref);
void ADC_setADLAR(int nbBit);
void ADC_freeRunning();
void ADC_AutoStart();
void ActivateIntteruptADC();
void DeactivateIntteruptADC();