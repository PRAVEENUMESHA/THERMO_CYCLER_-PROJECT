#include <Key.h>
#include <Keypad.h>
#include <Keypad_I2C.h>
#include <LiquidCrystal_I2C.h>
#define I2CADDR 0x21  // Set the Address of the PCF8574
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int stepPin = 5;
const int dirPin = 2;
const int enPin = 8;
int speed = 4000;
const byte ROWS = 4;  // Set the number of RowsA
const byte COLS = 4;  // Set the number of Columns
long D_well = 0;
long NO_cycle = 0;
long first = 0;
long Drain_time = 0;
// bool Approve = 0;
char key;

// Set the Key at Use (4x4)
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

// reset the all code
void (*resetFunc)(void) = 0;

// define active Pin (4x4)
byte rowPins[ROWS] = { 7, 6, 5, 4 };  // Connect to Keyboard Row Pin

byte colPins[COLS] = { 3, 2, 1, 0 };  // Connect to Pin column of keypad.
Keypad_I2C keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR);
void setup() {
  Wire.begin();                    // Call the connection Wire
  keypad.begin(makeKeymap(keys));  // Call the connection

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);

  Serial.begin(9600);
  lcd.begin();
  lcd.setCursor(1, 0);
  lcd.print("THERMO CYCLER");
  delay(2000);
  // lcd.clear();
}
void loop() {
  char NO_CYCLE[] = "CYCLE:";
  NO_cycle = get_key(NO_CYCLE, 7);
  first = 0;

  char D_WELL[] = "DIP TIME:";
  D_well = get_key(D_WELL, 10);
  first = 0;

  char DRAIN_TIME[] = "DRAIN TIME:";
  Drain_time = get_key(DRAIN_TIME, 12);
  first = 0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CYCLES No:");
  lcd.setCursor(10, 0);
  lcd.print(NO_cycle);

  lcd.setCursor(0, 1);
  lcd.print("DIP TIME :");
  lcd.setCursor(10, 1);
  lcd.print(D_well);

  delay(3000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CYCLES No:");
  lcd.setCursor(10, 0);
  lcd.print(NO_cycle);

  lcd.setCursor(0, 1);
  lcd.print("DRAIN TIME:");
  lcd.setCursor(11, 1);
  lcd.print(Drain_time);

  delay(3000);

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("A : TO NEXT");
  lcd.setCursor(1, 1);
  lcd.print("B : TO RESET");

  bool Approve = Approve_next();
  if (Approve == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("NO OF CYCLE LEFT");
    lcd.setCursor(4, 1);
    lcd.print(NO_cycle);
    while (NO_cycle != 0) {

      digitalWrite(dirPin, LOW);
      for (int x = 0; x < 500; x++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(speed);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(speed);
      }
      delay(1000*D_well);
      digitalWrite(dirPin, HIGH);
      for (int x = 0; x < 300; x++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(speed);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(speed);
      }
      delay(1000*Drain_time);
      digitalWrite(dirPin, HIGH);
      for (int x = 0; x < 200; x++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(speed);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(speed);
      }

      digitalWrite(dirPin, HIGH);
      for (int x = 0; x < 500; x++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(speed);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(speed);
      }
      delay(1000*D_well);
      digitalWrite(dirPin, LOW);
      for (int x = 0; x < 300; x++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(speed);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(speed);
      }
      delay(1000*Drain_time);
      digitalWrite(dirPin, LOW);
      for (int x = 0; x < 200; x++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(speed);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(speed);
      }

      NO_cycle--;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("NO OF CYCLE LEFT");
      lcd.setCursor(4, 1);
      lcd.print(NO_cycle);
    }
    
    // start from starting
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CYCLES COMPLETED");
    delay(2000);
    resetFunc();
  }
}

// GET KEY PRESSED
long get_key(char mystring[], int value) {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("THERMO CYCLER");
  lcd.setCursor(1, 1);
  lcd.print(mystring);
  bool ok = 1;
  while (ok == 1) {
    char key = keypad.getKey();  // Create a variable named key of type char to hold the characters pressed


    switch (key) {
      case '0' ... '9':
        first = first * 10 + (key - '0');
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("THERMO CYCLER");
        lcd.setCursor(1, 1);
        lcd.print(mystring);
        lcd.setCursor(value, 1);
        lcd.print(first);
        Serial.println(first);
        break;


      case '*':
        first = first / 10;
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("THERMO CYCLER");
        lcd.setCursor(1, 1);
        lcd.print(mystring);
        lcd.setCursor(value, 1);
        lcd.print(first);
        break;
      case '#':
        ok = 0;
        return first;
        break;
    }
  }
}

// ask for start for cycle
bool Approve_next() {
  while (1) {
    char key = keypad.getKey();
    switch (key) {
      case 'A':
        return 1;
        break;
      case 'B':
        resetFunc();
        break;
    }
  }
}
