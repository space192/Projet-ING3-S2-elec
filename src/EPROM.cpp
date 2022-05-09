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



void Ecrire() {
  int valeurE[10] = {1,2,3,1,1,2,3,3,4,5};
  EEPROM.update(adresse[0], 10);
  for(int i = 0; i<10; i++)
  {
    EEPROM.update(adresse[i+1], valeurE[i]);
  }
  
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
    for(int i = 1; i<taille+1; i++)
    {
      if(( intervalle > 250*i ) && ( intervalle < 250*(i+1) ))
      {
        if(i==taille)
        {
          conditionJouer = false;
        }
        valeurS =  valeurR[i-1];
      }
      
        digitalWrite(5,HIGH);
        delayMicroseconds(frequence[valeurS-1]);
        digitalWrite(5,LOW);
        delayMicroseconds(frequence[valeurS-1]);
      
    }
    if(intervalle > 250*(taille+1))
    {
      t1= millis();
    }
  }
    
}