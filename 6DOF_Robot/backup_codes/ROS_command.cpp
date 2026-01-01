#include <Arduino.h>
#include <Servo.h>

// ------------ SERVO SETUP ------------
Servo servoA, servoB, servoC, servoD, servoE, servoF;

// Current positions (Global trackers)
int posA = 90, posB = 90, posC = 90, posD = 105, posE = 105, posF = 55;

// ------------ COLOR SENSOR PINS (TCS3200) ------------
const int s0 = 12, s1 = 13, s2 = 7, s3 = 8, out = 4;
int redVal = 0, greenVal = 0, blueVal = 0;
String inputString = "";

// ------------ FUNCTION PROTOTYPES ------------
void moveSmooth(Servo& servo, int& currentPos, int targetAngle);
void moveArm(int a, int b, int c, int d, int e, int f);
void processCommand(String command);
void readColor();
void redTask();
void greenTask();
void blueTask();
void gripperCheck();

// ------------ SETUP ------------
void setup() {
  Serial.begin(9600);
  
  servoA.attach(3); servoB.attach(5); servoC.attach(6);
  servoD.attach(9); servoE.attach(10); servoF.attach(11);

  pinMode(s0, OUTPUT); pinMode(s1, OUTPUT);
  digitalWrite(s0, HIGH); digitalWrite(s1, LOW);
  pinMode(s2, OUTPUT); pinMode(s3, OUTPUT); pinMode(out, INPUT);

  // Home the arm
  servoA.write(posA); servoB.write(posB); servoC.write(posC);
  servoD.write(posD); servoE.write(posE); servoF.write(posF);
  
  Serial.println("SYSTEM READY: Auto-Sort + ROS Letter Mode");
}

// ------------ MAIN LOOP ------------
void loop() {
  if (Serial.available() > 0) {
    char inChar = (char)Serial.read();
    
    if (inChar != '\n' && inChar != '\r') {
      inputString += inChar;
    }

    // Process if we hit a newline or have a full command (e.g., A120)
    if (inChar == '\n' || inChar == '\r' || inputString.length() >= 4) {
      if (inputString.length() >= 2) {
        processCommand(inputString);
      }
      inputString = ""; 
    }
  } 
  else {
    // If no Serial commands, run sorting logic
    readColor();

    if (redVal < greenVal && redVal < blueVal && redVal < 60) {
      Serial.println("Detected RED box");
      redTask();
    } else if (greenVal < redVal && greenVal < blueVal && greenVal < 60) {
      Serial.println("Detected GREEN box");
      greenTask();
    } else if (blueVal < redVal && blueVal < greenVal && blueVal < 90) {
      Serial.println("Detected BLUE box");
      blueTask();
    }
    delay(200);
  }
}

// ------------ SERIAL COMMAND PROCESSING ------------
void processCommand(String command) {
  command.trim();
  char joint = command.charAt(0);
  if (joint >= 'a' && joint <= 'z') joint -= 32; // Convert to uppercase

  int value = command.substring(1).toInt(); 
  value = constrain(value, 0, 180);

  switch(joint) {
    case 'A': moveSmooth(servoA, posA, value); break;
    case 'B': moveSmooth(servoB, posB, value); break;
    case 'C': moveSmooth(servoC, posC, value); break;
    case 'D': moveSmooth(servoD, posD, value); break;
    case 'E': moveSmooth(servoE, posE, value); break;
    case 'F': moveSmooth(servoF, posF, value); break;
  }
}

// ------------ MOVEMENT ENGINE ------------
void moveSmooth(Servo& servo, int& current, int target) {
  if (current == target) return;
  int step = (current < target) ? 1 : -1;
  while (current != target) {
    current += step;
    servo.write(current);
    delay(10);
  }
}

void moveArm(int a, int b, int c, int d, int e, int f) {
  moveSmooth(servoA, posA, a);
  moveSmooth(servoB, posB, b);
  moveSmooth(servoC, posC, c);
  moveSmooth(servoD, posD, d);
  moveSmooth(servoE, posE, e);
  moveSmooth(servoF, posF, f);
}

// ------------ COLOR SENSOR & TASKS ------------
void readColor() {
  digitalWrite(s2, LOW); digitalWrite(s3, LOW);
  redVal = pulseIn(out, LOW); delay(50);
  digitalWrite(s2, HIGH); digitalWrite(s3, HIGH);
  greenVal = pulseIn(out, LOW); delay(50);
  digitalWrite(s2, LOW); digitalWrite(s3, HIGH);
  blueVal = pulseIn(out, LOW);
}

void gripperCheck() {
  servoF.write(118); delay(300);
  servoF.write(55);  delay(300);
  posF = 55; 
}

void redTask() {
  gripperCheck();
  moveArm(90, 60, 85, 105, 105, 55);
  moveArm(90, 60, 85, 105, 105, 118);
  moveArm(90, 90, 90, 105, 105, 118);
  moveArm(153, 90, 45, 45, 105, 55);
  moveArm(90, 90, 90, 105, 105, 55);
}

void greenTask() {
  gripperCheck();
  moveArm(90, 60, 85, 105, 105, 118);
  moveArm(150, 90, 70, 110, 105, 55);
  moveArm(90, 90, 90, 105, 105, 55);
}

void blueTask() {
  gripperCheck();
  moveArm(90, 60, 85, 105, 105, 118);
  moveArm(120, 90, 55, 65, 105, 55);
  moveArm(90, 90, 90, 105, 105, 55);
}