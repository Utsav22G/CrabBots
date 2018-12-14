#include <Adafruit_NeoPixel.h>
#include "WS2812_Definitions.h"

#define LED_INPUT 1
#define POT_PIN_0 A1
#define POT_PIN_1 A2
#define POT_PIN_2 A3
#define LED_COUNT 5

int brightness = 64;
int R = 0;
int G = 0;
int B = 0;

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
    strip.setPixelColor(i, 0);
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
  // Serial.begin(115200);  // ATtiny don't have inbuilt Serial UART

  pinMode(LED_INPUT, OUTPUT);
  pinMode(POT_PIN_0, INPUT);
  pinMode(POT_PIN_1, INPUT);
  pinMode(POT_PIN_2, INPUT);

  strip.begin();  // Call this to start up the LED strip.
  clear_LEDs();   // This function, defined above, turns all LEDs off...
  strip.show();   // ...but the LEDs don't actually update until you call this
}

void loop() {
  int pwm_0 = analogRead(POT_PIN_0);
  pwm_0 = map(pwm_0, 0, 1023, 0, 255);
  pwm_0 = constrain(pwm_0, 0, 255);

  int pwm_1 = analogRead(POT_PIN_1);
  pwm_1 = map(pwm_1, 0, 1023, 0, 255);
  pwm_1 = constrain(pwm_1, 0, 255);

  int pwm_2 = analogRead(POT_PIN_2);
  pwm_2 = map(pwm_2, 0, 1023, 0, 255);
  pwm_2 = constrain(pwm_2, 0, 255);

  strip.setBrightness(brightness);  // control the brightness, integer from 0-255

  // nth_pixel(4, 255, 0, 0);
  range_pixels(0, 4, pwm_0, pwm_1, pwm_2);
}
