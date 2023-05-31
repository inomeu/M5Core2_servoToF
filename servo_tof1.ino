#include <M5Core2.h>
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor; //VL53L0X　"sensor"として操作することを宣言している。

//servo
#define SERVO_PIN 26
//PortB
//#define SERVO_CH 0
//#define PMW_HZ 50
//#define PMW_BIT 16
//#define MAX 7800
//#define MIN 1700
#define SERVO_MIN_ANGLE 0
#define SERVO_MAX_ANGLE 90

void setup() {
  M5.begin();
  Serial.begin(115200);
  Wire.begin();
  sensor.setAddress(0x29);
  sensor.setTimeout(500);
  if (!sensor.init()) {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  sensor.startContinuous();

  //servo
  ledcSetup(0, 50, 16);
  ledcAttachPin(SERVO_PIN, 0);
//  M5.Lcd.setBrightness(200);
//  M5.Lcd.setTextSize(2);
//  M5.Lcd.setTextFont(7);
//  M5.Lcd.setTextColor(GREEN);
}


void loop() {
  int distance=0;
  distance = sensor.readRangeContinuousMillimeters();
  Serial.print(distance);
  if (sensor.timeoutOccurred()) {
    Serial.print(" TIMEOUT");
  }
  Serial.println();

  int angle = map(distance, 5, 50, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);
    ledcWrite(0, angle);
}
