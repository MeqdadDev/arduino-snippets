/*
Automatic Parking System with Arduino

By: MeqdadDev
*/

#include <Servo.h>

// Define pin numbers for ultrasonic sensor
const int trigPin = 9;
const int echoPin = 10;

// Define pin number for servo motor
const int servoPin = 6;

// Define variables for duration and distance
long duration;
int distance;

// Create a servo object
Servo myServo;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Set trigPin as output and echoPin as input
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Attach the servo to its pin
  myServo.attach(servoPin);
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Send a 10 microsecond pulse to trigger the sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the duration of the pulse from echoPin
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2;
  
  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // If the distance is less than 13 cm, open the servo motor from 0 to 90 degrees
  if (distance < 13) {
    // for (int angle = 0; angle <= 90; angle++) {
      myServo.write(90);
      delay(3500);

      // delay(15); // Adjust the speed of servo movement
  } else {
    // If the distance is not less than 13 cm, keep the servo motor at 0 degrees
    myServo.write(0);
  }
  
  // Wait for a moment before taking the next measurement
  delay(500);
}
