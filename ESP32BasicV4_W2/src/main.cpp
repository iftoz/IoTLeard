//ADC+TUGAS====================
#include <Arduino.h>
#define ADCIN 34
#define LED1 2
#define LED2 4
#define LED3 5
#define LED4 18

int POT[5];
int POTAVG;
float v, t;
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
  for (int i = 0; i < 5; i++)
  {
    POT[i] = analogRead(ADCIN);
    delay(100);
    POTAVG = (POT[0] + POT[1] + POT[2] + POT[3] + POT[4]) / 5;
  }

  Serial.print("nilai ADC = ");
  Serial.println(POTAVG);
  v = ((float)POTAVG / 4095) * 3.3;
  String printv = "Tegangan = " + String(v) + "V";
  Serial.println(printv);
  t = (v / 3.3) * 100;
  String printt = "Suhu = " + String(t) + "C";
  Serial.println(printt);
  if (t < 10)
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
  }
  else if (t >= 10 && t < 20)
  {
    digitalWrite(LED2, HIGH);
    digitalWrite(LED1, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
  }
  else if (t >= 20 && t < 30)
  {
    digitalWrite(LED3, HIGH);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED4, LOW);
  }
  else
  {
    digitalWrite(LED4, HIGH);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  }

  delay(1000);
}