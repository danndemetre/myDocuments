int dataIn = 0;
int coilPin = 5;

void setup(){
  Serial.begin(9600);
  
  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
  TCCR0B = _BV(CS00);
  
  pinMode(coilPin, OUTPUT);
  pinMode(8, OUTPUT);
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
          
