#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include "WS2812_Definitions.h"

// -----------------------
// DEFINE PINS
// -----------------------
#define RED1 A2 // input for red photodiode
#define RED2 A3 // input for blue photodiode

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
int init_red_one; // ambient reference value
int init_red_two;
int init_red_three;
int init_red_four;
int init_red_five;
int init_red_six;
int init_red_seven;
int init_red_eight;

int curr_red_one; // current value 
int curr_red_two;
int curr_red_three;
int curr_red_four;
int curr_red_five;
int curr_red_six;
int curr_red_seven;
int curr_red_eight;

int left2red;
int right2red;
int left2blue;
int right2blue;

int left3red;
int right3red;
int left3blue;
int right3blue;

int red_front;
int red_right;
int red_back;
int red_left;

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
int bluesum;

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
  
  pinMode(RED1,INPUT);
  pinMode(RED2,INPUT);

  pinMode(APWM,OUTPUT);
  pinMode(ADIR,OUTPUT);

  pinMode(BPWM,OUTPUT);
  pinMode(BDIR,OUTPUT);
 
  pinMode(MUX0, OUTPUT);
  pinMode(MUX1, OUTPUT);

  pinMode(LED_INPUT, OUTPUT);

  digitalWrite(MUX0, LOW); // set mux select to 0
  digitalWrite(MUX1, HIGH);
  delay(150);
  init_red_one = analogRead(RED2); // take initial front values to calibrate
  digitalWrite(MUX0, LOW); // set mux select to 0
  digitalWrite(MUX1, LOW);
  delay(150);
  init_red_two = analogRead(RED2);

  digitalWrite(MUX0, HIGH); // set mux select to 0
  digitalWrite(MUX1, HIGH);
  delay(150);
  init_red_three = analogRead(RED1); // take initial front values to calibrate
  digitalWrite(MUX0, HIGH); // set mux select to 0
  digitalWrite(MUX1, LOW);
  delay(150);
  init_red_four = analogRead(RED1);

  digitalWrite(MUX0, LOW); // set mux select to 0
  digitalWrite(MUX1, HIGH);
  delay(150);
  init_red_five = analogRead(RED1); // take initial front values to calibrate
  digitalWrite(MUX0, LOW); // set mux select to 0
  digitalWrite(MUX1, LOW);
  delay(150);
  init_red_six = analogRead(RED1);

  digitalWrite(MUX0, HIGH); // set mux select to 0
  digitalWrite(MUX1, HIGH);
  delay(150);
  init_red_seven = analogRead(RED2); // take initial front values to calibrate
  digitalWrite(MUX0, HIGH); // set mux select to 0
  digitalWrite(MUX1, LOW);
  init_red_two = analogRead(RED2);

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
    delay(500);
    colorWipe(strip.Color(0, 0, 255));
    bump = false;
    
  } else {
    colorWipe(strip.Color(0, 0, 255)); // Red
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
  digitalWrite(MUX0, LOW); // set mux select to 0
  digitalWrite(MUX1, HIGH);
  delay(mux_delay);
  curr_red_one = analogRead(RED2); // take initial front values to calibrate
  digitalWrite(MUX0, LOW); // set mux select to 0
  digitalWrite(MUX1, LOW);
  delay(mux_delay);
  curr_red_two = analogRead(RED2);

  //red_front = (2*((curr_red_one-init_red_one)+(curr_red_two-init_red_two)))/2;
  red_front = curr_red_one - init_red_one;
  if(red_front >= 10) {
    left1 = 100;
    right1 = 100;
  } else {
    left1 = 0;
    right1 = 0;
  }


// ---------------------------
//  take reading from right
//  r -> +L -R
//  b -> -L +R
// ----------------------------

  digitalWrite(MUX0, HIGH); // set mux select to 0
  digitalWrite(MUX1, HIGH);
  delay(mux_delay);
  curr_red_three = analogRead(RED1); // take initial front values to calibrate
  digitalWrite(MUX0, HIGH); // set mux select to 0
  digitalWrite(MUX1, LOW);
  delay(mux_delay);
  curr_red_four = analogRead(RED1);

  red_right = (2*((curr_red_three-init_red_three)+(curr_red_four-init_red_four)))/2;
  //red_right = curr_red_three-init_red_three;

  if(red_right >= 5) {
    left2red = 50 + (sens*red_right);
    right2red = 50 + (sens*red_right);
  } else {
    left2red = 0;
    right2red = 0;
  }

  left2 = left2red;
  right2 = -right2red;

// ---------------------------
//  take reading from left
//  r -> -L +R
//  b -> +L -R
// ----------------------------

  digitalWrite(MUX0, HIGH); // set mux select to 0
  digitalWrite(MUX1, HIGH);
  delay(mux_delay);
  curr_red_seven = analogRead(RED2); // take initial front values to calibrate
  digitalWrite(MUX0, HIGH); // set mux select to 0
  digitalWrite(MUX1, LOW);
  delay(mux_delay);
  curr_red_eight = analogRead(RED2);

  red_left = (2*((curr_red_seven-init_red_seven)+(curr_red_eight-init_red_eight)))/2;
  //red_left = curr_red_seven-init_red_seven;

  if(red_left >= 5) {
    left3red = 50 + (sens*red_left);
    right3red = 50 + (sens*red_left);
  } else {
    left3red = 0;
    right3red = 0;
  }

  left3 = -left3red;
  right3 = right3red;

  // ---------------------------
//  take reading from back
//  r -> 0
//  b -> +L +R
// ----------------------------

  digitalWrite(MUX0, LOW); // set mux select to 0
  digitalWrite(MUX1, HIGH);
  delay(mux_delay);
  curr_red_five = analogRead(RED1); // take initial front values to calibrate
  digitalWrite(MUX0, LOW); // set mux select to 0
  digitalWrite(MUX1, LOW);
  delay(mux_delay);
  curr_red_six = analogRead(RED1);

  red_back = (2*((curr_red_five-init_red_five)+(curr_red_six-init_red_six)))/2;

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
