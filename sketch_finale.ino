#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <DHT_U.h>
#include "utils.h"
#include "moisture.h"
#include "waterlvl.h"

//instanciation de classes Waterlvl , Moisture et DHT_Unified
Moisture moisture;
Waterlvl waterlvl ;
//DHT_Unified prend deux parametre Le pin de connexion du capteur dht et  le type de dth utiliser
DHT_Unified dht(DHTPIN, DHTTYPE);
//declaration de variables , delays et l'id du prototype
uint32_t delayMS;
int Id = 1 ; 

void setup() {
  Serial.begin(9600);
  // Initialisation des capteur
  dht.begin();
  delay(2000);
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;

}

void loop() {
  //envoie des données sous format JSON avec detection d'erreur
  delay(delayMS);
  DynamicJsonDocument doc(1024);
  doc["Id"]= Id ; 
  moisture.loop();
   if(isnan(moisture.moistureAnalog)){
      Serial.println("ERR moisture");
  }else {
    doc["Moisture"]= moisture.moisturePercent ;    
  }
  waterlvl.loop();
  if (isnan(waterlvl.reserve)) {
      Serial.println("ERR waterlvl");
  }else {
     doc["Waterlvl"]= waterlvl.reservePercent ;    
  }
  sensors_event_t event;
  dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
    Serial.println(F("Erreur lecture temperature!"));
  }else {
      doc["Temperature"]= event.temperature ;    
  }
  dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
    Serial.println(F("Erreur lecture humidite !"));
  }else {
     doc["Humidity"]= event.relative_humidity ;    
  }
    serializeJson(doc, Serial);
    Serial.println("");
}
