#include "server_wrapper.h"
#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

const char* SSID = "PowerMeter";
const char* PASSWORD = "secret AP pw";

const byte DNS_PORT = 53;
DNSServer dnsServer;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
AsyncWebSocketClient *globalClient = NULL;

void initAP() {
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    WiFi.mode(WIFI_AP);
  
    WiFi.softAP(SSID, PASSWORD);
    delay(500);

    IPAddress apIP = WiFi.softAPIP();

    dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
    dnsServer.start(DNS_PORT, "*", apIP);
}

void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){

  if(type == WS_EVT_CONNECT){

    Serial.println("Websocket client connection received");
    globalClient = client;

  } else if(type == WS_EVT_DISCONNECT){

    Serial.println("Websocket client connection finished");
    globalClient = NULL;

  }
}

void initServer() {
    if(!SPIFFS.begin()){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    ws.onEvent(onWsEvent);
    server.addHandler(&ws);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/index.html", String());
    });

    server.on("/generate_204", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/index.html", String());
    });

    server.on("/fwlink", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/index.html", String());
    });

    server.onNotFound([](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html", String());
    });

    server.on("/bootstrap.min.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/bootstrap.min.css", "text/css");
    });

    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/script.js", "text/javascript");
    });

    server.begin();
}

void processDNSRequests(){
    dnsServer.processNextRequest();
}

void sendMessage(){
    if(globalClient != NULL && globalClient->status() == WS_CONNECTED){
      globalClient->text("tate");
    }
}