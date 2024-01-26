const int buttonPin = 8;  // Change this to the pin where your button is connected
int buttonState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    Serial.write('1');  // Sending '1' when the button is pressed
    delay(500);  // Debounce delay
  }

  delay(100);  // Adjust the delay as needed
}
// +ADDR:21:13:55B8