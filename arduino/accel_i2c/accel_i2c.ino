// Basic demo for accelerometer readings from Adafruit LIS3DH

#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>


Adafruit_LIS3DH lis = Adafruit_LIS3DH();


void setup(void) {
pinMode(8, OUTPUT); //change this to 0x19 for alternative i2c address


  if (! lis.begin(0x18)) { 
    //
    while (1){
    digitalWrite(8, HIGH);
    delay(500);
    digitalWrite(8, LOW);
    delay(500);
    }
  }


  lis.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!

}

void loop() {
  lis.read();      // get X Y and Z data at once
  // Then print out the raw data


  /* Or....get a new sensor event, normalized */
  sensors_event_t event;
  lis.getEvent(&event);

  if(event.acceleration.z > 1) {
  digitalWrite(8, HIGH);
  delay(100);
  }
  digitalWrite(8, LOW);
  delay(100);
}
