// Interface L298N Driver Module with Arduino
#include <Stepper.h>
const int stepsPerRevolution = 1000;//1000 Revolution
Stepper myStepper(stepsPerRevolution,8,9,10,11);
void setup() {
  myStepper.setSpeed(60);//speed control 60rpm
  Serial.begin(9600);

}
void loop() {
  Serial.println("counterclockwise");
  myStepper.step(stepsPerRevolution);
  delay(1);//delay to change the direction 
  
  // Anti clockwise
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(1);

}
