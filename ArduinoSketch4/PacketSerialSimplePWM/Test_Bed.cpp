//Define the clock speed
#define F_CPU 16000000UL

//Included libraries and header files
#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "RoboClaw.h"
#include "SPI.h"
#include "mcp_can.h"

//See limitations of Arduino SoftwareSerial
SoftwareSerial serial(0,1);	
RoboClaw roboclaw = RoboClaw(&serial,10000);
//RoboClaw roboclaw(Serial,10000);
#define address 0x80

//LED Pint and PinMode initializing of variables
int ledPin = 9;
int val = 0;
int valPerc = 0;
int potPin = A0;
float pos = 0;
int threshold = 1;
int setPoint = 0;
const int spiCSPin = 10;

MCP_CAN CAN(spiCSPin);

void setup() {
  //Open roboclaw serial ports
  Serial.begin(115200);
  roboclaw.begin(38400);
  pinMode(ledPin, OUTPUT);
  pinMode(potPin, INPUT);
  setPoint = 4;
  threshold = 0.1;
  //setPoint = 0;
}
 
void loop() {
	/*val = analogRead(potPin);
	pos = map(val, 0, 1023, 0, 5);
	roboclaw.BackwardM1(address, 120);
	delay(5000);
	if (pos <= 3.5){
		digitalWrite(ledPin, LOW);
	}
	if (pos > 3.5){
		digitalWrite(ledPin, HIGH);
	}   
	delay(5000);                 
	val = analogRead(potPin);
	pos = map(val, 0, 1023, 0, 5);
	delay(5000);
	roboclaw.ForwardM1(address	, 50);
	delay(5000);
	if (pos <= 3.5){
		digitalWrite(ledPin, LOW);
	}
	if (pos > 3.5){
		digitalWrite(ledPin, HIGH);
	}
	delay(5000);
	
/*	
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
*/
  
  ////////////////////////////////////////////////////////////////////////////////
  
 val = analogRead(potPin);
  pos = map(val, 0, 1023, 0, 5);
  if (pos >= (setPoint - threshold) && pos <= (setPoint + threshold)) {
	  roboclaw.ForwardM1(address,0);
	  Serial.print(pos);
	}
  else if (pos > (setPoint - threshold)){
		roboclaw.ForwardM1(address, 70);
		Serial.print(pos);
	}
  else if (pos < (setPoint + threshold)){
		roboclaw.BackwardM1(address, 50);
		Serial.print(pos);
	}
}

