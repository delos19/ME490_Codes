/*Begining of Auto generated code by Atmel studio */
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

//See BareMinimum example for a list of library functions

//Includes required to use Roboclaw library
#include <SoftwareSerial.h>
#include "RoboClaw.h"
//#include "BMSerial.h"
//Beginning of Auto generated function prototypes by Atmel Studio
//End of Auto generated function prototypes by Atmel Studio

//See limitations of Arduino SoftwareSerial
SoftwareSerial serial(0,1);	
RoboClaw roboclaw = RoboClaw(&serial,10000);
//RoboClaw roboclaw(Serial,10000);
#define address 0x80

//LED Pint and PinMode initializing of variables
int ledPin = 9;
int val = 0;
int valPerc = 0;
int potPin = A2;
double pos = 0;
//int setPoint = 0;
//float threshold = 0;

//PID Constants
//double kp = 2;
//double ki = 5;
//double kd = 1;

//unsigned long currentTime, previousTime;
//double elapsedTime;
//double error;
//double lastError;
//double input, output, setPoint;
//double cumError, rateError;


void setup() {
  //Open roboclaw serial ports
  roboclaw.begin(38400);
  //Serial.begin(38400);
  pinMode(ledPin, OUTPUT);
  //setPoint = 5;
  
  //threshold = 0.5;
  //setPoint = 0;
}
 
void loop() {
	
  roboclaw.ForwardM1(address,120); //start Motor1 forward at half speed
  digitalWrite(ledPin, HIGH);
  delay(5000);

  roboclaw.BackwardM1(address,120);
  digitalWrite(ledPin, LOW);
  delay(5000);

  roboclaw.ForwardM1(address,96); //start Motor1 forward at half speed
  digitalWrite(ledPin, HIGH);
  delay(5000);

  roboclaw.BackwardM1(address,32);
  digitalWrite(ledPin, LOW);
  delay(5000);
}
  
  ////////////////////////////////////////////////////////////////////////////////
  
  /*val = analogRead(potPin);
  pos = map(val, 0, 1023, 0, 8);
  if (pos >= (setPoint - threshold) && pos <= (setPoint + threshold)) {
	  roboclaw.BackwardM1(address,0);
	}
  else if (pos > (setPoint - threshold)){
		roboclaw.BackwardM1(address, 64);
	}
  else if (pos < (setPoint + threshold)){
		roboclaw.ForwardM1(address, 64);
	}
}*/

  
  ///////////////////////////////////////////////////////////////////////////////
  
  /*val = digitalRead(potPin); //Read the hall effect sensor
  
  if (val == HIGH) { 
	  roboclaw.BackwardM1(address,64);
	  delay(10);
	  }
  else { 
	  roboclaw.ForwardM1(address,64);
	  delay(10);
  }
  */
  
  ///////////////////////////////////////////////////////////////////////////////

  /*input = analogRead(A2);
  output = computePID(input);
   pos = map(output, 0, 1023, 0, 8);
   if (pos >= (setPoint - threshold) && pos <= (setPoint + threshold)) {
	   roboclaw.BackwardM1(address,0);
   }
   else if (pos > (setPoint - threshold)){
	   roboclaw.BackwardM1(address, 64);
   }
   else if (pos < (setPoint + threshold)){
	   roboclaw.ForwardM1(address, 64);
   }
  delay(100);
}

double computePID(double inp){
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