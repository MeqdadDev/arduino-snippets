/* 
ESP8266 with DHT11 and ThingSpeak IoT Platform

By: MeqdadDev
*/

#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;

const char* ssid = "MySSID";   // Your Network SSID
const char* password = "MyPassword";       // Your Network Password

int val;
int pin = D3; // DHT Pin Connected at D3 Pin

WiFiClient client;

unsigned long myChannelNumber = 1295655; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "YOUR_WRITE_API_KEY"; //Your Write API Key

void setup()
{
  Serial.begin(9600);
  delay(300);
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);
}

void loop()
{
  val = digitalRead(pin); // Read DHT values
  Serial.print("Temperature: ");
  Serial.print(val);
  Serial.println("*C");
  delay(1000);
  ThingSpeak.writeField(myChannelNumber, 1,val, myWriteAPIKey); //Update in ThingSpeak
  delay(15000);
}