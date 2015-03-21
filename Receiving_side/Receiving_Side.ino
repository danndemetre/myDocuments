int i = 0;

void setup(){
  Serial.begin(9600);
}

void loop(){
  for(i = 1; i<1000; i++){
    Serial.write('H'); //Send 'H's to initiate
  }
  for(i = 1; i<1000; i++){
    Serial.write('B'); //Send 'B's to terminate
  }
}
