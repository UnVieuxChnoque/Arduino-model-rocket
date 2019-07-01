#include <dht11.h> // charger la librairie
#include <EEPROM.h>

dht11 DHT11; // Créer le capteur

#define DHT11PIN 3 // Définir la pin utilisée

int addresse = 0;
void setup()
{
  // Initialiser la liaison série
  Serial.begin(9600);
}

void loop()
{
  Serial.print(" --- Nouvelle lecture --- ");

  int chk = DHT11.read(DHT11PIN); // Lecture du capteur

  Serial.print("Etat du capteur: ");

  switch (chk) // Est-ce que le capteur fonctionne?
  {
    case DHTLIB_OK: 
                Serial.println("OK"); 
                break;
    case DHTLIB_ERROR_CHECKSUM: 
                Serial.println("Checksum erreur"); 
                break;
    case DHTLIB_ERROR_TIMEOUT: 
                Serial.println("Time out erreur"); 
                break;
    default: 
                Serial.println("Erreur inconnue"); 
                break;
  }

  Serial.print("humidite: "); // Humidité
  Serial.println((float)DHT11.humidity, 3);

  Serial.print("Temperature: "); // Température
  Serial.println((float)DHT11.temperature, 3);

  delay(1000); // Pause avant prochaine lecture

  addresse++

}
