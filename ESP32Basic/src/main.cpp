#include <Arduino.h>
#define LED 4
#define BTN 18
int kondisi = LOW;
void setup() 


{
  // put your setup code here, to run once:
pinMode(LED, OUTPUT);
pinMode(BTN, INPUT_PULLUP);

}

void loop()
 {
  // put your main code here, to run repeatedly:
if (digitalRead(BTN) == LOW)
{
  kondisi =! kondisi;
digitalWrite(LED, kondisi);
delay(2000);

}


}