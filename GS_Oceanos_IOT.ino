#include <WiFi.h>
#include <ThingerESP32.h>
#include <DHT.h>
#include "secrets.h"

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
float temperatura, umidade;

ThingerESP32 thing(THINGER_USERNAME, THINGER_DEVICE_ID, THINGER_DEVICE_CREDENTIAL);

void setup() {
  Serial.begin(115200);
  dht.begin();

  // temp = random(10, 26);
  // umid = random(10, 80);
}

void loop() {

  leitura_temp_umid();

  thing.add_wifi(SSID, SSID_PASSWORD);

  thing["dadosSensores"] >> [](pson &out){ 
    out["temperatura"] = temperatura;
    out["umidade"] = umidade;
  };

  // thing["Temperatura"] >> outputValue(temperatura);
  // thing["Umidade"] >> outputValue(umidade);

  thing.handle();
  thing.write_bucket("aquacare", "dadosSensores");

  delay(60000);
}

// Cria a função para leitura de temperatura e umidade
void leitura_temp_umid() {
  //  float variacaoTemp = random(-100, 100) / 100.0;
  //  temp = temp + variacaoTemp;
  //  umid = umid + random(-400, 400) / 100.0;
  temperatura = dht.readTemperature();
  umidade = dht.readHumidity();
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" - ");
  Serial.print("Umidade: ");
  Serial.println(umidade);
}