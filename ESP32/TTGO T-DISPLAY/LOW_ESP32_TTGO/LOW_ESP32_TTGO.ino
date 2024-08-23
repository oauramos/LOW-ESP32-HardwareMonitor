#include <TFT_eSPI.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "";     // Enter SSID
const char* password = "";  // Enter PASSWORD
const int refreshRate = 500;

// ExpressJS - Url
const char* expressJs = "http://localhost:5000/monitor"; // Change "localhost" for IP if you can use staticIp!

// TODO - Add later how to enable TFT_eSPI()
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

void setup() {
  Serial.begin(115200);

  // Initialize the display
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  tft.setCursor(0, 0);
  tft.println("Wifi Status [...]");

  while (WiFi.status() != WL_CONNECTED) {
    delay(3000);
    Serial.println("Wifi Status [FAILED]");
  }

  // Connected sucessefuly
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0);
  tft.println("Wifi Status [OK]");

  delay(1000);
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) {  // Check the current connection status

    HTTPClient http;
    http.begin(expressJs);  // Start CPU endpoint
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {

      String payload = http.getString();
      Serial.println(payload);

      // Parsing JSON
      StaticJsonDocument<1024> doc;
      DeserializationError error = deserializeJson(doc, payload);

      if (!error) {
        const char* cpu_id = doc["cpu"]["id"];
        const char* cpu_load = doc["cpu"]["load"];
        const char* cpu_temp = doc["cpu"]["temp"];

        const char* gpu_id = doc["gpu"]["id"];
        const char* gpu_load = doc["gpu"]["load"];
        const char* gpu_temp = doc["gpu"]["temp"];

        const char* ram_id = doc["ram"]["id"];
        const char* ram_load = doc["ram"]["load"];
        const char* ram_max = doc["ram"]["max"];

        const char* disk_id = doc["disk"]["id"];
        const char* disk_load = doc["disk"]["load"];
        const char* disk_temp = doc["disk"]["temp"];

        // Display data
        tft.fillScreen(TFT_BLACK);  // Clear screen
        tft.setCursor(0, 0);
        tft.setTextSize(2);


        // Display CPU
        tft.setTextColor(TFT_GREEN);
        tft.print("CPU:");
        tft.setCursor(0, tft.getCursorY() + tft.fontHeight());

        tft.setTextColor(TFT_DARKGREEN);
        tft.print(cpu_load);
        tft.print(" | ");
        tft.print(cpu_temp);
        tft.setCursor(0, tft.getCursorY() + tft.fontHeight());


        // Display GPU
        tft.setTextColor(TFT_GREEN);
        tft.print("GPU:");
        tft.setCursor(0, tft.getCursorY() + tft.fontHeight());

        tft.setTextColor(TFT_DARKGREEN);
        tft.print(gpu_load);
        tft.print(" | ");
        tft.print(gpu_temp);
        tft.setCursor(0, tft.getCursorY() + tft.fontHeight());


        // Display RAM
        tft.setTextColor(TFT_GREEN);
        tft.print("RAM:");
        tft.setCursor(0, tft.getCursorY() + tft.fontHeight());

        tft.setTextColor(TFT_DARKGREEN);
        tft.print(ram_load);
        tft.print(" | ");
        tft.print(ram_max);
        tft.setCursor(0, tft.getCursorY() + tft.fontHeight());


        // Display Disk
        tft.setTextColor(TFT_GREEN);
        tft.print("DISK:");
        tft.setCursor(0, tft.getCursorY() + tft.fontHeight());

        tft.setTextColor(TFT_DARKGREEN);
        tft.print(disk_load);
        tft.print(" | ");
        tft.print(disk_temp);

      } else {
        Serial.println("Failed to parse JSON");
      }
    } else {
      Serial.printf("Error code: %d\n", httpResponseCode);
    }
    http.end();
  }
  delay(1000);  // {refreshRate} in seconds
}

// Say thanks to Obesity King aka. Otavio A. Ramos
