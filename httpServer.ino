#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>

//const char* ssid = "Matty_main";
//const char* password = "1234123412";

const char* ssid = "Speluno_club";
const char* password = "Mamypr08l3m";

ESP8266WebServer server(80);

const char* www_username = "admin";
const char* www_password = "esp8266";
const char* www_realm = "Custom Auth Realm";
String authFailResponse = "Authentication Failed";

void led_on() {
  digitalWrite(2, HIGH);
}

void led_off() {
  digitalWrite(2, LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  WiFi.mode(WIFI_STA);
  IPAddress staticIP(192, 168, 0, 91); // where xx is the desired IP Address
  IPAddress gateway(192, 168, 0, 1); // set gateway to match your network
  IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network
  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 100 );
    Serial.print ( "." );
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());

  ArduinoOTA.begin();

  //  server.on("/", []() {
  //    if (!server.authenticate(www_username, www_password))
  //      return server.requestAuthentication(DIGEST_AUTH, www_realm, authFailResponse);
  //    else handleParameters();
  //  });


  server.on("/", handleParameters);

  server.begin();
}

void handleParameters() {
  String message = "";

  if (server.arg("led1") == "") {   //Parameter not found
    message = "Argument not found";
  } else {    //Parameter found
    if (server.arg("led1") == "on")
    led_off();
     
    else if (server.arg("led1") == "off")
       led_on();
    message += server.arg("led1");     //Gets the value of the query parameter
  }

  server.send(200, "text / plain", message);        //Returns the HTTP response
}

void loop() {
  ArduinoOTA.handle();
  server.handleClient();
}
