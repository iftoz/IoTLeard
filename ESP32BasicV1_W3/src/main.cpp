#include <Arduino.h>
#include <Wire.h>
#define BH1750_ADD 0x23  //alamat i2c cek datasheet atau st manual kalau pakai master slave
#define BH1750_DATALEN 2 //panjang data yg akan diterima

void BHReq(int address); //input adress = pada fungsi void loop
int BHGet(int address);

byte buff[2];
unsigned short lux = 0;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
}

void loop()
{
  BHReq(BH1750_ADD);
  delay(200);
  if (BHGet(BH1750_ADD) == BH1750_DATALEN)
  {
    lux = (((unsigned short)buff[0] << 8) | (unsigned short)buff[1]) / 1.2;
    String str = "Nilai lux  = " + String(lux) + "lx";
    Serial.println(str);
  }
  delay(1000);
}

int BHGet(int address)
{
  int i = 0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2); //jawaaban 2byte
  while (Wire.available())
  {
    buff[i] = Wire.read();
    i++;
  }
  Wire.endTransmission();

  return i;
}

void BHReq(int address)
{
  Wire.beginTransmission(address);
  Wire.write(0x10);
  Wire.endTransmission();
}