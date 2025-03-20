#include <Arduino.h>
#include "sizeSP.h"
#include <SPIFFS.h>
#include <SPI.h>

void sizeRemaining(){
    size_t totalBytes = SPIFFS.totalBytes();
    size_t usedBytes = SPIFFS.usedBytes();

    Serial.printf("Total SPIFFS space: %d bytes\n", totalBytes);
    Serial.printf("Used SPIFFS space: %d bytes\n", usedBytes);
    Serial.printf("Available SPIFFS space: %d bytes\n", totalBytes - usedBytes);
}