l//Incluimos las librerias necesarias
#include <WiFi.h>
#include "time.h"
#include <stdint.h>
#include <PubSubClient.h>

// WIFI
const char* ssid = "ALUMNOS_CICLOS";
const char* password = "Ciclos2025sz?";


// Fecha y hora
const char* ntpServer = "es.pool.ntp.org";
// Zona horaria
const int32_t gmtoffset_sec = 3600;
// Horario de verano
const int32_t daylightoffset_sec = 0;

// MQTT
const char* mqtt_username = "grupo_3";
const char* mqtt_password = "1234";
const char* mqtt_server = "broker.emqx.io";
const int mqtt_port = 1883; 
//leds
uint32_t led_low_level = 2;
uint32_t led_medium_level = 2;
uint32_t led_high_level = 2;

void setup() {
  // put your setup code here, to run once:
Serial.println(115200);


  // Conexión wifi  
  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConexión WiFi establecida.");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

}

