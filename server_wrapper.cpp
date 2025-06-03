#include "server_wrapper.h"
#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
// #include <SPIFFS.h>
#include <LittleFS.h>

#define SPIFFS LittleFS

const char* INTERNET_SSID = "your wifi ssid";
const char* INTERNET_PASSWORD = "your wifi password";

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
    WiFi.mode(WIFI_AP_STA);
  
    // connect to wifi
    WiFi.begin(INTERNET_SSID, INTERNET_PASSWORD);
    delay(50);

    // create an access point
    WiFi.softAP(SSID, PASSWORD);
    delay(500);

    IPAddress apIP = WiFi.softAPIP();

    dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
    dnsServer.start(DNS_PORT, "*", apIP);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    Serial.println((char*) data);
    updateLimits((char*) data);
  }
}

void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  if(type == WS_EVT_CONNECT){
    Serial.println("Websocket client connection received");
    globalClient = client;

  } else if(type == WS_EVT_DISCONNECT){
    Serial.println("Websocket client connection finished");
    globalClient = NULL;

  } else if(type == WS_EVT_DATA){
    handleWebSocketMessage(arg, data, len);
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

    server.on("/bootstrap.bundle.min.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/bootstrap.bundle.min.js", "text/javascript");
    });

    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/script.js", "text/javascript");
    });

    server.begin();
}

void handleConnections(){
    dnsServer.processNextRequest();
    ws.cleanupClients();
}

void sendMessage(char *msg){
    if(globalClient != NULL && globalClient->status() == WS_CONNECTED){
      ws.textAll(msg);
    }
}