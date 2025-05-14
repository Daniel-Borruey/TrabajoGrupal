//Incluimos las librerias necesarias
#include <WiFi.h>
#include "time.h"
#include <stdint.h>

#include <PubSubClient.h>

// WIFI
const char* ssid = "ALUMNOS_CICLOS";
const char* password = "Ciclos2025sz?";


// Estructura para el NTP
struct tm timeinfo;


// Fecha y hora
const char* ntpServer = "es.pool.ntp.org";
// Zona horaria
const int32_t gmtoffset_sec = 3600;
// Horario de verano
const int32_t daylightoffset_sec = 3600;

// MQTT
const char* mqtt_username = "grupo_3";
const char* mqtt_password = "1234";
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883; 
WiFiClient espClient;
PubSubClient mqtt_client(espClient);
//leds
uint32_t led_low_level = 18;
uint32_t led_medium_level = 4;
uint32_t led_high_level = 5;
//Sensor LDR 
int32_t LDR = 34;
int32_t LDR_value;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
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
  // Fexha y hora
  configTime(gmtoffset_sec, daylightoffset_sec, ntpServer);
   //Configuramos la NTP

  mqtt_client.setServer(mqtt_server,  mqtt_port);
  mqtt_client.setCallback(callback);
}

void loop() {
  // put your main code here, to run repeatedly:
  LDR_value = analogRead(LDR);

  if(!mqtt_client.connected()){
    reconnect();  
    }
  mqtt_client.loop();//procesa los mensajes

  getLocalTime(&timeinfo);//Recoge la fecha y hora desde la wifi

  erial.println(&timeinfo, "%d %m %Y %H:%M:%S");

  String currentTime = String(timeinfo.tm_mday)+"/"+String(timeinfo.tm_mon + 1 )+"/"+String(timeinfo.tm_year + 1900);


  String estado_actual;
  //Dependiendo de a que boton se le de desde el MQTT hara uno de los 3 casos
  if (LDR_value >= 3500) {
    estado_actual = "Alto";
    digitalWrite(led_low_level, LOW);
    digitalWrite(led_medium_level, LOW);
    digitalWrite(led_high_level, HIGH);
  } else if (LDR_value >= 1500 && LDR_value <= 3500) {
    estado_actual = "Medio";
    digitalWrite(led_low_level, LOW);
    digitalWrite(led_medium_level, HIGH);
    digitalWrite(led_high_level, LOW);
  } else if (LDR_value < 1500) {
    estado_actual = "Bajo";
    digitalWrite(led_low_level, HIGH);
    digitalWrite(led_medium_level, LOW);
    digitalWrite(led_high_level, LOW);
  }
  Serial.println("Estado persiana: " + estado_actual);
  if(mqtt_client.connected()){
    mqtt_client.publish("sensor/persiana", estado_actual.c_str());
      }
delay(100);

}

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
  void reconnect(){
  while (!mqtt_client.connected()) {
    Serial.print("Conectando a MQTT...");
    String client_id = "esp32-client-" + String(WiFi.macAddress());
    if (mqtt_client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Conectado a MQTT");
      Serial.println("Identificado.");
    } 
    else {
      Serial.print("Error, reconexión en 5s.");
      Serial.print(mqtt_client.state());
      
      delay(5000);
    }
  }
  }



