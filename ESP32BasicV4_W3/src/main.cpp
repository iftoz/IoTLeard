//TUGAS Week 3 Training IOT Nusantech =================================
//TOMBOLUNTUK WRITE MEMORY BLM BERHASIL hehe
#include <Arduino.h>
#include <SPI.h>
#include <w25q64.hpp>
#include <Wire.h>

#define BH1750_ADD 0x23
#define BH1750_DATALEN 2
#define CSPIN 5
#define SCKPIN 18
#define MISO 19
#define MOSI 23
#define GETCHIPID 0x9F
#define LEN_ID 4
#define LED1 2
#define LED2 4
#define LED3 16
#define LED4 17

int PB = 15;
void BHReq(int address);
int BHGet(int address);
void blink();
void startspi();
void LEDswitch(int d);
byte buff[2];
unsigned short lux = 0;
unsigned char writePage[256]="";
unsigned char readPage[256]="";
byte chipid[4];
w25q64 spichip;
volatile bool x;
int lx;
char c;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  spichip.begin();
  spichip.getId(chipid);
  Serial.print("Chip ID : ");
  for (int i = 0; i < LEN_ID; i++)
  {
    Serial.print(chipid[i], HEX);
  }
  Serial.println();
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(PB, INPUT_PULLUP);
  // attachInterrupt(PB, blink, FALLING);
}

void loop()
{
  BHReq(BH1750_ADD);
  delay(10);
  if (BHGet(BH1750_ADD) == BH1750_DATALEN)
  {
    lux = (((unsigned short)buff[0] << 8) | (unsigned short)buff[1]) / 1.2;
    String str = "Nilai lux  = " + String(lux) + "lx";
    Serial.println(str);
  }
  delay(10);
   int w = digitalRead(PB);
  if (w == LOW)
  {
    blink();
  }
  startspi();
 }
void startspi()
{
    // READ DATA
  Serial.println("MULAI BACA");
  spichip.readPages(readPage, 0xffff, 1);
  for (int i = 0; i < 256; i++)
  {
    if (readPage[i] > 8 && readPage[i] < 127)
      Serial.print((char)readPage[i]);
      c = readPage[i];
  }
  
  Serial.print("isi c adalah = "); //========================BUG TRAP=======================
  Serial.println(c);
    int cint = (int)c;
  Serial.print("isi cint adalah = "); //========================BUG TRAP=======================
  Serial.println(cint);

  if (c = 65)
  {
    Serial.println();
    delay(1000);
    lx = (int)lux;
    Serial.print("NILAI lx Z "); //========================BUG TRAP=======================
    Serial.println(lx);
    LEDswitch(lx);
  }
  else
  {
     Serial.print("NILAI lx SSS ");
    LEDswitch(0);
  }
}

void blink()
{
  x = !x;
  int y = (int)x;
  Serial.print("x awal : ");
  Serial.println(x);
  Serial.print("y awal : ");
  Serial.println(y);
  switch (y)
  {
  case 1:
    // WRITE DATA
    memcpy(writePage, "A", sizeof("A"));
    spichip.erasePageSector(0xffff);
    spichip.pageWrite(writePage, 0xffff);    
    Serial.println("WRITE");
    break;

  case 0:
     memcpy(writePage, "S", sizeof("S"));
    spichip.erasePageSector(0xffff);
    spichip.pageWrite(writePage, 0xffff);
    Serial.println("ERASED");
    break;
  }
  delay(1000);
  Serial.print("y akhir : ");
  Serial.println(y);
  Serial.print("X akhir : ");
  Serial.println(x);
}

void LEDswitch(int d)
{
  if (d == 0)
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    delay(100);
    Serial.println("KONDISI 0");
  }
  else
  {
    if (d > 0 && d <= 250)
    {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      Serial.println("KONDISI 1");
    }

    else if (d > 250 && d <= 500)
    {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, LOW);
      Serial.println("KONDISI 2");
    }

    else if (d > 500 && d <= 750)
    {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      Serial.println("KONDISI 3");
    }
    else if (d > 750 && d <= 1000)
    {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      Serial.println("KONDISI 4");
    }
    else
    {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      Serial.println("KONDISI 5");
    }
    delay(100);
  }
}

int BHGet(int address)
{
  int i = 0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
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
