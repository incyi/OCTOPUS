/**
 * IoT Octopus by fab-lab.eu
 * NodeMCU 1.0 (ESP-12E Module)
 * 
 * https://www.fab-lab.eu
 * What makes it special?
 * 
 * 1x ESP8266 including UBS/UART, power options(*) to run in 20uA sleep mode for extended battery lifetime
 * 2x RGBW NeoPixel on board
 * 2x Grove pinout (analog and I2C, make sure they are on 3V only!)
 * 1x Adafruit compatible FeatherWing pinout (tested: NeoPixel-, 7-Segment-, Charlie Wings), header included
 * 1x Bosch Sensortec BME680 (Gas/VOC, Humidity, Barometer, Temperatur)
 * credit card size
 * attaching a key holder turns it into a wearable or event badge
 * use banana plugs to interact with OCTOPUS, it is ready for it!
 * use alligator clips to interact with OCTOPUS, it is ready for it!
 * variety for power sources: 2xAAA, LiPo (charger on board), Solar charging via USB, charging via USB
 * stunning 921000 baud rate for flashing via the Arduino(TM) IDE
 * the external analog is fine to run on 3V/VCC voltage level.
 * 
 */

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

//Adafruit_BME680 bme; // I2C
//Adafruit_BME680 bme(BME_CS); // hardware SPI
Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO,  BME_SCK);

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println(F("BME680 test"));

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
}

void loop() {
  if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
  Serial.print("Temperature = ");
  Serial.print(bme.temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(bme.pressure / 100.0);
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  Serial.print(bme.humidity);
  Serial.println(" %");

  Serial.print("Gas = ");
  Serial.print(bme.gas_resistance / 1000.0);
  Serial.println(" KOhms");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.println();
  delay(2000);
}
