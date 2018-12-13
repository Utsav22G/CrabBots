#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include "WS2812_Definitions.h"

// -----------------------
// DEFINE PINS
// -----------------------
#define RED A2 // input for red photodiode
#define BLUE A3 // input for blue photodiode

#define BPWM 10
#define APWM 9
#define BDIR 5
#define ADIR 4

#define MUX0 2
#define MUX1 3

#define LED_COUNT 20
#define LED_INPUT 7


// ---------------------
// DEFINE VARIABLES TO 
// READ SENSORS
// ---------------------

// front = 0, right = 1, left = 2, back = 3 
int init_red_front; // ambient reference value
int init_red_right;
int init_red_left;
int init_red_back;
int init_blue_front;
int init_blue_right;
int init_blue_left;
int init_blue_back;

int curr_red_front; // current value 
int curr_red_right;
int curr_red_left;
int curr_red_back;
int curr_blue_front;
int curr_blue_right;
int curr_blue_left;
int curr_blue_back;

int diff_red_front; // difference between ambient and current value
int diff_red_right;
int diff_red_left;
int diff_red_back;
int diff_blue_front;
int diff_blue_right;
int diff_blue_left;
int diff_blue_back;

int left2red;
int right2red;
int left2blue;
int right2blue;

int left3red;
int right3red;
int left3blue;
int right3blue;

int mux_delay = 5;
int motor_delay = 5;

unsigned long prevTime = 0;
unsigned long currTime;
int programCounter = 0;

bool bump = false;

// ---------------------
// DEFINE VARIABLES TO 
// SEND MOTOR COMMANDS
// ---------------------
float left1; // left motor commands to be summed 
float left2;
float left3;
float left4;

float right1; // right motor commands to be summed
float right2;
float right3;
float right4;

float left_total = 0;
float right_total = 0;

float sens = 2;
float scale = 1;

// ---------------------
// DEFINE VARIABLES FOR
// LED STRIP
// ---------------------

int brightness = 64;
int R = 20;
int G = 0;
int B = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_INPUT, NEO_RGB + NEO_KHZ800);

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

void setup() {
  delay(5000);
  Serial.begin(9600);
  
  pinMode(RED,INPUT);
  pinMode(BLUE,INPUT);

  pinMode(APWM,OUTPUT);
  pinMode(ADIR,OUTPUT);

  pinMode(BPWM,OUTPUT);
  pinMode(BDIR,OUTPUT);
 
  pinMode(MUX0, OUTPUT);
  pinMode(MUX1, OUTPUT);

  pinMode(LED_INPUT, OUTPUT);

  digitalWrite(MUX0, HIGH); // set mux select to 0
  digitalWrite(MUX1, HIGH);
  delay(150);
  init_red_front = analogRead(RED); // take initial front values to calibrate
  init_blue_front = analogRead(BLUE);

  digitalWrite(MUX0, HIGH); // set mux select to 1
  digitalWrite(MUX1, LOW);
  delay(150);
  init_red_right = analogRead(RED); // take initial right values to calibrate
  init_blue_right = analogRead(BLUE);

  digitalWrite(MUX0, LOW); // set mux select to 2
  digitalWrite(MUX1, HIGH);
  delay(150);
  init_red_left = analogRead(RED); // take initial left values to calibrate
  init_blue_left = analogRead(BLUE);

  digitalWrite(MUX0, LOW); // set mux select to 3
  digitalWrite(MUX1, LOW);
  delay(150);
  init_red_back = analogRead(RED); // take initial back values to calibrate
  init_blue_back = analogRead(BLUE);

  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    while (1){
      digitalWrite(8,HIGH);
      delay(250);
      digitalWrite(8,LOW);
      delay(250);
    }
  }
  lis.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!

  strip.begin(); 
  colorWipe(strip.Color(0, 0, 0)); // Off   
  strip.show(); 
}

void loop() {
  
  currTime = millis();
  
  //ReadPhotodiodes();
  lis.read();      // get X Y and Z data at once
  sensors_event_t event; 
  lis.getEvent(&event);
  
  if(abs(event.acceleration.z) > 20) {
    if (bump){
      bump = false;
    }
    else{
      bump = true;
    }
  }

  if(bump) {
    colorWipe(strip.Color(0, 0, 0)); // Off
    analogWrite(APWM,0);
    analogWrite(BPWM,0);
    
  } else {
    colorWipe(strip.Color(0, 255, 0)); // Red
    ReadPhotodiodes();
    Move();

  }

  //Move();
}


