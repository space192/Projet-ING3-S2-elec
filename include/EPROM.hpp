#include <Arduino.h>
#include <EEPROM.h>


int enceinte = 4;
int taille = 4;
int valeurE[10] = {1,2,3,1,1,2,3,3,4,5}; 
int valeurR[10] = {0,0,0,0,0,0,0,0,0,0}; 
int adresse[11] = {17,19,21,23,25,27,29,31,33,35};
int frequence[7] = {1908,1700,1515,1428,1272,1136,1012};
int t1 = 0;
int t2 = 0;
int intervalle = 0;
int valeurS = 1;
