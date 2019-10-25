//Define the clock speed
#define F_CPU 16000000UL

//Included libraries and header files
#include <avr/io.h>
#include <util/delay.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "RoboClaw.h"
#include "SPI.h"
#include "mcp_can.h"

//See limitations of Arduino SoftwareSerial
SoftwareSerial serial(0,1);	
SoftwareSerial s1(10,11);
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
int spiCSPin = 10;
unsigned char raw;

MCP_CAN CAN(spiCSPin);

void setup() {
	//Open roboclaw serial ports
	//Serial.begin(38400);
	s1.begin(38400);
	//serial.begin(38400);
	roboclaw.begin(38400);
	pinMode(ledPin, OUTPUT);
	pinMode(potPin, INPUT);
	//setPoint = 4;
	threshold = 0.5;
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
	s1.listen();
	if(CAN_MSGAVAIL == CAN.checkReceive()) {
		CAN.readMsgBuf(&len, buf);
		unsigned long canId = CAN.getCanId();
	 
		val = analogRead(potPin);
		pos = map(val, 0, 1023, 0, 5);
		raw = buf[0];
		setPoint = map(raw, 0, 65535, 0, 5);
		digitalWrite(ledPin, HIGH);
	}
	serial.listen();
	if (pos >= (setPoint - threshold) && pos <= (setPoint + threshold)) {
		roboclaw.ForwardM1(address,0);
		Serial.print(pos);
		} else if (pos > (setPoint - threshold)) {
		roboclaw.ForwardM1(address, 70);
		Serial.print(pos);
		} else if (pos < (setPoint + threshold)) {
		roboclaw.BackwardM1(address, 50);
		Serial.print(pos);
		
	}
}

