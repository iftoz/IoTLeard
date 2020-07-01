#include <Arduino.h>
#include <SPI.h>

#define CSPIN 5
#define SCKPIN 18
#define MISO 19
#define MOSI 23

#define GETCHIPID 0x9F
#define LEN_ID 4

byte chipid[4];

void chipInit();
void chipGetID();
void setup()
{
  Serial.begin(9600);
  chipInit();
  chipGetID();
}

void loop()
{
}

void chipInit()
{
  pinMode(CSPIN, OUTPUT);
  SPI.begin(SCKPIN, MISO, MOSI, CSPIN);
  digitalWrite(CSPIN, HIGH);
}
void chipGetID()
{
  digitalWrite(CSPIN, LOW);
  SPI.transfer(GETCHIPID);
  //Recieve ID
  for (int i = 0; i < LEN_ID; i++)
  {
    chipid[i] = SPI.transfer(0);
  }
  pinMode(CSPIN, HIGH);
  Serial.print("CHIPID : ");
  for (int i = 0; i < LEN_ID; i++)
  {
    Serial.print(chipid[i], HEX);
  }
  Serial.println();
} 