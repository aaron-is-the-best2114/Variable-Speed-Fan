#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define ADS7830_ADDRESS 0x4b // I2C address of the ADS7830

int motorPin1 = 11; // Pin connected to Input 1 of L293D
int motorPin2 = 12; // Pin connected to Input 2 of L293D
int enablePin = 6; // Pin connected to Enable pin of L293D

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

unsigned long previousMillis = 0;
const long interval = 500;

void setup() {
  Wire.begin(); // Initialize I2C
  lcd.init(); // initialize the lcd
  lcd.backlight();
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
}

void loop() {
  int potValue = readADS7830(0); // Read value from channel 0 of ADS7830
  //Serial.println(potValue);
  int motorSpeed = map(potValue, 0, 255, 0, 255); // Map value to motor speed range
  analogWrite(enablePin, motorSpeed); // Set motor speed
  digitalWrite(motorPin1, HIGH); // Set motor direction
  digitalWrite(motorPin2, LOW);

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    if (potValue <= 120){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Fan Speed:0(MIN)");
    } else if (potValue >= 120 && potValue <= 180){
      int fanSpeed = 1;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Fan Speed: ");
      lcd.print(fanSpeed);
    } else if (potValue > 180 && potValue <= 200){
      int fanSpeed = 2;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Fan Speed: ");
      lcd.print(fanSpeed);
    } else if (potValue > 200 && potValue <= 220){
      int fanSpeed = 3;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Fan Speed: ");
      lcd.print(fanSpeed);
    } else if (potValue > 220 && potValue <= 240){
      int fanSpeed = 4;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Fan Speed: ");
      lcd.print(fanSpeed);
    } else if (potValue > 240 && potValue <= 255){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Fan Speed:5(MAX)");
    }
    //lcd.setCursor(0,-2);
    //lcd.print("Raw Output: ");
    //lcd.print(potValue);
  }
}

int readADS7830(byte channel) {
  Wire.beginTransmission(ADS7830_ADDRESS);
  Wire.write((channel << 4) | (1 << 2) | (1 << 3));
  Wire.endTransmission();
  
  Wire.requestFrom(ADS7830_ADDRESS, 1);
  
  if (Wire.available()) {
    return Wire.read();
  } else {
    return -1;
  }
}
