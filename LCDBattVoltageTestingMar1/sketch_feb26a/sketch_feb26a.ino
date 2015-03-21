#define  trigPin 2
#define echoPin 4
#include <PWM.h>
#include <Narcoleptic.h>
void setup(){
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(3,OUTPUT);
  int32_t frequency = 100; //frequency (in Hz)void setup()
  Serial.begin(9600);
  //initialize all timers except for 0, to save time keeping functions
  InitTimersSafe(); 
  //sets the frequency for the specified pin
  bool success = SetPinFrequencySafe(3, frequency);
}

void loop(){
/*  double totalVoltage =0;
  double avgVoltage;
  for(int i = 0; i<1000; i++){
    double x = (double)analogRead(0);
    double voltage = (5*x)/1023;
    totalVoltage += voltage;
  }
  avgVoltage = totalVoltage/1000;
  double battVoltage = (2*avgVoltage)/5+8;
  Serial.println(battVoltage);
  int duty;
  if (battVoltage >=8 && battVoltage <=10){
    duty = (256/2)*(10-battVoltage);
    pwmWrite(3, duty);
  }
  delay(1000);
//  Narcoleptic.delay(500);*/
  int32_t duration;
  int32_t distance;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin,HIGH);
  distance = (duration/2)/2.91; //mm
  InitTimersSafe(); 
  int32_t frequency = distance*1000; //frequency (in Hz)void setup()
  bool success = SetPinFrequencySafe(3, frequency);
  pwmWrite(3, 128);
  delay(5000);
}
