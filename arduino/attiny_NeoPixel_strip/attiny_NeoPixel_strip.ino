#include <Adafruit_NeoPixel.h>
#include "WS2812_Definitions.h"

#define BUTTON_PIN A1
#define LED_INPUT 1
#define LED_COUNT 9

int brightness = 255;
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_INPUT, NEO_RGB + NEO_KHZ800);

void clear_LEDs() {
   // This function turns all LEDs off
  for (int i=0; i<LED_COUNT; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
}

void nth_pixel(int nth, int R, int G, int B) {
  // Sets the color of the nth pixel
  // Note: indexing starts at 0
  strip.setPixelColor(nth, R, G, B);
  strip.show();
}

void range_pixels(int start, int end, int R, int G, int B) {
  // Sets the color of all pixels in the range (start, end)
  // Note: start and end are inclusive
  for(int i = start; i <= end; i++) {
    strip.setPixelColor(i, R, G, B);
    strip.show();
  }
}

void setup() {
  pinMode(LED_INPUT, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  strip.begin();  // Call this to start up the LED strip.
  clear_LEDs();   // This function, defined above, turns all LEDs off...
  strip.show();   // ...but the LEDs don't actually update until you call this
}

void loop() {
  strip.setBrightness(brightness);  // control the brightness, integer from 0-255

  // read the pushbutton input pin:
  buttonState = digitalRead(BUTTON_PIN);
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // went from off to on:
      buttonPushCounter++;
    }
    delay(50);
  }

  if (buttonPushCounter % 3 == 0) {
    range_pixels(0, (LED_COUNT-1), 0, 0, 255);
  }
  else if (buttonPushCounter % 2 == 0) {
    range_pixels(0, (LED_COUNT-1), 0, 255, 0);
  }
  else {
    clear_LEDs();
    strip.show();
  }

  lastButtonState = buttonState;
}
