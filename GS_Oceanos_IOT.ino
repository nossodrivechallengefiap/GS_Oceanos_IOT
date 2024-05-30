#include <WiFi.h>
#include <ThingerESP32.h>
#include "secrets.h"

// Declarando variáveis para os indicadores
float coliformes, ph, oxigenio_dissolvido, turbidez, temperatura;

ThingerESP32 thing(THINGER_USERNAME, THINGER_DEVICE_ID, THINGER_DEVICE_CREDENTIAL);

void setup() {
  Serial.begin(115200);

  // Atribuindo valores iniciais a os indicadores
  coliformes = 3000;
  ph = 7.0;
  oxigenio_dissolvido = 8.0;
  turbidez = 1.0;
  temperatura = 15.0;
}

void loop() {

  atualizandoIndicadores();

  // Conectando a o Thinger.io por wifi
  thing.add_wifi(SSID, SSID_PASSWORD);

  // Enviando os indicadores como propriedades
  thing["dadosSensores"] >> [](pson &out){ 
    out["coliformes"] = coliformes;
    out["ph"] = ph;
    out["oxigenio_dissolvido"] = oxigenio_dissolvido;
    out["turbidez"] = turbidez;
    out["temperatura"] = temperatura;
  };

  thing.handle();

  // Enviando a propriedades para o Databucket do Thinger.io
  thing.write_bucket("aquacare", "dadosSensores");

  delay(60000);
}

// Simulando a atualização dos indicadores com dados dos sensores
void atualizandoIndicadores() {
  coliformes += random(-100, 100);
  ph += random(-100, 100) / 100.0;
  oxigenio_dissolvido += random(-100, 100) / 100.0;
  turbidez += random(-100, 100) / 100.0;
  temperatura += random(-100, 100) / 100.0;

  Serial.println("coliformes: "+String(coliformes));
  Serial.println("ph: "+String(ph));
  Serial.println("oxigenio_dissolvido: "+String(oxigenio_dissolvido));
  Serial.println("turbidez: "+String(turbidez));
  Serial.println("temperatura: "+String(temperatura));
}

