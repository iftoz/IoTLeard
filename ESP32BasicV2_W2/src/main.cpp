// Array, Pointer ====================================

#include <Arduino.h>
int temp[3];
int templen;
int tempAVG;
int *pointer1, *pointer2, *pointer3;

void setup()
{
  Serial.begin(115200);
  templen = sizeof(temp) / sizeof(temp[0]);
  pointer1 = &temp[0];
  pointer2 = &temp[1];
  pointer3 = &temp[2];

  Serial.print("alamat temp1 ");
  Serial.println((unsigned int)pointer1);

  Serial.print("alamat temp2 ");
  Serial.println((unsigned int)pointer2);

  Serial.print("alamat temp3 ");
  Serial.println((unsigned int)pointer3);
}

void loop()
{
  for (int i = 0; i < templen; i++)
  {
    temp[i] = random(20, 30);
  }
  tempAVG = (*pointer1 + *pointer2 + *pointer3) / templen;
  Serial.print("SuhuRata2 : ");
  Serial.println(tempAVG);
  delay(3000);
}