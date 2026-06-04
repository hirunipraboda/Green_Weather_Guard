#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Smart Greenhouse"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

#define DHT_PIN 4
#define DHT_TYPE DHT11

#define FAN_PIN 12
#define HEATER_PIN 13
#define LIGHT_PIN 14
#define MIST_PIN 15
#define CO2_SENSOR_PIN 34

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

DHT dht(DHT_PIN, DHT_TYPE);
BlynkTimer timer;

float temperature;
float humidity;
int co2Level;

// Environmental thresholds
const float TEMP_HIGH = 30.0;
const float TEMP_LOW = 18.0;
const float HUMIDITY_LOW = 40.0;
const int CO2_HIGH = 400;

void readSensors()
{
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
    co2Level = analogRead(CO2_SENSOR_PIN);

    if (isnan(temperature) || isnan(humidity))
    {
        Serial.println("Failed to read DHT sensor!");
        return;
    }

    Serial.println("===== Greenhouse Data =====");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.print("CO2 Level: ");
    Serial.println(co2Level);

    // Send data to Blynk
    Blynk.virtualWrite(V0, temperature);
    Blynk.virtualWrite(V1, humidity);
    Blynk.virtualWrite(V2, co2Level);
}

void controlActuators()
{
    // Temperature Control
    if (temperature > TEMP_HIGH)
    {
        digitalWrite(FAN_PIN, HIGH);
        digitalWrite(HEATER_PIN, LOW);
    }
    else if (temperature < TEMP_LOW)
    {
        digitalWrite(FAN_PIN, LOW);
        digitalWrite(HEATER_PIN, HIGH);
    }
    else
    {
        digitalWrite(FAN_PIN, LOW);
        digitalWrite(HEATER_PIN, LOW);
    }

    // Humidity Control
    if (humidity < HUMIDITY_LOW)
    {
        digitalWrite(MIST_PIN, HIGH);
    }
    else
    {
        digitalWrite(MIST_PIN, LOW);
    }

    // CO2 Control
    if (co2Level > CO2_HIGH)
    {
        digitalWrite(FAN_PIN, HIGH);
    }

    // Lighting Control
    int currentHour = (millis() / 3600000) % 24;

    if (currentHour >= 6 && currentHour <= 18)
    {
        digitalWrite(LIGHT_PIN, HIGH);
    }
    else
    {
        digitalWrite(LIGHT_PIN, LOW);
    }

    // Send actuator status to Blynk
    Blynk.virtualWrite(V3, digitalRead(FAN_PIN));
    Blynk.virtualWrite(V4, digitalRead(HEATER_PIN));
    Blynk.virtualWrite(V5, digitalRead(MIST_PIN));
    Blynk.virtualWrite(V6, digitalRead(LIGHT_PIN));
}

void sendData()
{
    readSensors();
    controlActuators();
}

void reconnectWiFi()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Reconnecting WiFi...");
        WiFi.begin(ssid, pass);
    }
}

void setup()
{
    Serial.begin(115200);

    dht.begin();

    pinMode(FAN_PIN, OUTPUT);
    pinMode(HEATER_PIN, OUTPUT);
    pinMode(MIST_PIN, OUTPUT);
    pinMode(LIGHT_PIN, OUTPUT);

    digitalWrite(FAN_PIN, LOW);
    digitalWrite(HEATER_PIN, LOW);
    digitalWrite(MIST_PIN, LOW);
    digitalWrite(LIGHT_PIN, LOW);

    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("WiFi Connected");

    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

    timer.setInterval(2000L, sendData);
    timer.setInterval(10000L, reconnectWiFi);
}

void loop()
{
    Blynk.run();
    timer.run();
}