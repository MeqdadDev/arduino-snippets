#define MQ2pin 0
#define ledPin 13
#define buzzerPin 7
#define motorPin 4  // A dc motor with relay connected to D4

float sensorValue; // variable to store sensor value

void setup()
{
    Serial.begin(9600); // sets the serial port to 9600
    Serial.println("Warming up!");
    pinMode(ledPin, OUTPUT);
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
        digitalWrite(ledPin, HIGH);
        digitalWrite(buzzerPin, HIGH);
        digitalWrite(motorPin, HIGH);
    }
    else
    {
        digitalWrite(ledPin, LOW);
        digitalWrite(buzzerPin, LOW);
        digitalWrite(motorPin, LOW);
    }
    delay(2000); // wait 2s for next reading
}
