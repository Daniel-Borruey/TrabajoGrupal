//Incluimos las librerias necesarias
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
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883; 
//leds
uint32_t led_low_level = 2;
uint32_t led_medium_level = 2;
uint32_t led_high_level = 2;
//Sensor LDR 
int32_t LDR = 18;
int32_t LDR_value;

void setup() {
  // put your setup code here, to run once:
pinMode(led_low_level, OUTPUT);
pinMode(led_medium_level, OUTPUT);
pinMode(led_high_level, OUTPUT);
pinMode(LDR, INPUT);



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






void automatic(char* topic, byte* payload, unsigned int length) {

if(value_1 == x && value_2 == 1){
  digitalWrite(led_low_level, HIGH);
  
}

if()

if()



//Función callback
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje del topico");
  Serial.print(topic);


  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Mensaje: ");
  Serial.println(message);
 
  }


  //Función reconnec por si la conexió falla volver a conectar con el MQTT
  void reconnect() {
  while (!mqtt_client.connected()) {
    Serial.print("Conectando a MQTT...");
      String client_id = "esp32-client-" + String(WiFi.macAddress());
    if (mqtt_client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Conectado a MQTT");

      mqtt_client.subscribe("sensor/low");
      mqtt_client.subscribe("sensor/medium");
      mqtt_client.subscribe("sensor/high");
      Serial.println("Identificado.");
    } 
    else {
      Serial.print("Error, reconexión en 5s.");
      Serial.print(mqtt_client.state());
      
      delay(5000);
    }
  }
  }


