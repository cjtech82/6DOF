#include <Arduino.h>
#include <Servo.h>

Servo servoWAIST; 
Servo servoSHOULDER;
Servo servoELBOW;
Servo servoWRISTPITCH;
Servo servoWRISTROLL;
Servo servoGRIPPER;
int pos = 90;   
int buttonsw = 7;
int posincrement = 1;

int jtWAIST = A1;
int jtSHOULDER = A0;
int jtELBOW = A2;
int jtWRISTPITCH = A4;
int jtWRISTROLL = A3;
int jtGRIPPER = A5;

int posWAIST = 90, posSHOULDER = 90, posELBOW = 90, posWRISTPITCH = 90, posWRISTROLL = 90, posGRIPPER = 90;

void setup() {
  Serial.begin(9600);
  
  servoWAIST.attach(3);
  servoSHOULDER.attach(5);
  servoELBOW.attach(6);
  servoWRISTPITCH.attach(9);
  servoWRISTROLL.attach(10);
  servoGRIPPER.attach(11);
  
  delay(100);
  
  
  servoSHOULDER.write(90), delay(500);
  servoELBOW.write(90), delay(500);
  servoWRISTPITCH.write(90), delay(500);
  servoWRISTROLL.write(90), delay(500);
  servoGRIPPER.write(90), delay(500);
  servoWAIST.write(90), delay(500);
  
}

void loop() {
  //Serial.print("servo position: "), Serial.print(pos), Serial.write(", "), Serial.println(analogRead(0));
  

  if(analogRead(jtWAIST) < 400){
    Serial.print("jtWAIST: "), Serial.println(posWAIST);
    posWAIST = posWAIST - posincrement;
    if(posWAIST < 0) posWAIST = 0;
    servoWAIST.write(posWAIST);
  }
  else if(analogRead(jtWAIST) > 600){
    Serial.print("jtWAIST: "), Serial.println(posWAIST);
    posWAIST = posWAIST + posincrement;
    if(posWAIST > 180) posWAIST = 180;
    servoWAIST.write(posWAIST);
  }

  if(analogRead(jtSHOULDER) < 400){
    Serial.print("jtSHOULDER: "), Serial.println(jtSHOULDER);
    posSHOULDER = posSHOULDER - posincrement;
    if(posSHOULDER < 0) posSHOULDER = 0;
    servoSHOULDER.write(posSHOULDER);
  }
  else if(analogRead(jtSHOULDER) > 600){
    Serial.print("jtSHOULDER: "), Serial.println(jtSHOULDER);
    posSHOULDER = posSHOULDER + posincrement;
    if(posSHOULDER > 180) posSHOULDER = 180;
    servoSHOULDER.write(posSHOULDER);
  }

  if(analogRead(jtELBOW) < 400){
    Serial.print("jtELBOW: "), Serial.println(jtELBOW);
    posELBOW = posELBOW + posincrement;
    if(posELBOW > 180) posELBOW = 180;
    servoELBOW.write(posELBOW);
  }
  else if(analogRead(jtELBOW) > 600){
    Serial.print("jtELBOW: "), Serial.println(jtELBOW);
    posELBOW = posELBOW - posincrement;
    if(posELBOW < 0) posELBOW = 0;
    servoELBOW.write(posELBOW);
    
  }  

  if(analogRead(jtWRISTPITCH) < 400){
    Serial.print("jtWRISTPITCH: "), Serial.println(posWRISTPITCH);
    posWRISTPITCH = posWRISTPITCH - posincrement;
    if(posWRISTPITCH < 0) posWRISTPITCH = 0;
    servoWRISTPITCH.write(posWRISTPITCH);
  }
  else if(analogRead(jtWRISTPITCH) > 600){
    Serial.print("jtWRISTPITCH: "), Serial.println(posWRISTPITCH);
    posWRISTPITCH = posWRISTPITCH + posincrement;
    if(posWRISTPITCH > 180) posWRISTPITCH = 180;
    servoWRISTPITCH.write(posWRISTPITCH);
  }  

  if(analogRead(jtWRISTROLL) < 400){
    Serial.print("jtWRISTROLL: "), Serial.println(posWRISTPITCH);
    posWRISTROLL = posWRISTROLL + posincrement;
    if(posWRISTROLL > 180) posWRISTROLL = 180;
    servoWRISTROLL.write(posWRISTROLL);
    
  }
  else if(analogRead(jtWRISTROLL) > 600){
    Serial.print("jtWRISTROLL: "), Serial.println(posWRISTROLL);
    posWRISTROLL = posWRISTROLL - posincrement;
    if(posWRISTROLL < 0) posWRISTROLL = 0;
    servoWRISTROLL.write(posWRISTROLL);
  }   
  
  if(analogRead(jtGRIPPER) < 400){
    Serial.print("jtGRIPPER: "), Serial.println(posGRIPPER);
    posGRIPPER = posGRIPPER - posincrement;
    if(posGRIPPER < 0) posGRIPPER = 0;
    servoGRIPPER.write(posGRIPPER);
  }
  else if(analogRead(jtGRIPPER) > 600){
    Serial.print("jtGRIPPER: "), Serial.println(posGRIPPER);
    posGRIPPER = posGRIPPER + posincrement;
    if(posGRIPPER > 180) posGRIPPER = 180;
    servoGRIPPER.write(posGRIPPER);
  }    
  
  delay(20);
}
