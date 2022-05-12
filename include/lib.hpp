#ifndef LIB_HPP_INCLUDED
#define LIB_HPP_INCLUDED
#include <Arduino.h>
#include <Wire.h>
#include <avr/io.h>
#include <arduinoFFT.h>
#include <Adafruit_SSD1306.h>
#define SAMPLES 64
#define K 3

#define button1 4
#define button2 3
#define button3 2
#define LED1 9
#define LED2 8
#define LED3 7
#define LED4 12
#define LED5 11
#define LED6 10



void affichageLED(Adafruit_SSD1306& display, byte selected);
void initializeDisplay(Adafruit_SSD1306& display);
double difference(double samples[SAMPLES]);
#endif