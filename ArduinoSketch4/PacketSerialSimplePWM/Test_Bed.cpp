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
	
SoftwareSerial serial(10,11);				//Defines the SoftwareSerial class "serial"
Servo claw;						//Defines the servo class "claw"

//LED Pint and PinMode initializing of variables
int ledPin = 9;
float val = 0;
int valPerc = 0;
int potPin = A0;
float pos = 0;
float threshold = 1.0;
float setPoint = 0;
int spiCSPin = 10;
float raw;
int motor = 6;						//PWM pin is pin 6

MCP_CAN CAN(spiCSPin);					//Defines the class CAN as the can bus name and set it to transcieve data via SPI on the spiCSPin == pin 10

void setup() {
	claw.attach(motor);				//Defines the servo class claw
	serial.begin(38400);				//Begins the serial connection
	pinMode(ledPin, OUTPUT);			//Initializes the ledPin to be an output
	pinMode(potPin, INPUT);				//Defines the potentiometer pin as an input
	pinMode(motor,OUTPUT);				//Defines the pin connecting the PCB to the Roboclaw (PWM channel, in the servo class claw) as output
	threshold = 0.35;				//Sets the threshold value to read in between
	while (CAN_OK != CAN.begin(CAN_1000KBPS)) {	//Initializes the CAN connection at 1 Mbps
		Serial.println("CAN BUS Init Failed");
		delay(100);
	}
	Serial.println("CAN BUS Init OK!");		//Feedback that the CAN bus has been initialized (Requires 120 ohm terminating resistor)

	CAN.init_Mask(0,0,0xFF);			//Sets mask for CAN to read
	CAN.init_Mask(1,0,0xFF);
	CAN.init_Filt(0,0,0x520);			//Filters for channel 520

	claw.writeMicroseconds(2300);			//Sets the actuator to go full contraction on startup
	delay(7000);
}
 
void loop() {
	digitalWrite(ledPin, LOW);			//Set integrated PCB indicator LCD to low
	unsigned char len = 0;				//Initialized the length indicator
	unsigned char buf[8];				//Initialize the buffer array of size 8
	if(CAN_MSGAVAIL == CAN.checkReceive()) {	//Run the check on the CAN bus line. It verifies that signal is being received
		CAN.readMsgBuf(&len, buf);		//Saves the length of the data to integer  'len' and the data array to the buffer array 'buf'
		unsigned long canId = CAN.getCanId();	//Reads each CAN address and assigns it to the unsigned long val canId
		val = analogRead(potPin);		//Reads the voltage of the potentiometer and assigns it a value between 0 and 1023
		pos = map(val, 0, 1023, 0, 8);		//Gets the position of the actuator by mapping the value read from the potentiometer between 0 in to 8 in
		raw = buf[0];				//Stores the value at indices 0 of the buffer array to the integer 'Raw' 
		setPoint = map(raw, 0, 255, 0, 5);	//Remaps the read value from the buffer indices to read as a length that maximizes at the maximum actuation length of the system
	}
	
							// TODO: Replace Bang-Bang control loop with PID

	//Begin Bang-Bang control loop
	if (pos >= (setPoint - threshold) && pos <= (setPoint + threshold)) { //If read length is inside the threshold, send 1500 == STOP
		claw.writeMicroseconds(1500);
		delay(50);
		Serial.print(pos);
		digitalWrite(ledPin, HIGH);
	} else if (pos > (setPoint - threshold)) {	//If it is greater than the setpoint, go backwards at full speed
		claw.writeMicroseconds(2300);
		delay(50);
		Serial.print(pos);
	} else if (pos < (setPoint + threshold)) {	//If it is greater than the setpoint, go forwards at full speed
		claw.writeMicroseconds(1000);
		delay(50);
		Serial.print(pos);
	}
}

