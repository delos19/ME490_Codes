﻿/*Begining of Auto generated code by Atmel studio */
#define F_CPU 16000000UL
#include <avr/io.h>

#include <Arduino.h>

/*End of auto generated code by Atmel studio */

//See BareMinimum example for a list of library functions

//Includes required to use Roboclaw library
#include <SoftwareSerial.h>
#include "RoboClaw.h"
//Beginning of Auto generated function prototypes by Atmel Studio
//End of Auto generated function prototypes by Atmel Studio

//See limitations of Arduino SoftwareSerial
SoftwareSerial serial(0,1);	
RoboClaw roboclaw(&serial,10000);
//RoboClaw roboclaw(Serial,10000);
#define address 0x80

//LED Pint and PinMode initializing of variables
int ledPin = 9;
int val = 0;
int valPerc = 0;
int potPin = A2;
int threshold = 0.2;
double setPoint = 0;
int pos = 0;

//PID Constants
/*double kp = 2;
double ki = 5;
double kd = 1;

unsigned long currentTime, previousTime;
double elapsedTime;
double error;
double lastError;
double input, output, setPoint;
double cumError, rateError;*/

void setup() {
  //Open roboclaw serial ports
  roboclaw.begin(38400);
  pinMode(ledPin, OUTPUT);
  pinMode(potPin, INPUT)
  setPoint = 7;
}
 
void loop() {
  //roboclaw.ForwardM1(address,64); //start Motor1 forward at half speed
  //digitalWrite(ledPin, HIGH);
  //delay(2000);

  //roboclaw.BackwardM1(address,64);
  //digitalWrite(ledPin, LOW);
  //delay(2000);

  //roboclaw.ForwardM1(address,96); //start Motor1 forward at half speed
  //digitalWrite(ledPin, HIGH);
  //delay(2000);

  //roboclaw.BackwardM1(address,32);
  //digitalWrite(ledPin, LOW);
  //delay(2000);
  
  ////////////////////////////////////////////////////////////////////////////////
  
  val = analogRead(potPin);
  pos = map(val, 0, 1023, 0, 8) //Convert to the stroke length of actuator 
  if (pos >= (setPoint - threshold) && pos <= (setPoint + threshold)){ 
	roboclaw.BackwardM1(address,0);
  }
  else if (pos > setPoint){
	roboclaw.ForwardM1(address, 64);
  }
  else if (pos < setPoint){
	  roboclaw.BackwardM1(address, 64);
  }
}
    ///////////////////////////////////////////////////////////////////////////////
  /*input = analogRead(A0);
  output = computePID(input);
  delay(100);*/
}

/*double computePID(double inp){
	currentTime = millis();
	elapsedTime = (double)(currentTime - previousTime);
	
	error = setPoint - inp; //determine the proportional error
	cumError += error*elapsedTime; //integral
	rateError = (error - lastError)/elapsedTime; //derivative
	
	double out = kp*error + ki*cumError + kd*rateError; //Creates the output for the PID controller\
	
	lastError = error; //logs the current error for the next iteration
	previousTime = currentTime; //Recursively logs the time for the difference in time
	
	return out;
}*/