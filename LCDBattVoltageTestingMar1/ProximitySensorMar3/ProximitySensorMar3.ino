#define echoPin 6
#define trigPin 7
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup(){
  lcd.begin(16, 2);
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);
}
void loop(){
  int duration;
  double distance;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin,HIGH);
  distance = (duration/2)/2.91;
  lcd.print(distance);
  lcd.print(" mm"); 
  delay(1000);
  lcd.clear();
}
  
