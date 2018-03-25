#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = "XXXXXXXX";
const char* password = "XXXXXXXX";
const char* host = "XXX.XXX.XXX.XXX";
const int   port = 8080;
const char* user = "XXXX"; 
const char* password = "XXXX"; 
const char* url = "api/piscine/programmation"

char* programmation = "";
char* timeStr = "";
int heures = 0;
int minutes = 0;

void setup() {
  Serial.begin(115200);
  delay(10);
  
  WiFi.begin(ssid, password);  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
   
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.print(WiFi.localIP()); 
  
}

void getProgrammation() {
    int rc = -1;
    if(WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi not connected !");
    } else {
      Serial.print("connecting to ");
      Serial.println(host);
      Serial.print("Requesting URL: ");
      Serial.println(url);
      http.begin(host,port,url);
      http.setAuthorization(user, password);
      int httpCode = http.GET();
      if (httpCode) {
        if (httpCode == 200) {
          String payload = http.getString();
          Serial.println("Domoticz response ");
          Serial.println(payload);
          programmation = payload.substring(0,23);
          timeStr = payload.substring(24);

          majTime();
          
          rc = 0;
        }
      } 
      Serial.println("closing connection");
      http.end();
      if (rc == -1) {
        //incremente time d'une minute;
        minutes++;
        if (minutes > 59) {
          minutes = 0;
          heure++;
          if (heures > 23) {
            heures = 0;            
          }
        }
      }
    }
  
}

void majTime() {
  heureStr = timeStr.substring(0,1);
  minStr = timeStr.substring(2,3);
  minutes = minStr.toInt();
  heures = heureStr.toInt();
}

void setRelais() {
  int state = relaisState;
  if (heures == 23) {
    state = programmation.substring(heures,heures+1).toInt();
  } else {
    state = programmation.substring(heures).toInt();
  }
  relaisState = state;
  //TODO verifier le code
  digitalWrite(5,relaisStatus);
}

void loop() {
  getProgrammation();
  setRelais();
  
  // Attendre 60 secondes
  delay(60);
}
























