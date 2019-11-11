//Define the clock speed
#define F_CPU 16000000UL

//Included libraries and header files
#include <avr/io.h>
#include <util/delay.h>
#include "Servo.h"
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "RoboClaw.h"
#include "SPI.h"
#include "mcp_can.h"

//See limitations of Arduino SoftwareSerial
//SoftwareSerial serial(0,1);	
SoftwareSerial serial(10,11);
//RoboClaw roboclaw = RoboClaw(&serial,10000);
//RoboClaw roboclaw(Serial,10000);
#define address 0x80

Servo claw;

//LED Pint and PinMode initializing of variables
int ledPin = 9;
float val = 0;
int valPerc = 0;
int potPin = A0;
float pos = 0;
float threshold = 1.0;
float setPoint = 0;
int spiCSPin = 10;
unsigned char raw;
int motor = 6;

MCP_CAN CAN(spiCSPin);

void setup() {
	//Open roboclaw serial ports
	//Serial.begin(38400);
	//s1.begin(38400);
	//roboclaw.begin(38400);
	claw.attach(motor);
	serial.begin(38400);
	pinMode(ledPin, OUTPUT);
	pinMode(potPin, INPUT);
	pinMode(motor,OUTPUT);
	threshold = 0.35;
	while (CAN_OK != CAN.begin(CAN_500KBPS)) {
		Serial.println("CAN BUS Init Failed");
		delay(100);
	}
	Serial.println("CAN BUS Init OK!");
	setPoint = 0;
}
 
void loop() {
	digitalWrite(ledPin, LOW);
	unsigned char len = 0;
	unsigned char buf[8];
	if(CAN_MSGAVAIL == CAN.checkReceive()) {
		CAN.readMsgBuf(&len, buf);
		unsigned long canId = CAN.getCanId();
	 
		val = analogRead(potPin);
		pos = map(val, 0, 1023, 0, 5);
		raw = buf[0];
		setPoint = map(raw, 0, 65535, 0, 5);
	}
	//val = analogRead(potPin);
	//pos = map(val, 0, 1023, 0, 5);
	//setPoint = 2.4;
	if (pos >= (setPoint - threshold) && pos <= (setPoint + threshold)) {
		claw.writeMicroseconds(1500);
		delay(50);
		Serial.print(pos);
		digitalWrite(ledPin, HIGH);
	} else if (pos > (setPoint - threshold)) {
		claw.writeMicroseconds(1750);
		delay(50);
		Serial.print(pos);
	} else if (pos < (setPoint + threshold)) {
		claw.writeMicroseconds(1250);
		delay(50);
		Serial.print(pos);
		
	}
}

