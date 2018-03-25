#include <Arduino.h>
#include <ESP8266WiFi.h> //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager

String programmation = "";
String mode = "";
int heure = 0;
int minute = 0;
int relaisState = 0;

ESP8266WebServer server(80);

/**
 * Cette fonction calcul l'état du relais par rapport à la programmationet l'heure courante. 
 */
void checkProgrammation()
{
    int state = relaisState;
    if (heure == 23)
    {
        state = programmation.substring(heure).toInt();
    }
    else
    {
        state = programmation.substring(heure,heure +1).toInt();
    }
    Serial.print("relaisState=");
    Serial.println(relaisState);
    relaisState = state;
    //TODO verifier le code
    digitalWrite(0, relaisState);
}

//
/**
 * Reception d'une mise à jour du serveur
 * paramettre attendu
 * - programmation : string  représentant les 24 heures de programmation vallant 0 ou 1
 * - mode : string representant l'interrupteur : AUTO = mode programmation, ON = mode force, OFF = mode eteint
 * - hour : int = heure
 * - minute : int = minute
 * - token : string : authentification token
 * 
 * Exemple de requete : http://IP_ESP:piscine?programmation=010001111100000111100010&mode=AUTO&hour=10&minute=23&token=cyspeo-iot
 */
void reception()
{
    Serial.println("Update GPIO command from DOMOBOX : ");
    for (int i = 0; i < server.args(); i++)
    {
        Serial.print(server.argName(i));
        Serial.println(server.arg(i));
    }
    programmation = server.arg("programmation");
    mode = server.arg("mode");
    heure = server.arg("hour").toInt();
    minute = server.arg("minute").toInt();
    String token = server.arg("token");
    if (token != "cyspeo-iot")
    {
        Serial.println("Not authentified ");
        return;
    }

    if (mode == "AUTO")
    {
        checkProgrammation();
    }
    else if (mode == "OFF")
    {
        relaisState = 0;
        digitalWrite(0, relaisState);
    }
    else
    {
        // ON
        relaisState = 1;
        digitalWrite(0, relaisState);
    }
    //response
    String out = "";
    out += "{\"programmation\":\""; out.concat(programmation); out.concat("\",");
    out += "{\"mode\":\"" + mode + "\"}";
    out += "{\"hour\":\""; out.concat(heure); out.concat("\",");
    out += "{\"minute\":\""; out.concat(minute); out.concat("\",");
    out += "{\"token\":\"" + token + "\",";
    out += "{\"relaisStatus\":\""; out.concat(relaisState); out.concat("\"}");
    server.send(200, "application/json", out);
}

void setup()
{
    pinMode(0, OUTPUT);
    // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.println("piscine IOT ");
    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;
    //reset saved settings
    //wifiManager.resetSettings();

    //set custom ip for portal
    //wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

    //fetches ssid and pass from eeprom and tries to connect
    //if it does not connect it starts an access point with the specified name
    //here  "AutoConnectAP"
    //and goes into a blocking loop awaiting configuration
    wifiManager.autoConnect("AutoConnectAP");
    //or use this for auto generated name ESP + ChipID
    //wifiManager.autoConnect();

    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
    server.on("/piscine", reception);
    server.begin();
}

void loop()
{
    //Serial.println("loop");
    server.handleClient();
    // Verifie s'il faut modifier le relais en fonction de la programmation
    checkProgrammation();

    // Attendre 60 secondes
    delay(60);

    //Avancement de l'heure
    minute++;
    if (minute > 59)
    {
        minute = 0;
        heure++;
        if (heure > 23)
        {
            heure = 0;
        }
    }
}