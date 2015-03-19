int dataIn = 0;
int coilPin = 5;

void setup(){
  Serial.begin(9600);
  
  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
  TCCR0B = _BV(CS00);
  
  pinMode(coilPin, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(3,OUTPUT);
  // In the next line of code, we:
  // 1. Set the compare output mode to clear OC2A and OC2B on compare match.
  //    To achieve this, we set bits COM2A1 and COM2B1 to high.
  // 2. Set the waveform generation mode to fast PWM (mode 3 in datasheet).
  //    To achieve this, we set bits WGM21 and WGM20 to high.
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);

  // In the next line of code, we:
  // 1. Set the waveform generation mode to fast PWM mode 7 —reset counter on
  //    OCR2A value instead of the default 255. To achieve this, we set bit
  //    WGM22 to high.
  // 2. Set the prescaler divisor to 1, so that our counter will be fed with
  //    the clock's full frequency (16MHz). To achieve this, we set CS20 to
  //    high (and keep CS21 and CS22 to low by not setting them).
  TCCR2B = _BV(WGM22) | _BV(CS20);

  // OCR2A holds the top value of our counter, so it acts as a divisor to the
  // clock. When our counter reaches this, it resets. Counting starts from 0.
  // Thus 63 equals to 64 divs.
  OCR2A = 94;
  // This is the duty cycle. Think of it as the last value of the counter our
  // output will remain high for. Can't be greater than OCR2A of course. A
  // value of 0 means a duty cycle of 1/64 in this case.
  OCR2B = 47;
}
void loop(){
  digitalWrite(8,LOW);
  analogWrite(coilPin,0);
  
  if(Serial.available()>0){
    dataIn = Serial.read();
    Serial.println(dataIn); //Test to see if we get three 'H's in a row
    if(dataIn == 'H'){
      dataIn = Serial.read();
      Serial.println(dataIn);
      if(dataIn == 'H'){
        dataIn = Serial.read();
        while(1){
          dataIn = Serial.read();
          analogWrite(coilPin,125);
        }
      }
    }
  }
}
