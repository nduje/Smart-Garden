#ifndef Calculation_h
#define Calculation_h

#include <math.h>
#include <time.h>
#include <stdlib.h>

int calculateTime(float temp, float hum) {
    int calculatedTime = floor((100/temp) * 0.9 + hum * 0.1) * 10;    
    
    return calculatedTime;
}

int calculateCurrentTime() {
    return (int)(millis() / 1000);
}

uint16_t calculateRandomLight() {
    srand(millis());

    int randomLight = rand() % 50 + 90;

    Serial.print("Light: ");
    Serial.print(randomLight);
    Serial.println(" lx");

    return randomLight;
}

#endif