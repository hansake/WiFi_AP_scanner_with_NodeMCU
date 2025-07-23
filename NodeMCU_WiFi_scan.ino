// NodeMCU_WiFi_scan.ino
//
// Copied from: https://arduino-esp8266.readthedocs.io/en/2.5.2/esp8266wifi/scan-examples.html#id1
// Board: NodeMCU 1.0 (ESP-12E Module)
//
#include "ESP8266WiFi.h"

const char compile_date[] = __FILE__ ": "  __DATE__ " " __TIME__;

#define BLINK_PERIOD 250
long lastBlinkMillis;
boolean ledState;

#define SCAN_PERIOD 5000
long lastScanMillis;


void setup()
 {
  Serial.begin(115200);
  Serial.println();

  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(500);
  Serial.println();
  Serial.println("--------------------------------------------");
  Serial.println("Starting NodeMCU WiFi scan test program");
  Serial.println(compile_date);
  Serial.println("--------------------------------------------");
}

void loop()
{
  long currentMillis = millis();

  // blink LED
  if (currentMillis - lastBlinkMillis > BLINK_PERIOD)
  {
    digitalWrite(LED_BUILTIN, ledState);
    ledState = !ledState;
    lastBlinkMillis = currentMillis;
  }

  // trigger Wi-Fi network scan
  if (currentMillis - lastScanMillis > SCAN_PERIOD)
  {
    WiFi.scanNetworks(true);
    Serial.print("\nScan start ... ");
    lastScanMillis = currentMillis;
  }

  // print out Wi-Fi network scan result uppon completion
  int n = WiFi.scanComplete();
  if(n >= 0)
  {
    Serial.printf("%d network(s) found\n", n);
    for (int i = 0; i < n; i++)
    {
      Serial.printf("%2d: %-14s BSSID: %s, Ch:%2d (%ddBm) %s\n",
        i+1,
        WiFi.SSID(i).c_str(),
        WiFi.BSSIDstr(i).c_str(),
        WiFi.channel(i),
        WiFi.RSSI(i),
        WiFi.encryptionType(i) == ENC_TYPE_NONE ? "open" : "");
    }
    WiFi.scanDelete();
  }
}
