#include <Arduino.h>
#include <SPI.h>
#include <w25q64.hpp>

#define CSPIN 5
#define SCKPIN 18
#define MISO 19
#define MOSI 23
#define GETCHIPID 0x9F
#define LEN_ID 4

unsigned char writePage[256];
unsigned char readPage[256];
byte chipid[4];
w25q64 spichip;

void setup()
{
  Serial.begin(9600);
  spichip.begin();
  spichip.getId(chipid);
  Serial.print("Chip ID : ");
  for (int i = 0; i < LEN_ID; i++)
  {
    Serial.print(chipid[i], HEX);
  }
  Serial.println();

  //TEST WRITE DATA
  memcpy(writePage, "TRAINING MIFTAH", sizeof("TRAINING MIFTAH"));
  spichip.erasePageSector(0xffff);
  spichip.pageWrite(writePage, 0xffff);
  Serial.println("SELESAI NULIS");
  delay(1000); 

  //TEST READ DATA
  Serial.println("MULAI BACA");
  spichip.readPages(readPage, 0xffff, 1);
  for (int i = 0; i < 256; i++)
  {
    if (readPage[i] > 8 && readPage[i] < 127)
      Serial.print((char)readPage[1]);
  }
  Serial.println();
}

void loop()
{
}
