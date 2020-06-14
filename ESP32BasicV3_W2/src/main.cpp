#include <Arduino.h>
//Type conversion/casting, Bitwise, ADC=============

byte data[2];
int counter = 0;
float realdata;
unsigned dataShort;

void setup()
{
  Serial.begin(115200);
}

void loop()
{

  if (Serial.available())
  {
    data[counter] = Serial.read();
    counter++;
    if (counter > 1)
    {
      counter = 0;
      dataShort = (unsigned short)data[0] << 8;
      dataShort = dataShort | ((unsigned short)data[1]);
      realdata = (float)dataShort / 100.00;

      String print = "Nilai sensor : " + String(realdata);
      Serial.println(print);
    }
  }
}