#include <Wire.h>
#include <I2CKeyPad.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>

// Biblioteca donde defino las características del Keypad
#include "config_I2CKeyPad.h"

// Inicializo el Keypad
I2CKeyPad keyPad(KEYPAD_ADDRESS);

// Declaracion de la estructura
struct lastKeyPressed lastKey;

// Biblioteca donde defino las características del display OLED
#include "config_OLED.h"

// Inicializo la pantalla OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Puerto 80 TCP, este puerto se usa para la navegación web http
WiFiServer server(80);

// Creo el objeto cliente
WiFiClient client;

// Bibliotecas con configuraciones y modos del esp8266
#include "config_esp8266.h"
#include "modos_setup_esp8266.hpp"

// Datos en formato json
#include "datos_json.hpp"

String pass_ingresada="";
String validacion;
#define led_r 13
#define led_g 15
bool correcta=false;

// Biblioteca que contiene funciones para el muestreo de datos en el display OLED
#include "OLED_utils.h"

bool ValidacionDeContraseña(String);

void setup() {
  Serial.begin(115200);
  // Setup para el Keypad
  Wire.begin();
  Wire.setClock(100000);
  if (!keyPad.begin()){
    Serial.println("No se encontró el keypad");
    while(1) delay(10);
  }
  lastKey.time=0;
  lastKey.last='N';

  // Setup para la pantalla OLED
  // SSD1306_SWITCHCAPVCC = habilita el uso del voltaje interno de 3.3V en el display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println("No se encontró la pantalla OLED");
    while (1) delay(10);
  }
  display.clearDisplay();
  display.setRotation(2);
  display.display();
  displayPassword(pass_ingresada);
  
  // Setup para la conexión WiFi
  // Realizo la conexión WiFi en modo STA
  ConectarEnSTA();
  // Se inicia el esp como servidor web
  server.begin();
  Serial.println("Servidor iniciado");

  // Setup para los leds
  pinMode(led_r,OUTPUT);
  digitalWrite(led_r,LOW);
  pinMode(led_g,OUTPUT);
  digitalWrite(led_g,LOW);
  
}

void loop() {
  
  uint32_t now = millis();

  if (now - lastKey.time >= 100)
  {
    lastKey.time = now;
    // Lectura de Keypad
    uint8_t index = keyPad.getKey();
    
    if((keys[index]!='N') && (keys[index]!='F') && (keys[index]!=lastKey.last)){
      switch(keys[index]){
        // Se ingresa la contraseña
        case 'D':
          displayPassStatus("ingresada");
          delay(1500);
          // Se valida la contraseña a través de un cliente
          correcta=ValidacionDeContraseña(pass_ingresada);
          if(correcta){
            displayPassStatus("correcta");
            digitalWrite(led_g,HIGH);
            delay(3000);
            digitalWrite(led_g,LOW);
          }
          else{
            displayPassStatus("incorrecta");
            digitalWrite(led_r,HIGH);
            delay(3000);
            digitalWrite(led_r,LOW);
          }
          pass_ingresada="";
          displayPassword(pass_ingresada);
          break;
        // Borra el último caracter
        case 'B':
          if(pass_ingresada.length()>0){
            pass_ingresada.remove(pass_ingresada.length()-1);
            displayPassword(pass_ingresada);
          }
          break;
        // Borra todos los caracteres  
        case 'C':
          if(pass_ingresada.length()>0){
            pass_ingresada="";
            displayPassword(pass_ingresada);
          }
          break;
        default:
          pass_ingresada += keys[index];
          displayPassword(pass_ingresada);
          break;
      }
    }
    lastKey.last=keys[index];
  }
}


bool ValidacionDeContraseña(String pass_ingresada){
  if (!client){
    do{
      client = server.available();
    }while(!client);
  }

  Serial.println("Nuevo cliente");
  // Se espera a que el cliente envíe una solicitud para comenzar la validación
  while(!client.available()){
    delay(1);
  }
  
  client.flush();
  // El servidor envía una solicitud de validación al cliente
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println("");

  validacion="si";
  String text_json=json_reload(validacion,pass_ingresada);
  client.print(text_json);
  delay(1);
  
  do{
    client = server.available();
  }while(!client);

  Serial.println("Nuevo cliente");
  // Se espera a que el cliente envíe los resultados de la validación
  while(!client.available()){
    delay(1);
  }

  // Leo la primera línea de la solicitud
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush(); // Borro los datos
  client.println("HTTP/1.1 200 OK");

  do{
    client = server.available();
  }while(!client);
  
  if(request.indexOf("pass=correct") != -1){
    return true;
  }
  else{
    return false;
  }
}
