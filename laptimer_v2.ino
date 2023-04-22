#include <LiquidCrystal.h>

#define echoPin 8
#define trigPin 9

int maxdistance = 14;
int minlaptime = 5;
long duration;
int distance;
int lap = 0;
int recordlap = 1;
double laptime = 0;
double recordtime = 0;
double livelaptime = 0;
double totaltime_seconds;
double a;
double c;
double d;
double e;
int rs = 11;
int en = 12;
int d4 = 2;
int d5 = 3;
int d6 = 4;
int d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Welcome to");
  lcd.setCursor(0, 1);
  lcd.print("Arduino laptimer");
  delay(4000);
  lcd.clear();
  lcd.print("Start racing to");
  lcd.setCursor(0, 1);
  lcd.print("get started!");
}

void loop() {
  delay(10);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  while (lap < 1) {
    lcd.setCursor(0, 0);
    lcd.print("Start racing to");
    lcd.setCursor(0, 1);
    lcd.print("get started!");
    delay(10);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    if (distance < maxdistance) {
      lap++;
      a = millis();
      e = millis();
    }
  }

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
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Laptime:");
