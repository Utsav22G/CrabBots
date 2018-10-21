/*--- GLOBAL VARIABLES ---*/
int sensor1[11];
int counter = 0;


void setup() {
  pinMode(A0,INPUT);
  pinMode(A1, INPUT);

  Serial.begin(9600);

}


void loop() {
  readSensor(A0, sensor1);
  printVal(1, sensor1);
}


/*---- SUPPORT FUNCTIONS ----*/

//refresh rolling average
void readSensor(int pin, int sensorVal[]){
  int i;
  int sum= 0;
  for(i= 10; i>1; i = i-1){
    sum = sum + sensorVal[i];
    sensorVal[i] = sensorVal[i-1];
  }
  sensorVal[1] = analogRead(pin);
  sensorVal[0] = sum/10;
}

//display average voltage
void printVal(int num, int sensorVal[]){
  Serial.print("sensor ");
  Serial.print(num);
  Serial.print(": ");
  Serial.println(sensorVal[0]);
}
