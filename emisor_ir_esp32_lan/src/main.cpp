// An IR LED must be connected to Arduino PWM pin 3.
// On esp pin 4
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <IRremote.hpp>

// Credenciais para acesso a rede wifi
const char* ssid = "ComFio2.4GHz";
const char* password = "tomaladra0";

AsyncWebServer server(80);

String handler;
String idSense;
String mac;

void command(int opcao) {
  //const uint8_t NEC_KHZ = 38;
  const int RAW_DATA_LEN = 100;
  uint16_t OFF[RAW_DATA_LEN] = {4400,4350, 500,1650, 500, 600, 500,1650, 500,1700, 500, 550, 500, 550, 550,1650, 500, 550, 550, 550, 550,1650, 500, 550, 500, 600, 500,1650, 500,1650, 500, 600, 500,1650, 500, 600, 500,1650, 500,1650, 550,1650, 500,1650, 500, 550, 550,1650, 500,1650, 500,1650, 500, 550, 550, 550, 550, 550, 500, 550, 550,1650, 500, 550, 550, 550, 550,1650, 500,1650, 500,1650, 500, 550, 550, 550, 550, 550, 500, 550, 550, 550, 550, 550, 500, 550, 550, 550, 550,1650, 500,1650, 500,1650, 500,1650, 500,1650, 550};
  uint16_t ON22[RAW_DATA_LEN] = {4350,4300, 550,1650, 500, 550, 550,1650, 500,1650, 500, 600, 500, 550, 550,1650, 500, 550, 550, 550, 500,1650, 500, 600, 500, 550, 550,1650, 500,1650, 500, 550, 550,1650, 500, 550, 550, 550, 500,1700, 500,1650, 500,1650, 500,1650, 500,1650, 500,1700, 500,1650, 500,1650, 500, 550, 550, 550, 500, 550, 550, 550, 550, 550, 500, 600, 500, 550, 550,1650, 500,1650, 500,1650, 500, 550, 550, 550, 550, 550, 500, 600, 500,1650, 500, 550, 550, 550, 550, 550, 500,1650, 550,1650, 500,1650, 500,1650, 500};

  switch (opcao) {
  case 0:
    IrSender.sendRaw(OFF, RAW_DATA_LEN, 38);
    Serial.println(F("off\n"));
    break;
  case 22:
    IrSender.sendRaw(ON22, RAW_DATA_LEN, 38);
    Serial.println(F("22\n"));
    break;
  default:
  Serial.println(F("Nada\n"));
    break;
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  IrSender.begin(33, ENABLE_LED_FEEDBACK);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  mac = WiFi.macAddress();
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());

  server.on("/check", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", mac.c_str());
  });
  server.on("/emissor", HTTP_POST, [](AsyncWebServerRequest *request) {
    int params = request->params();
    for(int i=0;i<params;i++){
      AsyncWebParameter* p = request->getParam(i);
      idSense = p->name().c_str();
      handler = p->value().c_str();
      if(idSense == "off") {
        command(0);
        request->send_P(200, "text/plain", "Desligado");
      } else {
        if(handler == "22") {
          command(22);
        request->send_P(200, "text/plain", "Ligado 22");
        }
        else if(handler == "23") {
          command(23);
          request->send_P(200, "text/plain", "Ligado 23");
        }
        else if(handler == "24") {
          command(24);
          request->send_P(200, "text/plain", "Ligado 24");
        }
        else if(handler == "25") {
          command(25);
          request->send_P(200, "text/plain", "Ligado 25");
        }
        else if(handler == "26") {
          command(26);
          request->send_P(200, "text/plain", "Ligado 26");
        } else {
          request->send_P(500, "text/plain", "Nada a responder");
        }
      }
    }
  });

  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server.begin();
}

void loop() {}