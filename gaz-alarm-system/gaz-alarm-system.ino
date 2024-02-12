/*
Gaz/Smoke Alarm System

By: MeqdadDev
*/

#define MQ2pin 0
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
    delay(20000); // allow the MQ2 to warm up
}

void loop()
{
    sensorValue = analogRead(MQ2pin); // read Gaz value from sensor

    Serial.print("MQ2 Sensor Value: ");
    Serial.println(sensorValue);

    if (sensorValue >= 360)
    {
        digitalWrite(redLedPin, HIGH);
        digitalWrite(greenLedPin, LOW);
        digitalWrite(buzzerPin, HIGH);
        digitalWrite(motorPin, HIGH);
    }
    else
    {
        digitalWrite(greenLedPin, HIGH);
        digitalWrite(redLedPin, LOW);
        digitalWrite(buzzerPin, LOW);
        digitalWrite(motorPin, LOW);
    }
    delay(2000); // wait 2s for next reading
}
