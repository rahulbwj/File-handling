#include <WiFi.h>
#include <SPIFFS.h>
#include <WebServer.h>
#include "setupWifi.h"

const char* ssid = "ESPWIFI";
const char* password = "testing1234";

WebServer server(80); // HTTP server on port 80

void setupWifi() {  
  WiFi.softAP(ssid, password);
  Serial.println("Access Point started");
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", "<h1>ESP32 SPIFFS Web Server</h1><p><a href=\"/list\">List Files</a></p>");
  });

  server.on("/list", HTTP_GET, []() {
    String path = "/";
    File root = SPIFFS.open(path);
    File file = root.openNextFile();
    
    String fileList = "<h1>File List</h1><ul>";
    while (file) {
      fileList += "<li><a href=\"/download";
      fileList += file.name();
      fileList += "\">";
      fileList += file.name();
      fileList += "</a></li>";
      file = root.openNextFile();
    }
    fileList += "</ul>";
    server.send(200, "text/html", fileList);
  });

  server.on("/download", HTTP_GET, []() {
    String path = server.uri();
    path = path.substring(10); // Remove "/download" from the path
    File file = SPIFFS.open(path);
    
    if (!file) {
      server.send(404, "text/plain", "File Not Found");
      return;
    }

    server.streamFile(file, "application/octet-stream");
    file.close();
  });

  server.begin();

  while(true){
    server.handleClient();
  }
}
