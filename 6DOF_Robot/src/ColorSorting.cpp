#include <Arduino.h>
#include <Servo.h>

// ------------ FUNCTION PROTOTYPES ------------
void moveSmooth(Servo &servo, int &currentPos, int targetPos);
void moveArm(int waist, int shoulder, int elbow, int pitch, int roll, int gripper);
void gripperCheck();
void redTask();
void greenTask();
void blueTask();
void readColor();
bool isRed();
bool isGreen();
bool isBlue();

// ------------ SERVO SETUP ------------
Servo servoWAIST, servoSHOULDER, servoELBOW, servoWRISTPITCH, servoWRISTROLL, servoGRIPPER;

// Global variables (calibrated positions)
int posWAIST = 88, posSHOULDER = 90, posELBOW = 90;
int posPITCH = 95, posROLL = 110, posGRIPPER = 55;

// ------------ COLOR SENSOR PINS (TCS3200) ------------
const int s0 = 12;
const int s1 = 13;
const int s2 = 7;
const int s3 = 8;
const int out = 4;

// ------------ COLOR READINGS ------------
int redVal = 0, greenVal = 0, blueVal = 0;

// ------------ SETUP & LOOP ------------

void setup() {
  Serial.begin(9600);

  servoWAIST.attach(3);
  servoSHOULDER.attach(5);
  servoELBOW.attach(6);
  servoWRISTPITCH.attach(9);
  servoWRISTROLL.attach(10);
  servoGRIPPER.attach(11);

  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, LOW);

  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);

  // Initial move to Home Position
  moveArm(90, 90, 90, 105, 105, 55);
  delay(2000);
  Serial.println("System Initialized...");
}

void loop() {
  readColor();

  if (isRed()) {
    Serial.println("Detected RED box");
    redTask();
  } else if (isGreen()) {
    Serial.println("Detected GREEN box");
    greenTask();
  } else if (isBlue()) {
    Serial.println("Detected BLUE box");
    blueTask();
  }

  delay(500);
}

// ------------ SERVO MOVEMENT FUNCTIONS ------------

void moveSmooth(Servo &servo, int &currentPos, int targetPos) {
  if (currentPos == targetPos) return;
  int step = (targetPos > currentPos) ? 1 : -1;
  for (int pos = currentPos; pos != targetPos; pos += step) {
    servo.write(pos);
    delay(10);
  }
  currentPos = targetPos;
  servo.write(currentPos);
}

void moveArm(int waist, int shoulder, int elbow, int pitch, int roll, int gripper) {
  moveSmooth(servoWAIST, posWAIST, waist);
  moveSmooth(servoSHOULDER, posSHOULDER, shoulder);
  moveSmooth(servoELBOW, posELBOW, elbow);
  moveSmooth(servoWRISTPITCH, posPITCH, pitch);
  moveSmooth(servoWRISTROLL, posROLL, roll);
  moveSmooth(servoGRIPPER, posGRIPPER, gripper);
}

void gripperCheck() {
  servoGRIPPER.write(118); delay(300); // Close
  servoGRIPPER.write(55);  delay(300); // Open
  servoGRIPPER.write(118); delay(300); // Close
  servoGRIPPER.write(55);  delay(300); // Open
  posGRIPPER = 55; 
}

// ------------ PICK-AND-PLACE TASKS ------------

void redTask() {
  gripperCheck();
  moveArm(88, 90, 90, 95, 110, 55);   delay(50);  //Home
  moveArm(88, 90, 55, 95, 110, 55);   delay(10);  //Approach the object
  moveArm(88, 90, 55, 95, 110, 114);  delay(10);  //grab the object //Change the delay to 15 from 10 to make sure that object is pick up properly
  moveArm(88, 90, 90, 95, 110, 114);  delay(10);  //left the object
  moveArm(163, 90, 90, 60, 110, 114);  delay(10);  //transport to red bin
  moveArm(163, 90, 50, 60, 110, 114);  delay(10);  //pre drop preparation
  moveArm(163, 90, 50, 60, 110, 55);  delay(10);  //drop the object
  moveArm(163, 90, 90, 95, 110, 55);   delay(10);  //pre travel home
  moveArm(88, 90, 90, 95, 110, 55);   delay(10);  //home
}

void greenTask() {
  gripperCheck();
  moveArm(90, 90, 90, 95, 110, 55);   delay(10);  //change from 88 to 90 for base motor
  moveArm(88, 90, 55, 95, 110, 55);   delay(10);  
  moveArm(88, 90, 55, 95, 110, 114);  delay(10);  
  moveArm(88, 90, 90, 95, 110, 114);  delay(10);  
  moveArm(165, 90, 90, 95, 110, 114); delay(10);  
  moveArm(165, 85, 75, 130, 110, 114); delay(10);  
  moveArm(165, 85, 75, 130, 110, 55);   delay(10);  
  moveArm(165, 90, 90, 95, 110, 55);   delay(10);  
  moveArm(88, 90, 90, 95, 110, 55);    delay(10);  
}

void blueTask() {
  gripperCheck();
  moveArm(88, 90, 90, 95, 110, 55);   delay(20);  //Change the delay to 20, for a bit pause.
  moveArm(88, 90, 55, 95, 110, 55);   delay(10);  
  moveArm(88, 90, 55, 95, 110, 114);  delay(10);  
  moveArm(88, 90, 90, 95, 110, 114);  delay(10);  
  moveArm(130, 90, 90, 95, 110, 114); delay(10);  
  moveArm(130, 90, 65, 95, 110, 114);   delay(10);  
  moveArm(130, 90, 65, 95, 110, 55);   delay(10);  
  moveArm(130, 90, 90, 95, 110, 55);    delay(10);  
  moveArm(88, 90, 90, 95, 110, 55);   delay(10);  
}

// ------------ COLOR SENSOR FUNCTIONS ------------

void readColor() {
  digitalWrite(s2, LOW); digitalWrite(s3, LOW);
  redVal = pulseIn(out, LOW);
  delay(50);
  digitalWrite(s2, HIGH); digitalWrite(s3, HIGH);
  greenVal = pulseIn(out, LOW);
  delay(50);
  digitalWrite(s2, LOW); digitalWrite(s3, HIGH);
  blueVal = pulseIn(out, LOW);
}

bool isRed() { return (redVal < greenVal && redVal < blueVal && redVal < 60); }
bool isGreen() { return (greenVal < redVal && greenVal < blueVal && greenVal < 60); }
bool isBlue() { return (blueVal < redVal && blueVal < greenVal && blueVal < 90); }
