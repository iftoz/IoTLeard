#include <Arduino.h>
//Tugas mingu pertama menyalakan LED via terminal input use alt+shift+f to steady program line
#define LED1 2
#define LED2 5
#define LED3 18
#define LED4 19
void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  Serial.begin(115200);
  delay(500);
}

void loop()
{
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  if (Serial.available())
  {

    char data = Serial.read();
    Serial.println();
    Serial.print("Datamu adalah : ");
    Serial.println(data);
    int dataint = data;
    Serial.print("Dataint : ");
    Serial.println(dataint);
    switch (dataint)
    {
    case 49:
      digitalWrite(LED1, HIGH);
      delay(2000);
      break;
    case 50:
      digitalWrite(LED2, HIGH);
      delay(2000);
      break;
    case 51:
      digitalWrite(LED3, HIGH);
      delay(2000);
      break;
    case 52:
      digitalWrite(LED4, HIGH);
      delay(2000);
      break;

    default:

      break;
    }
  }
}