// This #include statement was automatically added by the Particle IDE.
#include <ThingSpeak.h>
TCPClient client;

// This #include statement was automatically added by the Particle IDE.
#include "Adafruit_DHT.h"
#include "adafruit_DHT.h" //To include library when flashing to device

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);

unsigned long myChannelNumber = 1035524;		/*Thingspeak channel id*/
const char * myWriteAPIKey = "O34LCVLOCVACFOUH";/*Channel's write API key*/

int led = D7;  // The on-board LED
float hum, temp;

void setup()
{
  ThingSpeak.begin(client);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
  digitalWrite(led, HIGH);          // LED High, indicates measurement being taken
  temp = dht.getTempCelcius();      // Measurement is taken from DHT-22 sensor
  delay(1000);                      // Delay til LED Low
  digitalWrite(led, LOW);           // LED Low indicates no measurement
  ThingSpeak.writeField(myChannelNumber, 1, temp, myWriteAPIKey);   // Measurement is sent to ThingSpeak field 1
  
  delay(14000);                     // Delay allows uninterrupted transmission of temp, before next measurement taken.
    
  digitalWrite(led, HIGH);          // LED High, indicates measurement being taken
  hum = dht.getHumidity();          // Measurement is taken from DHT-22 sensor
  delay(1000);                      // Delay til LED Low
  digitalWrite(led, LOW);           // LED Low indicates no measurement 
  ThingSpeak.writeField(myChannelNumber, 2, hum, myWriteAPIKey);    // Measurement is sent to ThingSpeak field 2

  delay(14000);                     // Delay allows uninterrupted transmission of humidity, before next measurement taken.
  
}