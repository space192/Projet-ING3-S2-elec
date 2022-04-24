#include <Arduino.h>
#include <Wire.h>
#include <avr/io.h>
#include <arduinoFFT.h>
#include <Adafruit_SSD1306.h>
#define SAMPLES 64
#define FE 30000

#define button 5
#define LED1 12
#define LED2 11
#define LED3 10



void affichageLED(Adafruit_SSD1306& display, int selected=-1);
void initializeDisplay(Adafruit_SSD1306& display);
double difference(double samples[SAMPLES]);