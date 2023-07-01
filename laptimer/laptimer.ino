// This includes the LiquidCrystal library, which is used to control the LCD display.
#include <LiquidCrystal.h>

#define echoPin 8  // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 9  // attach pin D3 Arduino to pin Trig of HC-SR04

// Adaptive variables
int maxdistance = 15;  // variable for setting the default distance in centimeters measured by the sensor
int minlaptime = 5;    // variable for setting the minimum number of seconds a lap should take (to prevent invalid laps from being registered)
int maxlaps = 3;      // variable for setting the maximum number of laps the timer should register. Do not set higher than 99, to prevent the lap numbers from rolling off the LCD screen.

// Defines variables
long duration;      // variable for the duration of sound wave travel
int distance;       // variable for the distance measurement
int lap = 0;        // variable for counting the amount of laps
int recordlap = 1;  // variable for counting which lap the fastest lap was set
double laptime = 0;
double recordtime = 0;
double livelaptime = 0;
double totaltime_seconds;
double a;
double c;
double d;
double e;
// Define LCD variables
int rs = 11;
int en = 12;
int d4 = 2;
int d5 = 3;
int d6 = 4;
int d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Finish Flag
byte flag1[8] = {
  B11111,
  B00000,
  B11111,
  B00000,
  B11111,
  B00000,
  B11111,
  B00000
};

byte flag2[8] = {
  B00000,
  B11111,
  B00000,
  B11111,
  B00000,
  B11111,
  B00000,
  B11111
};

void setup() {
  // Setup ultrasonic sensor HC-SR04
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);   // Sets the echoPin as an INPUT

  // Setup serial monitor
  Serial.begin(9600);                             // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Welcome to Arduino laptimer");  // print some text in Serial Monitor

  // Setup LCD
  lcd.begin(16, 2);               // set up number of columns and rows
  lcd.setCursor(0, 0);            // move cursor to   (0, 0)
  lcd.print("Welcome to");        // print message at (0, 0)
  lcd.setCursor(0, 1);            // move cursor to   (0, 0)
  lcd.print("Arduino laptimer");  // print message at (0, 0)
  delay(4000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Start racing to");
  lcd.setCursor(0, 1);
  lcd.print("get started!");

  lcd.createChar(0, flag1);  // Creates custom character and stores it in the LCD's memory
  lcd.createChar(1, flag2);  // Creates second custom character
}
void loop() {
  delay(10);
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;  // Speed of sound wave divided by 2 (go and back)

  // This loop is used to wait for the first lap to start.
  // It continuously measures the distance until the distance is less than maxdistance, indicating that the first lap has started.
  while (lap < 1) {
    lcd.setCursor(0, 0);
    lcd.print("Start racing to");
    lcd.setCursor(0, 1);
    lcd.print("get started!");
    delay(10);
    // Clears the trigPin condition
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2;  // Speed of sound wave divided by 2 (go and back)
    if (distance < maxdistance) {
      lap++;
      a = millis();
      e = millis();
    }
  }

  while (lap <= maxlaps) {
    // Clears the trigPin condition
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2;  // Speed of sound wave divided by 2 (go and back)


    // Display current race time to display
    d = millis();
    c = millis();
    totaltime_seconds = (d - e) / 1000;
    livelaptime = (c - a) / 1000;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Lap:");
    lcd.setCursor(6, 0);
    lcd.print(lap);
    lcd.setCursor(0, 1);
    lcd.print("Time:");
    lcd.setCursor(6, 1);
    lcd.print(livelaptime);
    delay(10);

    // Lap timer
    // This conditional block is executed when the distance is less than maxdistance, indicating that a lap has ended.
    // It then checks whether the lap time is more than the minimum lap time.
    // If it is, it updates the record time if necessary, increments the lap count, and displays the lap time and record time on the LCD.
    if (distance < maxdistance) {
      c = millis();
      laptime = (c - a) / 1000;
      if (laptime > minlaptime) {
        if (recordtime == 0) {
          recordtime = laptime;
        }
        if (laptime < recordtime) {
          recordtime = laptime;
          recordlap = lap;
        }

        Serial.print("Lap: ");
        Serial.print(lap);
        Serial.print("\t\t");
        Serial.print("Laptime: ");
        Serial.print(laptime);
        Serial.print("\t\t");
        Serial.print("Lap record: ");
        Serial.print(recordtime);
        Serial.print("\t\t");
        Serial.print("Total time: ");
        Serial.println(totaltime_seconds);
        a = millis();
        // Write information to LCD Display
        lcd.clear();
        lcd.setCursor(0, 0);  // move cursor to   (0, 0)
        lcd.print("Time:");
        lcd.setCursor(6, 0);
        lcd.print(laptime);
        lcd.setCursor(0, 1);
        lcd.print("Rec:");
        lcd.setCursor(6, 1);
        lcd.print(recordtime);
        lcd.setCursor(13, 0);
        lcd.print("L");
        lcd.setCursor(14, 0);
        lcd.print(lap);
        lcd.setCursor(13, 1);
        lcd.print("L");
        lcd.setCursor(14, 1);
        lcd.print(recordlap);
        delay(3000);
        lcd.clear();
        lap++;
        if (lap == 11) {
          Serial.print("Average time per lap over past 10 laps:");
          Serial.print("\t\t");
          Serial.println(totaltime_seconds / 10);
        }
      }
    }
  }
  while (lap > maxlaps) {
    // Display flag pattern on the first half of the LCD
    for (int i = 0; i < 2; i++) {    // For each row
      for (int j = 0; j < 8; j++) {  // For each column in the first half
        lcd.setCursor(j, i);
        if (j % 2 == i % 2) {
          lcd.write((uint8_t)0);
        } else {
          lcd.write((uint8_t)1);
        }
      }
    }

    // Display 'Finish' and fastest time on the second half of the LCD
    lcd.setCursor(9, 0);  // Set cursor at 9th column of the first row
    lcd.print("Finish!");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Record:");
    lcd.setCursor(0, 1);
    lcd.print(recordtime);
    lcd.setCursor(13, 1);
    lcd.print("L");
    lcd.setCursor(14, 1);
    lcd.print(recordlap);
    delay(3000);
    lcd.clear();
  }
}