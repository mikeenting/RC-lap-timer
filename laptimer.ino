// Sources
// Used the following as a basis: https://github.com/beaver-pc/RC-Lap-Timer/blob/master/Lap_Timer.ino

#include <LiquidCrystal.h>

#define echoPin 8  // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 9  //attach pin D3 Arduino to pin Trig of HC-SR04

// Adaptive variables
int maxdistance = 14;  // variable for setting the default distance in centimeters measured by the sensor
int minlaptime = 5;    // variable for setting the minimum time a lap should take (to prefent 'fraud')

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

  // Display current race time to dipslay
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
      lcd.setCursor(14, 0);
      lcd.print("L");
      lcd.setCursor(15, 0);
      lcd.print(lap);
      lcd.setCursor(14, 1);
      lcd.print("L");
      lcd.setCursor(15, 1);
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