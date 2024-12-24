#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

Adafruit_BME280 bme;  // I2C

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  if (!bme.begin(0x76)) {  // BME280 address may vary, default is 0x76
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  server.begin();
  Serial.println("Server started");

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  while (!client.available()) {
    delay(1);
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  if (request.indexOf("/data") != -1) {
    handleDataRequest(client);
  } else {
    handleRoot(client);
  }
}

void handleRoot(WiFiClient client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();

  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.println("<head>");
  client.println("<title>ESP32 BME280 Sensor Data</title>");
  client.println("</head>");

  client.println("<body>");
  client.println("<h1>ESP32 BME280 Sensor Data</h1>");

  client.println("<p>Temperature: " + String(bme.readTemperature()) + " °C</p>");
  client.println("<p>Humidity: " + String(bme.readHumidity()) + " %</p>");
  client.println("<p>Pressure: " + String(bme.readPressure() / 100.0F) + " hPa</p>");

  client.println("</body>");
  client.println("</html>");

  delay(10);
}

void handleDataRequest(WiFiClient client) {
  String response = "{\"temperature\":" + String(bme.readTemperature()) +
                    ",\"humidity\":" + String(bme.readHumidity()) +
                    ",\"pressure\":" + String(bme.readPressure() / 100.0F) + "}";

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println("Connection: close");
  client.println();
  client.println(response);

  delay(10);
}
