#include <Arduino.h>
#include <Servo.h>

// ------------ FUNCTION PROTOTYPES ------------
void moveSmooth(Servo& servo, int targetAngle);
void processCommand(String command);

// Create servo objects
Servo servoA, servoB, servoC, servoD, servoE, servoF;

String inputString = "";

void setup() {
  Serial.begin(9600);
  
  // Attach servos to pins
  servoA.attach(3); servoB.attach(5); servoC.attach(6);
  servoD.attach(9); servoE.attach(10); servoF.attach(11);

  // Initial Move
  servoA.write(90);
  
  Serial.println("\n--- CASE-INSENSITIVE READY ---");
  Serial.println("Type 'A120' or 'a120' - it will move immediately.");
}

void loop() {
  if (Serial.available() > 0) {
    char inChar = (char)Serial.read();
    
    // Add character to string if it's not a newline
    if (inChar != '\n' && inChar != '\r') {
      inputString += inChar;
    }

    // Process once we have enough characters (e.g. "a120" is 4 chars)
    if (inputString.length() >= 4 || inChar == '\n' || inChar == '\r') {
      delay(20); // Let the serial buffer finish
      processCommand(inputString);
      inputString = ""; // Reset buffer
    }
  }
}

void processCommand(String command) {
  command.trim();
  if (command.length() < 2) return;

  // Convert the first character to Uppercase manually to be safe
  char joint = command.charAt(0);
  if (joint >= 'a' && joint <= 'z') {
    joint = joint - 32; // Standard ASCII conversion from lower to upper
  }

  // Get the number part
  int value = command.substring(1).toInt(); 
  value = constrain(value, 0, 180);

  Serial.print("\n[OK] Moving "); Serial.print(joint); 
  Serial.print(" to "); Serial.println(value);

  switch(joint) {
    case 'A': moveSmooth(servoA, value); break;
    case 'B': moveSmooth(servoB, value); break;
    case 'C': moveSmooth(servoC, value); break;
    case 'D': moveSmooth(servoD, value); break;
    case 'E': moveSmooth(servoE, value); break;
    case 'F': moveSmooth(servoF, value); break;
    default: Serial.println("Joint unknown. Use A-F");
  }
}

void moveSmooth(Servo& servo, int targetAngle) {
  int current = servo.read();
  int step = (current < targetAngle) ? 1 : -1;
  while (current != targetAngle) {
    current += step;
    servo.write(current);
    delay(15);
  }
}