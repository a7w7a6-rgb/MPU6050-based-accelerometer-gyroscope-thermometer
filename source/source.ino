#include <Wire.h>
#include <SPI.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

#define TFT_CS   10
#define TFT_DC   9
Adafruit_ILI9341 tft(TFT_CS, TFT_DC);

#define WIDTH 320
#define HEIGHT 240

void setup(void) {
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
pinMode(9,OUTPUT);
pinMode(4,OUTPUT);
delay(100);

Serial.begin(9600);
Wire.begin(10000);
mpu.begin();

tft.begin();
tft.setRotation(1);
tft.setTextSize(2);
tft.setTextColor(0xFFFF, 0x0000);
tft.setCursor(0,0);
tft.fillRect(0,0,320,240,0x0000);
tft.setCursor(0,20);
tft.write(" X Deg/S:");
tft.setCursor(0,65);
tft.write(" Y Deg/S:");
tft.setCursor(0,110);
tft.write(" Z Deg/S:");
tft.setCursor(150,20);
tft.write(" X Speed:");
tft.setCursor(150,65);
tft.write(" Y Speed:");
tft.setCursor(150,110);
tft.write(" Z Speed:");
tft.setCursor(150,155);
tft.write(" Temp C:");

tft.setTextSize(2);
tft.setTextColor(0x001F, 0x0000);
tft.setCursor(0,155);
tft.write(" MPU Sens ");
tft.setCursor(0,175);
tft.write(" Ver 1.2.2");

tft.drawRect(0, 20, 120, 40, 0xFFFF);
tft.drawRect(0, 65, 120, 40, 0xFFFF);
tft.drawRect(0, 110, 120, 40, 0xFFFF);

tft.drawRect(150, 20, 120, 40, 0xFFFF);
tft.drawRect(150, 65, 120, 40, 0xFFFF);
tft.drawRect(150, 110, 120, 40, 0xFFFF);

tft.drawRect(150, 155, 120, 40, 0xFFFF);
}

void loop() {

sensors_event_t a, g, temp;
mpu.getEvent(&a, &g, &temp);

float gyroX_deg = g.gyro.x * 180.0 / PI;
float gyroY_deg = g.gyro.y * 180.0 / PI;
float gyroZ_deg = g.gyro.z * 180.0 / PI;

tft.setTextColor(0xFFFF, 0x0000);

tft.setCursor(155,40);
tft.print(a.acceleration.x - 10.04);
tft.setCursor(155,85);
tft.print(a.acceleration.y + 3.86);
tft.setCursor(155,130);
tft.print(a.acceleration.z - 2.71);

tft.setCursor(5,40);
tft.print(gyroX_deg + 3.87);
tft.setCursor(5,85);
tft.print(gyroY_deg + 19.98);
tft.setCursor(5,130);
tft.print(gyroZ_deg + 1.93);
tft.setCursor(155,175);
tft.print(temp.temperature);

tft.fillCircle(300, 230, 2, 0xF800);
delay(100);
tft.fillCircle(300, 230, 2, 0x0000);
delay(100);
}

