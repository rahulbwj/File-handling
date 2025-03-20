#include <Arduino.h>
#include <SPI.h>
#include <SPIFFS.h>
#include <FS.h>
#include "listFiles.h"
#include "parseCSVLine.h"
#include "format.h"
#include "sizeSP.h"

const size_t chunkSize = 5 * 1024;
size_t totalChunks;  
const int input_pin = 0;
char buffer[chunkSize + 1]; 

void setup() {
  Serial.begin(115200);
  pinMode(input_pin, INPUT_PULLUP);

  if (!SPIFFS.begin(true)) {
    Serial.println("Failed to mount file system");
    return;
  }
  Serial.println("Successfully mounted file system");

  File largeFile = SPIFFS.open("/data.csv", "r");
  if (!largeFile) {
    Serial.println("Failed to open main file for reading");
    return;
  }

  size_t fileSize = largeFile.size();
  Serial.println("Main file size is: ");
  Serial.println(fileSize);
  totalChunks = (fileSize + chunkSize - 1) / chunkSize; // Uncomment this line if totalChunks is a dynamic value
  Serial.println("Total number of sub files are: ");
  Serial.println(totalChunks);

  largeFile.close();

  largeFile = SPIFFS.open("/data.csv", "r");
  if (!largeFile){
    Serial.println("Failed to reopen main file for reading");
    return;
  }

  size_t chunkIndex = 0;
  size_t currentSize = 0;
  size_t writtenDataSize = 0;

  while (largeFile.available()) {     // executes for every subfile created
    String SubFile = "/sub" + String(chunkIndex) + ".csv"; // Create SubFile name inside the loop
    File smallFile = SPIFFS.open(SubFile, "w"); // Open subfile inside the loop
    if (!smallFile) {
      Serial.println("Failed to create sub file " + SubFile);
      return;
    }

    while (largeFile.available()) {   
      size_t bytesRead = largeFile.readBytesUntil('\n', buffer, sizeof(buffer) - 1);
      buffer[bytesRead] = '\0'; 
      size_t lineSize = bytesRead + 1; // +1 for the newline character

      if (currentSize + lineSize > chunkSize) {
        break; //Exit inner while loop
      }

      smallFile.write((const uint8_t*)buffer, lineSize - 1);
      smallFile.write('\n');
      currentSize += lineSize;
      writtenDataSize += lineSize;
    }

    smallFile.close();
    Serial.println("Created " + SubFile);

    // Deleting the portion from the main file
    largeFile.seek(writtenDataSize);
    File tempFile = SPIFFS.open("/temp.csv", "w");
    if (!tempFile) {
      Serial.println("Failed to create temp file");
      return;
    }

    while (largeFile.available()) {
      tempFile.write(largeFile.read());
    }
    tempFile.close();
    largeFile.close();
    SPIFFS.remove("/data.csv");
    SPIFFS.rename("/temp.csv", "/data.csv");

    largeFile = SPIFFS.open("/data.csv", "r+");
    if (!largeFile) {
      Serial.println("Failed to reopen main file for reading");
      return;
    }

    chunkIndex++;
    currentSize = 0;
    writtenDataSize = 0;
  }

  largeFile.close();
  Serial.println("All files closed successfully");

  listFiles(SPIFFS, "/", 0);  // function to list all the files present in SPIFFS 
  sizeRemaining();            // function to check how much space in SPIFFS is remaining
}

void loop() {
}


// 16-08-2024 | Rahul
