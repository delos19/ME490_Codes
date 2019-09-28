/*Begining of Auto generated code by Atmel studio */
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

//Includes required to use Roboclaw library
#include <SoftwareSerial.h>
#include "RoboClaw.h"

//See limitations of Arduino SoftwareSerial
SoftwareSerial serial(0,1);
RoboClaw roboclaw = RoboClaw(&serial,10000);
//RoboClaw roboclaw(Serial,10000);
#define address 0x80

//LED Pint and PinMode initializing of variables
int ledPin = 9;

void setup() {
	//Open roboclaw serial ports
	roboclaw.begin(38400);
	//Set LED pin as an output
	pinMode(ledPin, OUTPUT);
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
