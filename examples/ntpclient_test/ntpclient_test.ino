#include <ESP8266WiFi.h>
#include <ntpclient.h>
#include <PrintEx.h>
#include <TimeLib.h>
#include <WiFiUdp.h>

#include "ssid-info.h"

static PrintEx serial = Serial;

static ntp_client ntp(std::unique_ptr<UDP>(new WiFiUDP()));

void setup() {
  Serial.begin(9600);
  
  serial.printf("Connecting to: %s\n", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    serial.print(".");
  }

  serial.print(" connected\n");
  serial.printf("Address: %s\n", WiFi.localIP().toString().c_str());
  Serial.println("waiting for sync");

  setSyncProvider([]() { return ntp.get_time(); });
  while(timeStatus() == timeNotSet)
    delay(100);
}

static time_t prev_time = 0;

void loop() {  
  if(now() != prev_time) {
    prev_time = now();
    serial.printf("%d:%02d:%02d %02d-%02d-%04d\n",
      hour(),
      minute(),
      second(),
      day(),
      month(),
      year());
  }
}

