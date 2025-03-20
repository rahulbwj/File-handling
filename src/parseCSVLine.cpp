#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <SPIFFS.h>
#include "parseCSVLine.h"

String col1;
String col2;
String col3;
String col4;

void parseCSVLine(String line) {
    int commaIndex1 = line.indexOf(',');
    int commaIndex2 = line.indexOf(',', commaIndex1 + 1);
    int commaIndex3 = line.indexOf(',', commaIndex2 + 1);
    int commaIndex4 = line.indexOf(',', commaIndex3 + 1);

    String col1 = line.substring(0, commaIndex1);
    String col2 = line.substring(commaIndex1 + 1, commaIndex2);
    String col3 = line.substring(commaIndex2 + 1, commaIndex3);
    String col4 = line.substring(commaIndex3 + 1, commaIndex4);

    Serial.println("Column 1: " + col1);
    Serial.println("Column 2: " + col2);
    Serial.println("Column 3: " + col3);
    Serial.println("Column 4: " + col4);
    Serial.println();
}