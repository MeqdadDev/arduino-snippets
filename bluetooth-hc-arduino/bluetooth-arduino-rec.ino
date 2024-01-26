/* 
Bluetooth HC-05 Module with Arduin Uno
Code for Receiver.

By: MeqdadDev
*/
const int ledPin = 13;  // Change this to the pin where your LED is connected
const int buzzerPin = 12;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();
    
    if (receivedChar == '1') {
      digitalWrite(ledPin, HIGH);  // Turn on the LED when '1' is received
      digitalWrite(buzzerPin, HIGH);  // Turn on the Buzzer when '1' is received
      delay(3000);  // Adjust the delay as needed
      digitalWrite(ledPin, LOW);  // Turn off the LED
      digitalWrite(buzzerPin, LOW);  // Turn off the Buzzer
    }
  }
  delay(50);  // Adjust the delay as needed
}
