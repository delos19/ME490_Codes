#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int potPin = A0;
int val = 0;
int pos = 0;
const int btn = 2;
const int led = 3;
int selector = 0;
boolean isPressed = false;
unsigned long buf[8] = {0,0,0,0,0,0,0,0};

LiquidCrystal_I2C lcd(0x27,16,2);  //I have used I2C scan program, so address is correct.

void setup() {
  
  lcd.init();
  lcd.backlight();
  lcd.home();
  Serial.begin(9600);
  pinMode(btn, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop ()
{
  if (digitalRead(btn) == LOW && isPressed == false ) //button is pressed AND this is the first digitalRead() that the button is pressed
  {
    isPressed = true;  //set to true, so this code will not run again until button released
    doSwitchStatement(); // a call to a separate function that performs the switch statement and subsequent evoked code

    selector++; // this is done after the doSwitchStatement(), so case 0 will be executed on the first button press 
    if (selector > 3) {
      selector = 0;
    }
    // selector = (selector+1) % 4;  // does the same, without if-statement
  } else if (digitalRead(btn) == HIGH)
  {
    isPressed = false; //button is released, variable reset
  }
}

void doSwitchStatement() {
  switch(selector) {
  case 0:
    digitalWrite(led, HIGH);
    lcd.clear();
    lcd.print("RPM Tuning");
    delay(250);
    doRun();
    // add a call to doExtraStuff() if you like
    break;
  case 1:
    digitalWrite(13, HIGH);
    lcd.clear();
    lcd.print("Fully Extended");
    delay(250);
    doExtend();
    break;
  case 2:
    digitalWrite(4, HIGH);
    lcd.clear();
    lcd.print("Fully Contracted");
    delay(250);
    doContract();
    break;
  case 3:
    digitalWrite(5, HIGH);
    lcd.clear();
    lcd.print("Boundary Demo");
    delay(250);
  }
}

void doRun(){
  val = analogRead(potPin);
  pos = map(val, 0, 1023, 0, 255);
  //buf[8] = {pos,0,0,0,0,0,0,0};
  //insert CAN send message here
  return;
}

void doExtend(){
  pos = 255;
  //buf[8] = {pos,0,0,0,0,0,0,0};
  //insert CAN send message here
  return;
}

void doContract(){
  pos = 0;
  //buf[8] = {pos,0,0,0,0,0,0,0};
  //insert CAN send message here
  return;
}

void doDemo(){
  for(int i = 0; i<=50; i++);
  pos = 0;
  //buf[8] = {pos,0,0,0,0,0,0,0};
  //insert CAN send message here
  delay(1000);
  pos = 255;
  //buf[8] = {pos,0,0,0,0,0,0,0};
  //insert CAN send message here
  delay(1000);
  return;
}


