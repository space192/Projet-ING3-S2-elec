#include "lib.hpp"


void affichageLED(Adafruit_SSD1306& display, byte selected) //envoie un chiffre entre 1 et 6 pour changer l'affichage des cartes entre 123 123
{
    display.setTextColor(WHITE);
    display.setTextSize(1,1);
    for(byte j = 1 ; j <= 2; j++)
    {
        for(byte i =j-1 ; i < 3 + j-1 ; i++)
        {
            if(selected == -1)
            {
                display.writeFillRect(i*20+5 + (j-1)*40,1, 15,7, BLACK);
                display.drawRoundRect(i*20+5 + (j-1)*40,1, 15,7,2, WHITE);
                for(int k = 0 ; k < (i+1) - (j-1) ;k++)
                {
                    display.drawFastVLine(i*20+10 + (j-1)*40 + 2-k, 3, 3, WHITE);
                }
            }
            else if(selected == ((i+1) + (j-1)*(j)))
            {
                display.writeFillRect(i*20+5 + (j-1)*40,1, 15,7, WHITE);
                display.drawFastVLine(i*20+10 + (j-1)*40, 3, 3, BLACK);
            }
            else
            {
                display.drawRoundRect(i*20+5 + (j-1)*40,1, 15,7,2, WHITE);
                for(int k = 0 ; k < (i+1) - (j-1) ;k++)
                {
                    display.drawFastVLine(i*20+10 + (j-1)*40 + 2-k, 3, 3, WHITE);
                } 
            }
        }
    }
}

void initializeDisplay(Adafruit_SSD1306& display)
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.fillScreen(BLACK);
  for (byte i = 0; i < (SAMPLES/2); i++) 
  {
      display.drawFastHLine(i*4 , display.height() - 1, 3, WHITE);
  }
}