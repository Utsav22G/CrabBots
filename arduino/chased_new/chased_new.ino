#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include "WS2812_Definitions.h"

// -----------------------
// DEFINE PINS
// -----------------------
#define BLUE1 A2 // input for red photodiode
#define BLUE2 A3 // input for blue photodiode

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
int init_blue_one; // ambient reference value
int init_blue_two;
int init_blue_three;
int init_blue_four;
int init_blue_five;
int init_blue_six;
int init_blue_seven;
int init_blue_eight;

int curr_blue_one; // current value 
int curr_blue_two;
int curr_blue_three;
int curr_blue_four;
int curr_blue_five;
int curr_blue_six;
int curr_blue_seven;
int curr_blue_eight;

int left2red;
int right2red;
int left2blue;
int right2blue;

int left3red;
int right3red;
int left3blue;
int right3blue;

int blue_front;
int blue_right;
int blue_back;
int blue_left;

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
  
  pinMode(BLUE1,INPUT);
  pinMode(BLUE2,INPUT);

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
  init_blue_one = analogRead(BLUE2); // take initial front values to calibrate
  digitalWrite(MUX0, LOW); // set mux select to 0
  digitalWrite(MUX1, LOW);
  init_blue_two = analogRead(BLUE2);

  digitalWrite(MUX0, HIGH); // set mux select to 0
  digitalWrite(MUX1, HIGH);
  delay(150);
  init_blue_three = analogRead(BLUE1); // take initial front values to calibrate
  digitalWrite(MUX0, HIGH); // set mux select to 0
  digitalWrite(MUX1, LOW);
  init_blue_four = analogRead(BLUE1);

  digitalWrite(MUX0, LOW); // set mux select to 0
  digitalWrite(MUX1, HIGH);
  delay(150);
  init_blue_five = analogRead(BLUE1); // take initial front values to calibrate
  digitalWrite(MUX0, LOW); // set mux select to 0
  digitalWrite(MUX1, LOW);
  init_blue_six = analogRead(BLUE1);

  digitalWrite(MUX0, HIGH); // set mux select to 0
  digitalWrite(MUX1, HIGH);
  delay(150);
  init_blue_seven = analogRead(BLUE2); // take initial front values to calibrate
  digitalWrite(MUX0, HIGH); // set mux select to 0
  digitalWrite(MUX1, LOW);
  init_blue_two = analogRead(BLUE2);

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

  bluesum = blue_front + blue_right + blue_left + blue_back;
  if(abs(event.acceleration.z) > 10) {
    if (bump){
      bump = false;
    }
    else if(!bump && bluesum >= 7) {
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
  digitalWrite(MUX0, LOW); // set mux select to 0
  digitalWrite(MUX1, HIGH);
  delay(mux_delay);
  curr_blue_one = analogRead(BLUE2); // take initial front values to calibrate
  digitalWrite(MUX0, LOW); // set mux select to 0
  digitalWrite(MUX1, LOW);
  delay(mux_delay);
  curr_blue_two = analogRead(BLUE2);

  blue_front = (2*((curr_blue_one-init_blue_one)+(curr_blue_two-init_blue_two)))/2;


// ---------------------------
//  take reading from right
//  r -> +L -R
//  b -> -L +R
// ----------------------------

  digitalWrite(MUX0, HIGH); // set mux select to 0
  digitalWrite(MUX1, HIGH);
  delay(mux_delay);
  curr_blue_three = analogRead(BLUE1); // take initial front values to calibrate
  digitalWrite(MUX0, HIGH); // set mux select to 0
  digitalWrite(MUX1, LOW);
  delay(mux_delay);
  curr_blue_four = analogRead(BLUE1);

  blue_right = (2*((curr_blue_three-init_blue_three)+(curr_blue_four-init_blue_four)))/2;

  if(blue_right >= 5) {
    left2blue = 50 + (sens*blue_right);
    right2blue = 50 + (sens*blue_right);
  } else {
    left2blue = 0;
    right2blue = 0;
  }

  left2 = -left2blue;
  right2 = right2blue;

// ---------------------------
//  take reading from left
//  r -> -L +R
//  b -> +L -R
// ----------------------------

  digitalWrite(MUX0, HIGH); // set mux select to 0
  digitalWrite(MUX1, HIGH);
  delay(mux_delay);
  curr_blue_seven = analogRead(BLUE2); // take initial front values to calibrate
  digitalWrite(MUX0, HIGH); // set mux select to 0
  digitalWrite(MUX1, LOW);
  delay(mux_delay);
  curr_blue_eight = analogRead(BLUE2);

  blue_left = (2*((curr_blue_seven-init_blue_seven)+(curr_blue_eight-init_blue_eight)))/2;

  if(blue_left >= 5) {
    left3blue = 50 + (sens*blue_left);
    right3blue = 50 + (sens*blue_left);
  } else {
    left3blue = 0;
    right3blue = 0;
  }

  left3 = left3blue;
  right3 = -right3blue;

  // ---------------------------
//  take reading from back
//  r -> 0
//  b -> +L +R
// ----------------------------

  digitalWrite(MUX0, LOW); // set mux select to 0
  digitalWrite(MUX1, HIGH);
  delay(mux_delay);
  curr_blue_five = analogRead(BLUE1); // take initial front values to calibrate
  digitalWrite(MUX0, LOW); // set mux select to 0
  digitalWrite(MUX1, LOW);
  delay(mux_delay);
  curr_blue_six = analogRead(BLUE1);

  blue_back = (2*((curr_blue_five-init_blue_five)+(curr_blue_six-init_blue_six)))/2;

  if(blue_back >= 10) {
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
