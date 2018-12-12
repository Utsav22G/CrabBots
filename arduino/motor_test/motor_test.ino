// Basic demo for accelerometer readings from Adafruit LIS3DH

#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

#define BPWM 10
#define APWM 9
#define BDIR 5
#define ADIR 4
#define ISSUE 12

bool crash = true;

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

void setup(void) {
  pinMode(8, OUTPUT);
  pinMode(ADIR, OUTPUT);
  pinMode(BDIR, OUTPUT);
  pinMode(APWM, OUTPUT);
  pinMode(BPWM, OUTPUT);

  pinMode(ISSUE, INPUT);

  digitalWrite(BPWM, HIGH);
  digitalWrite(APWM, HIGH);
  digitalWrite(ADIR, HIGH);
  digitalWrite(BDIR, LOW); //drives straight like this

  digitalWrite(8,HIGH);
}

void loop() {
  straight();
  delay(200);
  off();
  delay(400);
  on();
  turnL();
  delay(100);
  off();
  delay(400);
  on();
  turnR();
  delay(100);
  off();
  delay(400);
  on();
  back();
  delay(100);
  off();
  delay(400);
  
}

void turnL(){
  digitalWrite(ADIR, LOW);
  digitalWrite(BDIR, HIGH);
}
void turnR(){
  digitalWrite(ADIR, HIGH);
  digitalWrite(BDIR, HIGH);
}
void straight(){
  digitalWrite(ADIR, HIGH);
  digitalWrite(BDIR, LOW);
}
void back(){
  digitalWrite(ADIR, LOW);
  digitalWrite(BDIR, HIGH);
}
void off(){
  digitalWrite(APWM, LOW);
  digitalWrite(BPWM, LOW);
}
void on(){
  digitalWrite(APWM, HIGH);
  digitalWrite(BPWM, HIGH);
}
