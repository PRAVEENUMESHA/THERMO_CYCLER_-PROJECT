#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3,0);//START IS SPACE AND 2ND ZERO IS COLOUM
  lcd.print("HELLO");
 lcd.setCursor(3,1);
  lcd.print("PRAVEEN");
}

void loop()
{
  
}