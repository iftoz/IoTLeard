#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <SPI.h>
#include <DHT_U.h>

#define DHTPIN 5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float readtemp();
//sensor_t sensor;
//alt+shift+F
void setup()
{
    Serial.begin(115200);
    dht.begin();
}

void loop()
{
    float temp = readtemp();

    Serial.print("Suhu saat ini : ");
    Serial.println(temp);
    delay(5000);
}

float readtemp()
{
    return dht.readTemperature();
}
