#include "EPROM.hpp"

int taille = 10;

int valeurR[10] = {0,0,0,0,0,0,0,0,0,0}; 
int adresse[11] = {17,19,21,23,25,27,29,31,33,35};
int frequence[7] = {1908,1700,1515,1428,1272,1136,1012};
int t1 = 0;
int t2 = 0;
int intervalle = 0;
int valeurS = 1;
bool conditionJouer = true;



void Ecrire(byte valeurE, byte index) {
  EEPROM.update(adresse[0], 10);
  
  EEPROM.update(adresse[index+1], valeurE);
  
}

void recuperer()
{
    EEPROM.get(adresse[0], taille);
  for(int i = 0; i<taille; i++)
  {
    EEPROM.get(adresse[i+1], valeurR[i]);
  }
}


void jouer() {
  
  conditionJouer=true;
  while(conditionJouer)
  {
    t2 = millis();
    intervalle = t2 - t1;
    for(int i = 0; i<taille; i++)
    {
      if(( intervalle > 250*i ) && ( intervalle < 250*(i+1) ))
      {
        if(i==taille-1)
        {
          conditionJouer = false;
        }
        valeurS =  valeurR[i];
      }
      
        digitalWrite(5,HIGH);
        delayMicroseconds(frequence[valeurS-1]);
        digitalWrite(5,LOW);
        delayMicroseconds(frequence[valeurS-1]);
      
    }
    
  }
    
}