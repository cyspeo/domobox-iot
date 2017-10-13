#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = "XXXXXXXX";
const char* password = "XXXXXXXX";
const char* host = "XXX.XXX.XXX.XXX";
const int   port = 8080;

void setup() {
  Serial.begin(115200);
  delay(10);
  
  WiFi.begin(ssid, password);  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
   
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.print(WiFi.localIP()); 
  
}

void getProgrammation() {
}

void majTime() {
  
}

void setRelais() {
  
}

void loop() {
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected !");
    } else {  
    Serial.print("connecting to ");  Serial.println(host);
    Serial.print("Requesting URL: ");
    Serial.println(url);
  http.begin(host,port,url);
  int httpCode = http.GET();
    if (httpCode) {
      if (httpCode == 200) {
        String payload = http.getString();
        Serial.println("Domoticz response "); 
        Serial.println(payload);
      }
    }
  Serial.println("closing connection");
  http.end();
  }
}
























