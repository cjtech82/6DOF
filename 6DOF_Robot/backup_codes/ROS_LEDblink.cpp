#include <Arduino.h>
#include <Servo.h>

Servo s1, s2, s3, s4, s5, s6;
int ledPin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  s1.attach(3); s2.attach(5); s3.attach(6);
  s4.attach(9); s5.attach(10); s6.attach(11);

  // Blink 3 times to show code is alive
  for(int i=0; i<3; i++){
    digitalWrite(ledPin, HIGH); delay(200);
    digitalWrite(ledPin, LOW); delay(200);
  }
}

void loop() {
  if (Serial.available() > 0) {
    int w = Serial.parseInt();
    int s = Serial.parseInt();
    int e = Serial.parseInt();
    int p = Serial.parseInt();
    int r = Serial.parseInt();
    int g = Serial.parseInt();

    if (Serial.read() == '\n') {
      // Valid data received! Blink the LED
      digitalWrite(ledPin, HIGH);
      
      s1.write(w); s2.write(s); s3.write(e);
      s4.write(p); s5.write(r); s6.write(g);
      
      delay(10); 
      digitalWrite(ledPin, LOW);
    }
  }
}