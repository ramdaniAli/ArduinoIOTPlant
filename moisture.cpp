
#include "moisture.h"
//constructeur de la calasse moisture 
Moisture::Moisture() : 
//initialisaiton des variables a 0 
//moistureAnalog c'est la variable qui recupere les données depuis le port analogique relier au capteur de moisture
//moisturePercent c'est le pourcetage d'humidite dans le sol  
       moisturePercent(0.0f),  moistureAnalog(0)
{
  
}

void Moisture::loop() 
{
  moistureAnalog = analogRead(moisturePin);
  moisturePercent =(100 - ((moistureAnalog/1023.00)*100));
  
}
