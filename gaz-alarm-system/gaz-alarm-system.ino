/*
Gaz/Smoke Alarm System

By: MeqdadDev
*/

#define MQ2pin 2
#define greenLedPin 9
#define redLedPin 13
#define buzzerPin 7
#define motorPin 4

float sensorValue; // variable to store sensor value

void setup()
{
    Serial.begin(9600); // sets the serial port to 9600
    Serial.println("Warming up!");
    pinMode(redLedPin, OUTPUT);
    pinMode(greenLedPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    pinMode(motorPin, OUTPUT);
    pinMode(MQ2pin, INPUT);
    delay(3000); // allow the MQ2 to warm up
}

void loop()
{
    sensorValue = digitalRead(MQ2pin); // read Gaz value from sensor

    Serial.print("MQ2 Sensor Value: ");
    Serial.println(sensorValue);

    if (!sensorValue)
    {
        digitalWrite(redLedPin, HIGH);
        digitalWrite(greenLedPin, LOW);
        digitalWrite(buzzerPin, HIGH);
        digitalWrite(motorPin, HIGH);
        delay(2000);
    }
    else
    {
        digitalWrite(greenLedPin, HIGH);
        digitalWrite(redLedPin, LOW);
        digitalWrite(buzzerPin, LOW);
        digitalWrite(motorPin, LOW);
    }
}
