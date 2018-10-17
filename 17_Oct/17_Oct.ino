// Defining pins

const int diode_in = A2;
int measure;
int measure_better;
int better_better;

void setup() {
  analogReference(DEFAULT);
  Serial.begin(115200);   // set Baud rate

  pinMode(A2, INPUT);
  //pinMode(9, OUTPUT);
}

void loop() {
  measure = analogRead(A2);
  measure_better = constrain(measure, 10, 995);
  better_better = map(measure_better, 10, 995, 1024, 0);
  //digitalWrite(9, HIGH);
  Serial.println(measure);
  delay(200);
}
