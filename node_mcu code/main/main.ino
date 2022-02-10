#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char *wifiName = "wifiname";
const char *wifiPass = "password";
WiFiClient wifiClient;

// Web Server address to read/write from
// const char *host = "http://statichomeautomation.herokuapp.com/api";
const char *host = "API end point of your Home Automation App";

void setup()
{

  Serial.begin(115200);
  delay(10);
  Serial.println();

  Serial.print("Connecting to ");
  Serial.println(wifiName);

  WiFi.begin(wifiName, wifiPass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); // You can get IP address assigned to ESP
}

void loop()
{
  HTTPClient http; // Declare object of class HTTPClient

  Serial.print("Request Link:");
  Serial.println(host);

  http.begin(wifiClient, host); // Specify request destination

  int httpCode = http.GET();         // Send the request
  String payload = http.getString(); // Get the response payload from server

  Serial.print("Response Code:"); // 200 is OK
  Serial.println(httpCode);       // Print HTTP return code

  Serial.print("Returned data from Server:");
  Serial.println(payload); // Print request response payload

  if (httpCode == 200)
  {
    // Allocate JsonBuffer
    // Use arduinojson.org/assistant to compute the capacity.
    const size_t capacity = 3 * JSON_OBJECT_SIZE(3) + 140;
    DynamicJsonBuffer jsonBuffer(capacity);
    JsonObject &root = jsonBuffer.parseObject(payload);

    if (!root.success())
    {
      Serial.println(F("Parsing failed!"));
      return;
    }

    const char *analog = root["analog"]; // "0"

    JsonObject &digitaldevices = root["digitaldevices"];
    bool digitaldevices_digital01 = digitaldevices["digital01"]; // false
    bool digitaldevices_digital02 = digitaldevices["digital02"]; // false
    bool digitaldevices_digital03 = digitaldevices["digital03"]; // false

    JsonObject &lights = root["lights"];
    bool lights_light01 = lights["light01"]; // false
    bool lights_light02 = lights["light02"]; // false
    bool lights_light03 = lights["light03"]; // false

    // Parse JSON object
    // Decode JSON/Extract values
    Serial.println(F("Response:"));
    Serial.println(analog);
    Serial.println(digitaldevices_digital01);
    Serial.println(digitaldevices_digital02);
    Serial.println(digitaldevices_digital03);
    Serial.println(lights_light01);
    Serial.println(lights_light02);
    Serial.println(lights_light03);
    root.printTo(Serial);
  }
  else
  {
    Serial.println("Error in response");
  }

  http.end(); // Close connection

  delay(5000); // GET Data at every 5 seconds
}
