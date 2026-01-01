#define S2 8
#define S3 12
#define sensorOut 13

void setup() {
  pinMode(S2, OUTPUT); pinMode(S3, OUTPUT); pinMode(sensorOut, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(S2, LOW); digitalWrite(S3, LOW);
  Serial.print("R: "); Serial.print(pulseIn(sensorOut, LOW));
  
  digitalWrite(S2, HIGH); digitalWrite(S3, HIGH);
  Serial.print(" G: "); Serial.print(pulseIn(sensorOut, LOW));
  
  digitalWrite(S2, LOW); digitalWrite(S3, HIGH);
  Serial.print(" B: "); Serial.println(pulseIn(sensorOut, LOW));
  delay(500);
}