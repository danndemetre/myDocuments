/*
  LiquidCrystal Library - Hello World
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>
#include <PWM.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  pinMode(9,OUTPUT);
  int32_t frequency = 4000; //frequency (in Hz)void setup()
  //initialize all timers except for 0, to save time keeping functions
  InitTimersSafe(); 
  //sets the frequency for the specified pin
  bool success = SetPinFrequencySafe(3, frequency); 
}

void loop() {
  //pwmWrite(9, 0);
  double totalVoltage =0;
  double avgVoltage;
  for(int i = 0; i<100; i++){
    double x = (double)analogRead(0);
    double voltage = (5*x)/1023;
    totalVoltage += voltage;
  }
  avgVoltage = totalVoltage/100;
  double battVoltage = (2*avgVoltage)/5+8;
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  double fullDischarge = 8.1;
  double fullCharge = 9.6; //Volts
  if(battVoltage >= fullDischarge){
    lcd.clear();
    lcd.print("Battery Status");
    lcd.setCursor(0, 1);
    lcd.print(battVoltage); 
    lcd.print(" V / ");
    double perCharge = ((battVoltage-fullDischarge)/(fullCharge-fullDischarge))*100;
    int perChargeInt = (int)perCharge;
    lcd.print(perChargeInt);
    lcd.print(" %");
  }
  if(battVoltage > fullCharge){
    lcd.clear();
    lcd.print("Battery Status");
    lcd.setCursor(0, 1);
    lcd.print("Fully Charged");
  }
  if(battVoltage <8.1){
    lcd.clear();
    lcd.print("Battery Status");
    lcd.setCursor(0, 1);
    lcd.print("Depleted");
  }
  int duty;
  if (battVoltage >=8 && battVoltage <=10){
    duty = (256/2)*(10-battVoltage);
    pwmWrite(9, duty);
  }
  delay(1000); 
}

