#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
long first = 0;
char customKey;
const byte ROWS = 4;  //four rows
const byte COLS = 3;  //three columns

#define stepPin 11
#define dirPin 10
int distance = 200*15;

char keys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};

byte rowPins[ROWS] = { 2, 3, 4, 5 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 6, 7, 8 };     //connect to the column pinouts of the keypad

Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  lcd.init();  // initialize the lcd
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print(" THERM0 CYCLER");
  delay(4 * 1000);
  lcd.clear();
  // lcd.clear();
}
// void MOTOR() {
//   // put your main code here, to run repeatedly:
// lcd.clear();
//   // lcd.setCursor(1, 0);
//   // lcd.print(first);
//   // delay(1000);
//   digitalWrite(dirPin, HIGH);

//   for (int x = 0; x < distance; x++) {
//     digitalWrite(stepPin, HIGH);
//     delayMicroseconds(500);
//     digitalWrite(stepPin, LOW);
//     delayMicroseconds(500);
//   }
//   delay(1000);

//   ///
//   digitalWrite(dirPin, LOW);

//   for (int x = 0; x < distance; x++) {
//     digitalWrite(stepPin, HIGH);
//     delayMicroseconds(500);
//     digitalWrite(stepPin, LOW);
//     delayMicroseconds(500);
//   }
//   delay(1000);
// }


void loop() {
  lcd.setCursor(1, 0);
  lcd.print("FEED NO.CYCLE: ");
  customKey = customKeypad.getKey();
  switch (customKey) {
    case '2' ... '9':
      first = first * 10 + (customKey - '0');
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("FEED NO.CYCLE: ");
      lcd.setCursor(9, 1);
      lcd.print(first);
      break;

    case '1':
      while (first) {
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("left cycle is:");
        lcd.setCursor(5, 1);
        lcd.print(first);
        {
          digitalWrite(dirPin, HIGH);

          for (int x = 0; x < distance; x++) {
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(500);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(500);
          }
          delay(1000);

          ///
          digitalWrite(dirPin, LOW);

          for (int x = 0; x < distance; x++) {
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(500);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(500);
          }
          delay(1000);
        }
        first--;
        // lcd.print(first); 
      }
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("PROCESS COMPLETED.. ");
      delay(2000);
      break;
  }
}