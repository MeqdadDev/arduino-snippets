/*
Pet Feeder System with Arduino

RTC, Servo, 4x4 Keypad and 16x2 LCD Screen
By: MeqdadDev
*/

#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <RTClib.h>

LiquidCrystal lcd(A0, A1, A2, 11, 12, 13);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
Servo myservo;

RTC_DS3231 rtc;
int feedingHour = 0;
int feedingMinute = 0;
bool feedingTimeSet = false;

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    rtc.begin();

    myservo.attach(10);
    lcd.begin(16, 2);

    Serial.println("Enter feeding time (HH:MM):");
}

void loop()
{
    char customKey = customKeypad.getKey();
    if (customKey)
    {
        handleKeypadInput(customKey);
    }

    DateTime now = rtc.now();
    if (now.hour() == feedingHour && now.minute() == feedingMinute)
    {
        feedPet();
    }

    if (feedingTimeSet)
    {
        displayCurrentTime(now);
    }

    delay(1000); // Wait for 1 second
}

void handleKeypadInput(char key)
{
    static bool waitingForMinute = false;
    static int hourDigits = 0;
    static int minuteDigits = 0;

    if (key >= '0' && key <= '9')
    {
        if (!waitingForMinute)
        {
            hourDigits = hourDigits * 10 + (key - '0');
            lcd.print(key);
        }
        else
        {
            minuteDigits = minuteDigits * 10 + (key - '0');
            lcd.print(key);
        }
    }
    else if (key == '#')
    {
        if (!waitingForMinute)
        {
            waitingForMinute = true;
            lcd.print(":");
        }
        else
        {
            feedingHour = hourDigits;
            feedingMinute = minuteDigits;
            lcd.clear();
            lcd.print("Feeding Time Set");
            lcd.setCursor(0, 1);
            lcd.print(feedingHour);
            lcd.print(":");
            lcd.print(feedingMinute);
            delay(2000);
            lcd.clear();
            waitingForMinute = false;
            hourDigits = 0;
            minuteDigits = 0;
            feedingTimeSet = true;
        }
    }
}

void feedPet()
{
    int val1 = 0;
    int val2 = 180;

    myservo.write(val2); // Open the servo
    lcd.print("Feeding...");
    delay(3000); // Wait for 3 seconds

    myservo.write(val1); // Close the servo
    lcd.clear();
}

void displayCurrentTime(DateTime now)
{
    lcd.setCursor(0, 0);
    lcd.print("Time: ");
    lcd.print(now.hour(), DEC);
    lcd.print(":");
    lcd.print(now.minute(), DEC);
    lcd.print(":");
    lcd.print(now.second(), DEC);
}