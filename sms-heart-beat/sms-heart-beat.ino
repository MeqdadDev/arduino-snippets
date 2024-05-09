/*
Heart Rate and SMS Alarm System with Arduino

Pulse Sensor, OLED 0.96' Screen, Mini A6 GSM Board
By: MeqdadDev
*/

#include "U8glib.h"
#include <PulseSensorPlayground.h>
#include <SoftwareSerial.h>

#define USE_ARDUINO_INTERRUPTS true // Include necessary libraries
#define GSM_TX 2                    // Arduino pin 2 to UTX
#define GSM_RX 3                    // Arduino pin 3 to URX

SoftwareSerial sim(GSM_RX, GSM_TX); //
// The GSM
String number = "00970568098889"; //-> change with your number

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
unsigned long previousMillis = 0;
const long interval = 1000; // Update OLED every 1 second

// Constants
const int PULSE_SENSOR_PIN = 0; // Analog PIN where the PulseSensor is connected
const int THRESHOLD = 550;      // Threshold for detecting a heartbeat

// Create PulseSensorPlayground object
PulseSensorPlayground pulseSensor;

void printOLED(int bpm)
{
  u8g.setFont(u8g_font_9x18);
  u8g.drawStr(25, 10, "BPM: ");
  u8g.setFont(u8g_font_7x14);
  u8g.drawStr(5, 35, String(bpm).c_str());
}

void setup()
{
  // Initialize Serial Monitor
  Serial.begin(9600);

  Serial.println("System Started...");
  sim.begin(115200);
  delay(1000);

  Serial.println("Communicating GSM/GPS.....");

  // sms();   //send sms
  // call();  //call to us

  // Configure PulseSensor
  pulseSensor.analogInput(PULSE_SENSOR_PIN);
  pulseSensor.setThreshold(THRESHOLD);

  // Check if PulseSensor is initialized
  if (pulseSensor.begin())
  {
    Serial.println("PulseSensor object created successfully!");
  }
}

void loop()
{
  unsigned long currentMillis = millis();

  // Get the current Beats Per Minute (BPM)
  int currentBPM = pulseSensor.getBeatsPerMinute();
  Serial.print("Current BPM: ");
  Serial.println(currentBPM);

  // Check if a heartbeat is detected
  if (pulseSensor.sawStartOfBeat())
  {
    Serial.println("♥ A HeartBeat Happened!");
    Serial.print("BPM: ");
    Serial.println(currentBPM);

    // Update OLED screen at a specific interval
    if (currentMillis - previousMillis >= interval)
    {
      previousMillis = currentMillis;
      // picture loop
      u8g.firstPage();
      do
      {
        u8g.setFont(u8g_font_9x18);
        u8g.drawStr(25, 10, "BPM: ");
        u8g.setFont(u8g_font_7x14);
        u8g.drawStr(5, 35, String(currentBPM).c_str());
        // printOLED(currentBPM);
        u8g.setColorIndex(1);
      } while (u8g.nextPage());
    }
  }

  // Add a small delay to reduce CPU usage
  delay(250);
}

//----------- GSM Functions ------------------------

void sms()
{
  Serial.println("Sending Message");
  sim.println("AT+CMGF=1"); // Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println("Set SMS Number");
  sim.println("AT+CMGS=\"" + number + "\"\r"); // Mobile phone number to send message
  delay(1000);
  String SMS = "Sample SMS is sending....."; // sms content

  sim.println(SMS);

  delay(100);
  sim.println((char)26); // ASCII code of CTRL+Z
  delay(1000);
}

void call()
{
  sim.print(F("ATD"));
  sim.print(number);
  sim.print(F(";\r\n"));
}