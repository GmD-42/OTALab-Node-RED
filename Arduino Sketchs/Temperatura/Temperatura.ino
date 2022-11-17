
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <OTALabDevice.h>

String id = "15";
OTALabDevice* device = new OTALabDevice();

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

char temp[10];
char pres[10];
char alti[10];

const char* mqtt_server = "broker.mqtt-dashboard.com";
const int lamp = 2;

WiFiClient espClient;
PubSubClient client(espClient);


// Esta função reconecta o ESP8266 ao servidor MQTT
void reconnect2() {
  // Fica em loop até conectar novamente
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    // Tentativa de conexão. O argumento passado na função 'connect' é o id da conexão MQTT, este deve ser único em um servidor.
    if (client.connect("EspClientIot")) {
      Serial.println("connectado");
      // Aqui nos increvemos ou reinscrevemos nos tópicos
      // Você pode se inscrever em mais de um tópico com o mesmo ESP8266
      client.subscribe("tcc/iot/mqtt/led");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(lamp, OUTPUT);
  digitalWrite(lamp, LOW);
  Serial.begin(115200);
  Serial.println(F("BMP280 test"));
  
  client.setServer(mqtt_server, 1883);
  
  if (!bmp.begin(0x76)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  
  device->setup(id);
}

void loop() {
    Serial.print(F("Temperature = "));

    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    
    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
    Serial.println(" m");
    dtostrf(bmp.readTemperature(),6,2,temp);
    dtostrf(bmp.readPressure(),6,2,pres);
    dtostrf(bmp.readAltitude(1013.25),6,2,alti);
    
    if (!client.connected()) {
      reconnect2();
      delay(5000);
    }
    if(!client.loop())
      client.connect("EspClientIot");

    client.publish("tcc/iot/mqtt/led",temp);
    delay(1000);
    client.publish("tcc/iot/mqtt/led",pres);
    delay(1000);
    client.publish("tcc/iot/mqtt/led",alti);
    
    Serial.println();
    device->handle();
    delay(10000);
}
