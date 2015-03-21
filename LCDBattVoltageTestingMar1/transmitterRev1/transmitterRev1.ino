
#include <VirtualWire.h>
#include <PWM.h>

const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 2;
const int transmit_en_pin = 3;

void setup(){
    // Initialise the IO and ISR
    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);       // Bits per sec
    pinMode(led_pin, OUTPUT);
}

void loop(){
  RFtransmitData();
}

void RFtransmitData(){
  double battVoltage = getBattVoltage();
  String str;
  double fullDischarge = 8.1;
  double fullCharge = 9.6; //Volts
  if(battVoltage >= fullDischarge){
    str =  String(int(battVoltage*1000));
    str += " mV / ";
    double perCharge = ((battVoltage-fullDischarge)/(fullCharge-fullDischarge))*100;
    int perChargeInt = (int)perCharge;
    str += String(perChargeInt);
    str += "%";    
  }
 if(battVoltage > fullCharge){
    str = "Fully Charged";
  }
 if(battVoltage < fullDischarge){
    str = "Depleted";
  }
  char msg[100];
  str.toCharArray(msg, str.length()+1);
  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, str.length()+1);
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led_pin, LOW);
  delay(1000);
}

double getBattVoltage(){
  double totalVoltage =0;
  double avgVoltage;
  for(int i = 0; i<100; i++){
    double x = (double)analogRead(0);
    double voltage = (5*x)/1023;
    totalVoltage += voltage;
  }
  avgVoltage = totalVoltage/100;
  double battVoltage = (2*avgVoltage)/5+8;
  return battVoltage;
}
