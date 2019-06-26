#include <SPI.h>

#include <Wire.h>

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#include <OneWire.h>
#include <DS18B20.h>

// The pin number to which you connect the sensor
#define ONEWIRE_PIN 2

#define OLED_DC 11  //OLED -- D/C
#define OLED_CS 12  //Not connected
#define OLED_CLK 10 //OLED -- SCL
#define OLED_MOSI 9 //OLED -- SDA
#define OLED_RESET 13//OLED -- RST
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

// Sensor address (use sensor_number.ino to find the address)
byte address[8] = {0x28, 0xFF, 0x5D, 0xC5, 0xB4, 0x16, 0x3, 0xF};

OneWire onewire(ONEWIRE_PIN);
DS18B20 sensors(&onewire);

void setup() {
  while(!Serial);
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();

  display.setTextSize(3.0);
  display.setTextColor(WHITE);

  sensors.begin();
  sensors.request(address);
}

void loop() {
  float temperature;
  if (sensors.available())
  {
    temperature = sensors.readTemperature(address);
    sensors.request(address);
  }

  display.clearDisplay();
  display.setCursor(10,6);
  display.println(String(temperature));
  display.display();
  delay(1000);
}
