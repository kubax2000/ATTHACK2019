#include "WiFi.h"
#include <WiFiMulti.h>

//#include <SoftwareSerial.h>

#define MAX_CLIENTS_NUM 8
#define SERVER_PORT 333
const char* ssid     = "hackathon";
const char* password = "att4hack";
WiFiServer server(SERVER_PORT);
WiFiClient* clients[MAX_CLIENTS_NUM] = { NULL };

WiFiMulti WiFiMulti;

//SoftwareSerial mySerial(2, 4);

void setup() {
    //mySerial.begin(9600);
    //mySerial.println("Hello, world?");
    
    WiFiMulti.addAP("hackathon", "att4hack");

    while(WiFiMulti.run() != WL_CONNECTED) {
        delay(500);
    }
  
    server.begin();
}

bool sendedData[50];
double provousMillis = 0;
double usersCometime[50];
double usersTimestamps[50];
String usersCrosstype[50];
String usersName[50];
int usersHelper = 0;

void loop() {
  for(int i = 0; i < usersHelper; i++) {
    if(!sendedData[i] && (millis() - usersTimestamps[i]) >= (usersCometime[i] - 10000)) {
      //mySerial.println("Hello, world?");
      sendedData[i] = true;
    }
  }

  WiFiRead();
}

int g_char_spaces[50];
int g_char_backslashs[50];
void getCharsPositions(String string) {
  int counter[] = {0, 0};
  bool escapeChars = false;
  for(int i = 0; i < 50; i++){
    g_char_spaces[i] = -1;
    g_char_backslashs[i] = -1;
  }
  for(int i = 0; i < string.length(); i++){
    if(string.charAt(i) == ' ' && !escapeChars && counter[0] < 50){
      g_char_spaces[counter[0]] = i;
      counter[0]++;
    }
    if(string.charAt(i) == '/' && !escapeChars && counter[1] < 50){
      g_char_backslashs[counter[1]] = i;
      counter[1]++;
    }
    if(string.charAt(i) == '"'){
      escapeChars = !escapeChars;
    }
  }
}

void WiFiApplyCommand(int idUser, String stringData) {
  if(stringData.indexOf("GET /send-data") == 0 || stringData.indexOf("OPTIONS /send-data") == 0) {
    getCharsPositions(stringData);
    String username = stringData.substring(g_char_backslashs[1] + 1, g_char_backslashs[2]);
    int millisToCome = stringData.substring(g_char_backslashs[2] + 1, g_char_backslashs[3]).toInt();
    String crosstype = stringData.substring(g_char_backslashs[3] + 1, g_char_backslashs[4]);
    
    int userId = -1;
    for(int i = 0; i < 50; i++) {
      if(usersName[i] == username) {
        userId = i;
        break;
      }
    }
    if(userId == -1) {
      sendedData[usersHelper] = false;
      usersCometime[usersHelper] = millisToCome;
      usersCrosstype[usersHelper] = crosstype;
      usersTimestamps[usersHelper] = millis();
      usersName[usersHelper] = username;
      usersHelper++;
    }
  }
}

void WiFiRead(){
  WiFiClient newClient = server.available();

  if (newClient) {
    for (int i = 0; i < MAX_CLIENTS_NUM; i++) {
        if (NULL == clients[i]) {
            clients[i] = new WiFiClient(newClient);
            break;
        }
     }
  }

  for (int i = 0; i < MAX_CLIENTS_NUM; i++) {
    String stringData = "";
    if (NULL != clients[i]) {
      if(clients[i]->available()){
        while(clients[i]->available()){
          char c = clients[i]->read();
          if(clients[i]->available() == 0){
            stringData += char(c);
            c = '\n';
          }
          if (c == '\n') {
            WiFiApplyCommand(i, stringData);
            stringData = "";
          } else {
            stringData += char(c);
          }
        }
        clients[i]->println("HTTP/1.1 200 OK");
        clients[i]->println("Content-type:text/html");
        clients[i]->println("Server: ESP32/Custom by Uzlabina :)");
        clients[i]->println();
        clients[i]->println("{\"result\":\"success\"}");
        clients[i]->stop();
        clients[i]->flush();
        clients[i] = NULL;
      } else if(!clients[i]->connected()) {
        clients[i] = NULL;
      }
    }
  }
}
