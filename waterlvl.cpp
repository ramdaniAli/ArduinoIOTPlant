
#include "waterlvl.h"

//constructeur de la calasse waterlvl 
Waterlvl::Waterlvl() : 
//initialisaiton des variables a 0 
//reserve c'est la variable qui recupere les données depuis le port analogique relier au capteur de decteur de niveau d'eau 
//reservePercent c'est le niveaur d'eau disponible dans le reservoir d'eau en porcentage 
   reservePercent(0.0f),  reserve(0)
{
  
}
void Waterlvl::loop() 
{ 
 reserve = analogRead(waterlvlPin);
 reservePercent = (reserve/500)*100 ;
}
