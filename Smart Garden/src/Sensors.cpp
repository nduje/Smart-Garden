#include "Sensors.h"

DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter(0x23);

SENSORS::SENSORS(){}
SENSORS::~SENSORS(){}

float humidity, temperature;

void SENSORS::DHT_init(){
  Serial.println(F("DHTxx test!"));
  dht.begin();
}

void SENSORS::BH1750_init(){
  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
  Serial.println(F("BH1750 test!"));
}

float SENSORS::readTemp() {
    temperature = dht.readTemperature();

    if(isnan(temperature)) {
        Serial.println("Failed to read temperature from DHT sensor!");
        return -1;
    }

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    return temperature;
}

float SENSORS::readHum() {
    humidity = dht.readHumidity();

    if(isnan(humidity)) {
        Serial.println("Failed to read humidity from DHT sensor!");
        return -1;
    }

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%");

    return humidity;
}

uint16_t SENSORS::readLight() {
    uint16_t lux = lightMeter.readLightLevel();

    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println(" lx");

    return lux;
}