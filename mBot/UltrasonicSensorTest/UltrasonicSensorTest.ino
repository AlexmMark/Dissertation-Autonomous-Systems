/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * @file    UltrasonicSensorTest.ino
 * @author  MakeBlock
 * @version V1.0.0
 * @date    2015/09/01
 * @brief   Description: this file is sample code for Me ultrasonic sensor module.
 *
 * Function List:
 * 1. double MeUltrasonicSensor::distanceCm(uint16_t MAXcm)
 *
 * \par History:
 * <pre>
 * <Author>     <Time>        <Version>      <Descr>
 * Mark Yan     2015/09/01    1.0.0          rebuild the old lib
 * </pre>
 */
#include "MeMCore.h"
#include <SoftwareSerial.h>


// SENSOR
MeUltrasonicSensor ultraSensor(PORT_3); /* Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield. */

//MOTORS
MeDCMotor MotorL(M1);
MeDCMotor MotorR(M2);

//RGB LED
// Onboard LED port/slot definitions
const int PORT = 7;
const int SLOT = 2;

// LED Control settings
const int BOTH_LEDS = 0;
const int RIGHT_LED = 1;
const int LEFT_LED  = 2;

// Declare the MeRGLed object
MeRGBLed led(PORT, SLOT);

int movespeed = 100;
int moveDuration = 900;
int workCounter = 0;


void Forward(){
  MotorL.run(-movespeed);
  MotorR.run(movespeed);
  delay(moveDuration);
  MotorL.stop();
  MotorR.stop();
}

void Backward(){
  MotorL.run(movespeed);
  MotorR.run(-movespeed);
  delay(moveDuration);
  MotorL.stop();
  MotorR.stop();
}

void Turn(){
  MotorL.run(-movespeed);
  MotorR.run(-movespeed);
  delay(700);
  MotorL.stop();
  MotorR.stop();
}

void Stop(){
  MotorL.stop();
  MotorR.stop();
}

void updateLED(int ledNum, int red, int green, int blue) {
  led.setColor(ledNum, red, green, blue);
  led.show();
}

void offLED(int ledNum){
  updateLED(ledNum, 0,0,0);
}

void doWork(){
  updateLED(BOTH_LEDS,0,255,0);
   delay(1000);
  updateLED(BOTH_LEDS,255,0,0);
   delay(1000);
  offLED(BOTH_LEDS);
}

void setup() {
  // Initialize serial communication with a baud rate of 9600
  Serial.begin(9600);
  Serial.println("Arduino ready!");
}

void loop() {
  
  // Check if data is available to read from serial
  if (Serial.available() > 0) {
    // Read the incoming byte
    char receivedChar = Serial.read(); 

 if (receivedChar == 'C'){
      Serial.print("Sensor_Reading");
      delay(300);
      double distance = ultraSensor.distanceCm();
      Serial.print(distance);
      delay(300);
      Serial.print("end_Sensor_Reading");
      delay(100);

    } else if (receivedChar == 'U'){
      workCounter++;
      delay(300);
      if (workCounter % 5 == 0) {
      Serial.print("doWork");
      delay(300);
      Serial.print("end_doWork");
      delay(100);
      } else {
      Serial.print("Sensor_Reading");
      delay(300);
      double distance = ultraSensor.distanceCm();
      Serial.print(distance);
      delay(300);
      Serial.print("end_Sensor_Reading");
      delay(100);
      }
      
    }else if (receivedChar == '3'){
      delay(100);
      Turn();
      delay(100);
    } else if (receivedChar == '1'){
      delay(100);
      Forward();
      delay(100);
    } else if (receivedChar == '2'){
      delay(100);
      Backward();
      Turn();
      delay(100);
    } else if (receivedChar == '4'){
      delay(100);
      doWork();
      delay(100);
    }
  }
}


