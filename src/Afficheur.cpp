#include "lib.hpp"


void affichageLED(Adafruit_SSD1306& display, int selected=-1) //envoie un chiffre entre 1 et 6 pour changer l'affichage des cartes entre 123 123
{
    display.setTextColor(WHITE);
    display.setTextSize(1,1);
    for(byte j = 1 ; j <= 2; j++)
    {
        for(byte i =j-1 ; i < 3 + j-1 ; i++)
        {
            if(selected == ((i+1) + (j-1)*(j)))
            {
                display.writeFillRect(i*20+5 + (j-1)*40,1, 15,7, WHITE);
                //display.setTextColor(BLACK);
                //display.setCursor(i*20+10 + (j-1)*40,2);
                //display.print(String((i+1) - (j-1)));
                //display.setTextColor(WHITE);
                display.drawFastVLine(i*20+10 + (j-1)*40, 3, 3, BLACK);
            }
            else
            {
                display.drawRoundRect(i*20+5 + (j-1)*40,1, 15,7,2, WHITE);
                //display.setCursor(i*20+10 + (j-1)*40,2);
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
      display.drawFastHLine(i*4 , display.height() - 5, 3, WHITE);
  }
}