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

int mux_delay = 150;
int motor_delay = 200;

unsigned long prevTime = 0;
unsigned long currTime;
int programCounter = 0;

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

void setup() {
  Serial.begin(9600);
  
  pinMode(RED,INPUT);
  pinMode(BLUE,INPUT);

  pinMode(APWM,OUTPUT);
  pinMode(ADIR,OUTPUT);

  pinMode(BPWM,OUTPUT);
  pinMode(BDIR,OUTPUT);

  pinMode(MUX0, OUTPUT);
  pinMode(MUX1, OUTPUT);

  digitalWrite(MUX0, LOW); // set mux select to 0
  digitalWrite(MUX1, LOW);
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
  init_red_left = analogRead(RED);
  init_blue_left = analogRead(BLUE);

  digitalWrite(MUX0, HIGH); // set mux select to 3
  digitalWrite(MUX1, HIGH);
  delay(150);
  init_red_back = analogRead(RED);
  init_blue_back = analogRead(BLUE);
}

void loop() {
  
  currTime = millis();
  
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
  digitalWrite(MUX1, LOW);
  delay(mux_delay);
  curr_red_front = analogRead(RED);
  curr_blue_front = analogRead(BLUE);

  diff_red_front = curr_red_front - init_red_front;
  diff_blue_front = curr_blue_front - init_blue_front; // act based on difference from ambient value

  left1 = sens*diff_red_front; // scaled motor values from front sensors
  right1 = sens*diff_red_front;

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

  left2 = (sens*diff_red_right) - (sens*diff_blue_right);
  right2 = -(sens*diff_red_right) + (sens*diff_blue_right);

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

  left3 = -(sens*diff_red_left) + (sens*diff_blue_left);
  right3 = (sens*diff_red_left) - (sens*diff_blue_left);

  // ---------------------------
//  take reading from back
//  r -> 0
//  b -> +L +R
// ----------------------------

  digitalWrite(MUX0, HIGH); // set mux select to 3
  digitalWrite(MUX1, HIGH);
  delay(mux_delay);
  curr_red_back = analogRead(RED);
  curr_blue_back = analogRead(BLUE);

  diff_red_back = curr_red_back - init_red_back;
  diff_blue_back = curr_blue_back - init_blue_back;

  left4 = (sens*diff_red_back) + (sens*diff_blue_back);
  right4 = 0;

// ----------------------------
// Sum all motor response and 
// send response to the motors
// ----------------------------

   left_total = scale*(left1 + left2 + left3 + left4 + 10);
   right_total = scale*(right1 + right2 + right3 + right4 + 10);

   digitalWrite(ADIR,HIGH);
   digitalWrite(BDIR,LOW);

   if(diff_red_front >= 100) {
    left_total = 0;
    right_total = 0;
   }

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

