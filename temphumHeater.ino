
#include "DHT.h"
#include "JeeLib.h"
#define DHTPIN 7
#define DHTTYPE DHT22 // DHT 22 (AM2302)
#define PORT 2
Port port = Port(2);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
 Serial.begin(9600);
 Serial.println("DHTxx test!");
 port.mode(OUTPUT);
 dht.begin();
 port.digiWrite(HIGH);

}

void loop() {
 delay(2000);
 float h = dht.readHumidity();
 float t = dht.readTemperature();
 
 if (isnan(h) || isnan(t) ) {
   Serial.println("Failed to read from DHT sensor!");
   return;
 }
 if(t > 15){
    
    //port.digiWrite();
  
  }
 Serial.print("Humidity: ");
 Serial.print(h);
 Serial.print(" %\t");
 Serial.print("Temperature: ");
 Serial.print(t);
 Serial.print(" *C ");
 Serial.print("\n");
}


