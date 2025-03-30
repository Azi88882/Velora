#include <Arduino.h>
#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

// Define GPS module connection
static const int RXPin = 5, TXPin = 4; // ESP32 D4 → TX, D5 → RX
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
HardwareSerial gpsSerial(1);

void setup()
{
  Serial.begin(115200);
  gpsSerial.begin(GPSBaud, SERIAL_8N1, RXPin, TXPin);
  Serial.println("GPS Module Initialized...");
}

void loop()
{
  while (gpsSerial.available() > 0)
  {
    gps.encode(gpsSerial.read());

    if (gps.location.isUpdated())
    {
      Serial.print("Latitude: ");
      Serial.println(gps.location.lat(), 6);
      Serial.print("Longitude: ");
      Serial.println(gps.location.lng(), 6);
    }
  }
}