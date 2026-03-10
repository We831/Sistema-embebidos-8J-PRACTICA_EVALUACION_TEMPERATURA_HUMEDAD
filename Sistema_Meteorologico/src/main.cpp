#include <WiFi.h>
#include "ThingSpeak.h"
#include "DHT.h"

#define DHTPIN 15
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "UAM-ROBOTICA";
const char* password = "m4nt32024uat";

unsigned long channelID = 3292152;
const char* writeAPIKey = "1C8CFJQ5BC0NO3G0";

WiFiClient client;

void setup() {

  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);

  Serial.print("Conectando a WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(" Conectado!");

  ThingSpeak.begin(client);
}

void loop() {

  float temperatura = dht.readTemperature();
  float humedad = dht.readHumidity();

  Serial.print("Temperatura: ");
  Serial.println(temperatura);

  Serial.print("Humedad: ");
  Serial.println(humedad);

  ThingSpeak.setField(1, temperatura);
  ThingSpeak.setField(2, humedad);

  int respuesta = ThingSpeak.writeFields(channelID, writeAPIKey);

  if(respuesta == 200){
    Serial.println("Datos enviados correctamente");
  }
  else{
    Serial.println("Error enviando datos");
  }

  delay(20000);
}