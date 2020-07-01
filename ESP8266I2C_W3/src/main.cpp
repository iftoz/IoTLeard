//I2C Read LDR for TUGAS W3 Support Cuz lack of BH1750 Sensor haha
#include <Arduino.h>
#include <Wire.h>

#define ADCIN 0
#define SENSORADD 0x23
#define SENSOR_DATALEN 2

void REQEVENT();
void RCVEVENT();
int datacount;
void setup()
{
  pinMode(ADCIN, INPUT);
  Serial.begin(9600);
  Wire.begin(SENSORADD);
 Wire.onRequest(REQEVENT);
 Wire.onReceive(RCVEVENT);
}

void REQEVENT()
{
  byte x = Wire.read();
  while (x == 0x10)
  {
    int a = analogRead(ADCIN);
    Serial.print("Nilai ADC : ");
    Serial.println(a);
    int b = (map(a, 0, 1023, 0, 65536)) * 1.2;
    int c1 = (bit(b) & 0b1111111100000000) >> 8;
    int c2 = (bit(b) & 0b0000000011111111);
    Serial.print("Nilai Lux : ");
    Serial.println(b);
    Serial.println(c1);
    Serial.println(c2);
    Wire.beginTransmission(SENSORADD);
    Wire.write(c1);
    Wire.write(c2);
    Wire.endTransmission();
  }
  Serial.println("RCV");

// void REQEVENT()
// {
//   unsigned short respon;
//   Wire.write(respon);
// }
void loop()
{
  //======================
  int a = analogRead(ADCIN);
    Serial.print("Nilai ADC : ");
    Serial.println(a);
    int b = (map(a, 0, 1023, 0 , 65536)) * 1.2;
    int c1 = (bit(b) & 0b1111111100000000) >> 8;
    int c2 = (bit(b) & 0b0000000011111111);
    Serial.print("Nilai Lux : ");
    Serial.println(b);
    Serial.println(c1);
    Serial.println(c2);
    Wire.beginTransmission(SENSORADD);
    Wire.write(c1);
    Wire.write(c2);
    Wire.endTransmission();
  //======================
  delay(2000);
}