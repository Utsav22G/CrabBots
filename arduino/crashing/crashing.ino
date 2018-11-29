// Basic demo for accelerometer readings from Adafruit LIS3DH

#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

#define BPWM 10
#define APWM 9
#define BDIR 5
#define ADIR 4

bool crash = true;

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

void setup(void) {
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    while (1){
      digitalWrite(8,HIGH);
      delay(100);
      digitalWrite(8,LOW);
      delay(100);
    }
  }
  
  pinMode(ADIR, OUTPUT);
  pinMode(BDIR, OUTPUT);
  pinMode(APWM, OUTPUT);
  pinMode(BPWM, OUTPUT);

  digitalWrite(BPWM, HIGH);
  digitalWrite(APWM, HIGH);
  digitalWrite(ADIR, HIGH);
  digitalWrite(BDIR, HIGH);

  digitalWrite(8,HIGH);
  
  lis.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!
}

void loop() {
  digitalWrite(BDIR, LOW);
  lis.read();      // get X Y and Z data at once
  sensors_event_t event; 
  lis.getEvent(&event);
  // Then print out the raw data
  
  if(event.acceleration.z > 13) {
    if (crash){
      crash = false;
    }
    else{
      crash = true;
    }
  }
  
  if(crash){
    digitalWrite(8, LOW);
    digitalWrite(BPWM, LOW);
    digitalWrite(APWM, LOW);
  }
  else {
    digitalWrite(BPWM, HIGH);
    digitalWrite(APWM, HIGH);
    digitalWrite(8, HIGH);
  }
  /* Or....get a new sensor event, normalized */
  //  sensors_event_t event;
  //  lis.getEvent(&event);

  /* Display the results (acceleration is measured in m/s^2) */
//  delay(1);
//  digitalWrite(BPWM, LOW);
//  digitalWrite(APWM, LOW);
//  digitalWrite(8, LOW );
  delay(11);
}
