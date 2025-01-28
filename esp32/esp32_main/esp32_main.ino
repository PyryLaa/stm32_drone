void setup(){
  Serial.begin(115200);
}

void loop(){
  while(1){
      Serial.print("{blue}");
      delay(1000);
      Serial.print("{red}");
      delay(1000);
      Serial.print("{orange}");
      delay(1000);
      Serial.print("{green}");
      delay(1000);
  }
}