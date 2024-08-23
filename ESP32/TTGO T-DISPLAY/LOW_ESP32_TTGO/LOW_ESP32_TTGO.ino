#include <TFT_eSPI.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = ""; // Enter SSID
const char* password = ""; // Enter PASSWORD
const int* refreshRate = 500

// ExpressJS - Url
// TODO - Enter serverCpu/Gpu/Ram/Disk
const char* serverCpu = "http://localhost:5000/cpu"; // Change "localhost" for IP if you can use staticIp!
const char* serverGpu = "http://localhost:5000/gpu";
const char* serverRam = "http://localhost:5000/ram";
const char* serverDisk = "http://localhost:5000/disk";


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
  tft.println("Connecting to WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(5000);
    Serial.println("Connecting to WiFi...");
  }

  // Connected sucessefuly
  tft.fillScreen(TFT_BLACK);
  tft.println("Success! Wifi Conected");
  delay(1000);
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) { // Check the current connection status

    HTTPClient http;

    http.begin(serverCpu); // Specify the URL
    int httpCode = http.GET(); // Make the request

    if (httpCode > 0) { // Check for the returning code

      String payload = http.getString(); // Get the request response payload
      Serial.println(payload);

      // Parse JSON data
      DynamicJsonDocument doc(200);
      deserializeJson(doc, payload);

      // Extract data (example: CPU temperature)
      const char* cpuValue = doc["value"];

      // Clear the screen
      tft.fillScreen(TFT_BLACK);

      // Display CPU - Usage
      tft.setCursor(0, 0);
      tft.setTextColor(TFT_GREEN);
      tft.setTextSize(2);
      tft.print("CPU Load: ");
      tft.print(cpuValue);

      // Display GPU - Usage
      // tft.setCursor(0, 30);
      // tft.setTextColor(TFT_GREEN);
      // tft.setTextSize(2);
      // tft.print("GPULoad: ");
      // tft.print("N/A");
    }

    else {
      Serial.println("Error on HTTP request");
    }

    http.end(); // Free the resources
  }

  delay(refreshRate); // {refreshRate} in seconds
}
