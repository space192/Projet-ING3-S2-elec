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
                display.writeFillRect(i*20+5 + (j-1)*40,1, 15,10, WHITE);
                display.setTextColor(BLACK);
                display.setCursor(i*20+10 + (j-1)*40,2);
                display.print(String((i+1) - (j-1)));
                display.setTextColor(WHITE);
            }
            else
            {
                display.drawRoundRect(i*20+5 + (j-1)*40,1, 15,10,2, WHITE);
                display.setCursor(i*20+10 + (j-1)*40,2);
                display.print(String((i+1) - (j-1)));
            }
        }
    }
}

void initializeDisplay(Adafruit_SSD1306& display)
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.fillScreen(BLACK);
  for (byte i = 0; i < (SAMPLES/2)-1; i++) 
  {
      display.drawFastHLine(i*4+1 , display.height() - 1, 3, WHITE);
  }
}