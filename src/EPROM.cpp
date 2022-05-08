#include "EPROM.hpp"


void Ecrire() {

  
  EEPROM.put(adresse[0], 10);
  for(int i = 0; i<10; i++)
  {
    EEPROM.put(adresse[i+1], valeurE[i]);
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
  t2 = millis();
  intervalle = t2 - t1;

  for(int i = 1; i<taille+1; i++)
  {
    if(( intervalle > 250*i ) && ( intervalle < 250*(i+1) ))
    {
      valeurS =  valeurR[i-1];
    }
    
      digitalWrite(enceinte,HIGH);
      delayMicroseconds(frequence[valeurS-1]);
      digitalWrite(enceinte,LOW);
      delayMicroseconds(frequence[valeurS-1]);
    
  }
  if(intervalle > 250*(taille+1))
  {
    t1= millis();
  }
}