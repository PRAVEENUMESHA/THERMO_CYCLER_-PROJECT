#include <Stepper.h>
#include <ezButton.h>

// Define the number of steps per revolution
const int stepsPerRevolution = 1000;


// Define the pins connected to the L298N driver
const int in1Pin = 8;
const int in2Pin = 9;
const int in3Pin = 10;
const int in4Pin = 11;

// Define the pins connected to the limit switches
ezButton limitSwitch1Pin(7);  // create ezButton object that attach to pin 7;
ezButton limitSwitch2Pin(6);
// const int limitSwitch1Pin = 2;
// const int limitSwitch2Pin = 3;

// Define the delay between steps
// const int stepDelay = 10;

// Define the Stepper object
Stepper stepper(stepsPerRevolution, in1Pin, in2Pin, in3Pin, in4Pin);

void setup() {
  // Set the pins as inputs for the limit switches
  limitSwitch1Pin.setDebounceTime(100);  // set debounce time to 50 milliseconds
  limitSwitch2Pin.setDebounceTime(100);
  Serial.begin(9600);

  // Set the motor speed and direction
  stepper.setSpeed(20);
}

void loop() {
  limitSwitch1Pin.loop();
  int LEFT = limitSwitch1Pin.getState();
  while (LEFT == LOW) {
    stepper.step(-1);
    limitSwitch2Pin.loop();
    bool state = limitSwitch2Pin.getState();
    if (state == LOW )
     { stepper.step(0); delay(2000);late(1); return; }
  }
  limitSwitch2Pin.loop();
  int RIGTH = limitSwitch2Pin.getState();
  while (RIGTH == LOW) {
    stepper.step(1);
    limitSwitch1Pin.loop();
    bool state = limitSwitch1Pin.getState();
    if (state == LOW)
     { stepper.step(0); delay(2000);late(-1); return; }
  }
  // Check if either of the limit switches are pressed
}
void late(int value)
{
  int i =1000*2;
  while(i!=0)
  {
    stepper.step(value); 
    i--;
    Serial.println(i);
  }
  delay(2000);
}