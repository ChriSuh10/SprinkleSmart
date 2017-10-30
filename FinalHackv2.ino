
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <Servo.h>

// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

#define WHITE 0x7
Servo myServo;
int pos = 1500;
int threshold = 3;
int highAtTwelve = 0;

void setup() {
  myServo.attach(9);
  Serial.begin(9600);
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:

  int time = millis();
  lcd.print("SprinkleSmart");
  time = millis() - time;
  //Serial.print("Took "); Serial.print(time); Serial.println(" ms");
  lcd.setBacklight(WHITE);
  highAtTwelve = digitalRead(12);
}

void loop() {
  lcd.setCursor(0, 1); // set the cursor to column 0, line 1 
  int numSecs = millis()/1000;
  //lcd.print(numSecs); // print the number of seconds since reset:

  
  if (highAtTwelve == HIGH) {
    lcd.clear();
    lcd.print("SprinkleSmart");
    lcd.setCursor(0, 1);
    lcd.print("ON");
    for (int k=0; k<5; k++) {
      for (int i=0; i<7; i++)
        spray();
      for (int i=0; i<30; i++)
        retract();
    }
  }

  else {
  lcd.clear();
  lcd.print("SprinkleSmart");
  lcd.setCursor(0, 1);
  lcd.print("OFF");
  }
  highAtTwelve = digitalRead(12);
}

void spray() {
  myServo.writeMicroseconds(pos+500);
  delay(80);
  myServo.writeMicroseconds(pos);
  delay(150);
}

void retract() {
  myServo.writeMicroseconds(pos-500);
  delay(25);
  myServo.writeMicroseconds(pos);
  delay(25);
}
