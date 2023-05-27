#include <M5Core2.h>
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor; //VL53L0X　"sensor"として操作することを宣言している。

//servo
#define SERVO_PIN 26
#define SERVO_CH 0
#define PMW_HZ 50
#define PMW_BIT 16
#define MAX 7800
#define MIN 1700

void setup() {
  M5.begin();
  Wire.begin();// I2C通信を開始する
  sensor.init();
  sensor.startContinuous();  //  連続測定を開始
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setTextSize(4);

  //servo
  ledcSetup(SERVO_CH, PMW_HZ, PMW_BIT);
  ledcAttachPin(SERVO_PIN, SERVO_CH);
  M5.Lcd.setBrightness(200);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextFont(7);
  M5.Lcd.setTextColor(GREEN);
}


void loop() {
  int distance = sensor.readRangeContinuousMillimeters(); //センサデータの取得(mm単位)
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print(distance);
  M5.Lcd.print("  [mm]  ");

  if(distance < 200){
    ledcWrite(0,13);
    delay(1000);
  }else{
    ledcWrite(0,0);
    delay(1000);
  }
  
}