int ReadPhotodiodes() {
  // ---------------------------
//  find current values of red
//  and blue by subtracting from
//  ambient value
//
//  take reading from front
//  r -> +L +R
//  b -> 0
//  scale values based on brightness 
// ----------------------------
   
  digitalWrite(MUX0, HIGH); // set mux select to 0
  digitalWrite(MUX1, HIGH);
  delay(mux_delay);
  //curr_red_front = analogRead(RED);
  curr_blue_front = analogRead(BLUE);

  //diff_red_front = curr_red_front - init_red_front;
  diff_blue_front = curr_blue_front - init_blue_front; // act based on difference from ambient value

  // left1 = sens*diff_red_front; // scaled motor values from front sensors
  // right1 = sens*diff_red_front;

  /*if(diff_red_front >= 10) {
    left1 = 100;
    right1 = 100;
  } else {
    left1 = 0;
    right1 = 0;
  }*/

// ---------------------------
//  take reading from right
//  r -> +L -R
//  b -> -L +R
// ----------------------------

  digitalWrite(MUX0, HIGH); // set mux select to 1
  digitalWrite(MUX1, LOW);
  delay(mux_delay);
  curr_red_right = analogRead(RED);
  curr_blue_right = analogRead(BLUE);

  diff_red_right = curr_red_right - init_red_right;
  diff_blue_right = curr_blue_right - init_blue_right;

  if(diff_red_right >= 5) {
    left2red = 10 + (sens*diff_red_right);
    right2red = 10 + (sens*diff_red_right);
  } else {
    left2red = 0;
    right2red = 0;
  }

  if(diff_blue_right >= 5) {
    left2blue = 50 + (sens*diff_blue_right);
    right2blue = 50 + (sens*diff_blue_right);
  } else {
    left2blue = 0;
    right2blue = 0;
  }

  left2 =  left2red -
  left2blue;
  //left2 = -left2blue;
  right2 = -right2red + right2blue;
  //right2 = right2blue;

  // left2 = (sens*diff_red_right) - (sens*diff_blue_right);
  // right2 = -(sens*diff_red_right) + (sens*diff_blue_right);

// ---------------------------
//  take reading from left
//  r -> -L +R
//  b -> +L -R
// ----------------------------

  digitalWrite(MUX0, LOW); // set mux select to 2
  digitalWrite(MUX1, HIGH);
  delay(mux_delay);
  curr_red_left = analogRead(RED);
  curr_blue_left = analogRead(BLUE);

  diff_red_left = curr_red_left - init_red_left;
  diff_blue_left = curr_blue_left - init_blue_left;

  if(diff_red_left >= 5) {
    left3red = 10 + (sens*diff_red_left);
    right3red = 10 + (sens*diff_red_left);
  } else {
    left3red = 0;
    right3red = 0;
  }

  if(diff_blue_left >= 5) {
    left3blue = 50 + (sens*diff_blue_left);
    right3blue = 50 + (sens*diff_blue_left);
  } else {
    left3blue = 0;
    right3blue = 0;
  }

  left3 = -left3red + left3blue;
  //left3 = left3blue;
  right3 = right3red - right3blue;
  //right3 = -right3blue;

  // ---------------------------
//  take reading from back
//  r -> 0
//  b -> +L +R
// ----------------------------

  digitalWrite(MUX0, LOW); // set mux select to 3
  digitalWrite(MUX1, LOW);
  delay(mux_delay);
  //curr_red_back = analogRead(RED);
  curr_blue_back = analogRead(BLUE);;
   right_total = scale*(right1 + right2 + right3 + right4)

  //diff_red_back = curr_red_back - init_red_back;
  diff_blue_back = curr_blue_back - init_blue_back;

  // left4 = (sens*diff_red_back) + (sens*diff_blue_back);
  // right4 = 0;

  if(diff_blue_back >= 10) {
    left1 = 100;
    right1 = 100;
  } else {
    left1 = 0;
    right1 = 0;
  }
}

int Move() {
  // ----------------------------
  // Sum all motor response and 
  // send response to the motors
  // ----------------------------

   left_total = scale*(left1 + left2 + left3 + left4) - 40;
   right_total = scale*(right1 + right2 + right3 + right4) - 40;

   digitalWrite(ADIR,HIGH);
   digitalWrite(BDIR,LOW);

   /*if(diff_red_front >= 80) {
    left_total = 0;
    right_total = 0;
   }*/

   if(left_total <= 0) {
    left_total = 0;
   }
   if(right_total <= 0) {
    right_total = 0;
   }

   analogWrite(APWM,left_total);
   analogWrite(BPWM,right_total);
   delay(motor_delay);
}

void colorWipe(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}
