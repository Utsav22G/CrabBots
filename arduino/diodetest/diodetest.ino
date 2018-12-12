#define RED A2
#define BLUE A3

int init_red;
int init_blue;

int curr_red;
int curr_blue;

int diff_red;
int diff_blue;

float leftspeed;
float rightspeed;

#define APWM 9
#define ADIR 4
#define BPWM 10
#define BDIR 5

#define MUX0 2
#define MUX1 3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RED,INPUT);
  pinMode(BLUE,INPUT);
  pinMode(APWM,OUTPUT);
  pinMode(ADIR,OUTPUT);
  pinMode(BPWM,OUTPUT);
  pinMode(BDIR,OUTPUT);
  pinMode(MUX0,OUTPUT);
  pinMode(MUX1,OUTPUT);
  pinMode(8,OUTPUT);

  digitalWrite(MUX0,HIGH);
  digitalWrite(MUX1,LOW);
  delay(200);
  init_red = analogRead(RED);
  init_blue = analogRead(BLUE);

}

void loop() {
  Serial.println("hello");
  digitalWrite(MUX0,HIGH);
  digitalWrite(MUX1,LOW);

  curr_red = analogRead(RED);
  curr_blue = analogRead(BLUE);

  diff_red = curr_red - init_red;
  diff_blue = curr_blue - init_blue;
  
  delay(200);
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
