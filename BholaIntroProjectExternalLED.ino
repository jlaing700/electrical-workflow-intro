int led0 = 8;

void setup() {

  pinMode(8,OUTPUT); //Set pin 8 of microcontroller to an output
  
}

void loop() {
  
  digitalWrite(led0,HIGH); //Turn LED on
  delay(1000); //Wait for 1000 millisecond(s)
  digitalWrite(led0,LOW); //Turn LED off
  delay(1000); //Wait for 1000 millisecond(s)
  
}
