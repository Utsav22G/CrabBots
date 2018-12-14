
#include <Wire.h>
#include <Adafruit_MotorShield.h>
//#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motorL = AFMS.getMotor(1);
Adafruit_DCMotor *motorR = AFMS.getMotor(2);

int initial = 1;

int red = A1;
int green = A2;
int blue = A3;

int init_red;
int init_green;
int init_blue;

int curr_red;
int curr_green;
int curr_blue;

int diff_red;
int diff_green;
int diff_blue;

int value = 0;

int motorspeed = 30;

unsigned long pTime = 0;
unsigned long cTime;

int StateL = FORWARD;
int StateR = BACKWARD;

void setup() {

  long baudRate = 9600;
  Serial.begin(baudRate);
    AFMS.begin();

  pinMode(red, INPUT);
  pinMode(green, INPUT);
  pinMode(blue, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(initial == 1) {
    init_red = analogRead(red);
    init_green = analogRead(green);
    init_blue = analogRead(blue);

    delay(200);

    initial = 0;
  }
    
  motorL->setSpeed(motorspeed);
  motorR->setSpeed(motorspeed);
  
  curr_red = analogRead(red);
  curr_green = analogRead(green);
  curr_blue = analogRead(blue);

  diff_red = curr_red - init_red;
  diff_green = curr_green - init_green;
  diff_blue = curr_blue - init_blue;

  if(abs(diff_red) > abs(3*diff_green) && abs(diff_red) > abs(3*diff_blue)) {
    value = 1;
  }
  else if(abs(diff_green) > abs(5*diff_red) && abs(diff_green) > abs(5*diff_blue)) {
    value = 2;
  }
  else if(abs(diff_blue) > abs(5*diff_red) && abs(diff_blue) > abs(5*diff_green)) {
    value = 3;
  }
  else {
    value = 0;
  }
  /*
  Serial.println(diff_red);
  Serial.println("---");
  Serial.println(diff_green);
  Serial.println("---");
  Serial.println(diff_blue);
  Serial.println("---");
  Serial.println(value);
  Serial.println(" ");
  delay(250);*/
  

  if(value == 1 && abs(curr_red) < 500) {
    motorspeed = 40;
    motorL->run(FORWARD);
    motorR->run(FORWARD); 
  }
  else if(value ==1 && abs(curr_red) >= 500) {
    motorL->run(RELEASE);
    motorR->run(RELEASE);
  }
  else {
    cTime = millis();
    motorspeed = 40;
    if((cTime - pTime) >= 1000) { //if time difference is greater than or equal to 200ms, turn the other direction
      if(StateL == FORWARD) {
        StateL = BACKWARD;
      } else {
        StateL = FORWARD;
      }
      
      if(StateR == FORWARD) {
        StateR = BACKWARD;
      } else {
        StateR = FORWARD;
      }
      pTime = cTime;
    }

    motorL->run(StateL);
    motorR->run(StateR);
    delay(20);
  }
}
