#include <Arduino.h>
#include <SPIFFS.h>
#include <FS.h>
#include "format.h"
#include "flashLED.h"

void format(){
    Serial.println("Beginning format ");
    bool formatted = SPIFFS.format();
    if(formatted){
        Serial.println("Successfully formatted");
        flashLEDsuccess();          // 3 short flashes
    }
    else{
        Serial.println("Error in formatting");
        flashLEDfailure();          //2 long flashes
    }
}
