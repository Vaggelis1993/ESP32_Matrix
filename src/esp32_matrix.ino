//Libraries
#include <Arduino.h>
#include <RGBmatrixPanel.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

// Tabs
#include "time.h"
#include"matrix_print.h"
#include"servers.h"

/*Wiring
**********************************
  DS18B20 pin   --> 4
  ------------------------------
  //Matrix pins   --> ESP32_Pins
  -------------------------------
  CLK   --> 15
  OE    --> 33
  LAT   --> 32
  A     --> 12
  B     --> 16
  C     --> 17
  D     --> 18
  R1    --> 25
  G1    --> 26
  B1    --> 27
  R2    --> 21
  G2    --> 22
  B2    --> 5
*/

void setup() {
  Serial.begin(115200);
  WiFi_Connection();
  NTP_Server();
  AsyncWebServer1();
  AsyncElegantOTA.begin(&Server);
  matrix.begin();
  Server.begin();
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();
  matrixprint();
}
