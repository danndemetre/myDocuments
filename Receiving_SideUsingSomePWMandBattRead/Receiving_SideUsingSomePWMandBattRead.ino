#include <PWM.h>
//#include <Narcoleptic.h>
void setup(){

  pinMode(9,OUTPUT);
  int32_t frequency = 4000; //frequency (in Hz)void setup()
  //initialize all timers except for 0, to save time keeping functions
  InitTimersSafe(); 
  //sets the frequency for the specified pin
  bool success = SetPinFrequencySafe(3, frequency); 
}
void loop(){
  double totalVoltage =0;
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
//  Narcoleptic.delay(500);
  /*int duration;
  int distance;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin,HIGH);
  distance = (duration/2)*29.1;
  //bool success = SetPinFrequencySafe(3, frequency);
  pwmWrite(3, 128);
 // delay(5000);

}
