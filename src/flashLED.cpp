#include <Arduino.h>
#include "flashLED.h"
const int ledPin1 = 2;

void flashLEDsuccess(){
    pinMode(ledPin1, OUTPUT);

    for(int i=0; i<3 ; i++){
        digitalWrite(ledPin1, HIGH);
        delay(500);
        digitalWrite(ledPin1,LOW);
        delay(500);
    }
}

void flashLEDfailure(){
    pinMode(ledPin1, OUTPUT);

    for(int i=0; i<2 ; i++){
        digitalWrite(ledPin1, HIGH);
        delay(2000);
        digitalWrite(ledPin1,LOW);
        delay(2000);
    }
}