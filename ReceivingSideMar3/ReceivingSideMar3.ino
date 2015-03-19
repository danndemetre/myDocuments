#define trigPin 8
#define echoPin 9
#define lcdSwitch 6

#include <VirtualWire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 10;
const int transmit_en_pin = 3;

void setup(){
    //Setup proximity sensor
    pinMode(echoPin,INPUT);
    pinMode(trigPin,OUTPUT);  
    pinMode(lcdSwitch, INPUT);
    //Setup LCD screen
    lcd.begin(16, 2);
    lcd.clear();
    delay(1000);
    
    //Setup RF communications
    vw_set_tx_pin(transmit_pin);    // Initialise the IO and ISR
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100 
    vw_setup(2000);	 // Bits per sec 
    vw_rx_start();       // Start the receiver PLL running
    pinMode(led_pin, OUTPUT);
    lcd.setCursor(0, 1);
    delay(1000);
}

void loop(){
  if(digitalRead(lcdSwitch) == 1){
    updateDistance();
  }
  else{
    updateBattVolt();
  }
  delay(1000);
}

void updateBattVolt(){
    String getSerial = RFreceiveData();
    boolean gotData = false;
    int count = 0;
    while((gotData == false) && (count < 1000)){
      getSerial = RFreceiveData();
      if(getSerial.length() >10){
        gotData = true;
      }
     count += 1;
     if(count == 1000){
       getSerial = "No Communication";
     }
   }
      
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Battery Status");
    lcd.setCursor(0, 1);
    lcd.print(getSerial);
}

String RFreceiveData(){
    char saveBuf[20];
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
  
    if (vw_get_message(buf, &buflen)){
	int i;
      digitalWrite(led_pin, HIGH); // Flash a light to show received good message
	// Message with a good checksum received, dump it.
      for (i = 0; i < buflen; i++){
          saveBuf[i] = (char)buf[i];
	}
      digitalWrite(led_pin, LOW);
   }
   return saveBuf;
}

void updateDistance(){
  int duration;
  double distance;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin,HIGH);
  distance = (duration)/2.91;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Charge Distance");    
  lcd.setCursor(0,1);
  
  if(distance <= 75){
    lcd.print(distance);
    lcd.print(" mm"); 
  }
  else{
    lcd.print("Out of Range");
  }
}

