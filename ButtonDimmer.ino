//Pin 8: Input for reading the button
//Pin 6: Output for controlling LED brightness

int ButtonValue = 0;

int Button = 8;
int LED = 6;

void setup() {
  // put your setup code here, to run once:

  pinMode(LED, OUTPUT);
  pinMode(Button, INPUT);


}

void loop() {
  // put your main code here, to run repeatedly:

  ButtonValue = digitalRead(Button);

  if(ButtonValue != 0) {
    //if button is pressed lower brightness (50%)
    analogWrite(LED, 127);
  }
  //else if the button is not pressed keep brightness
  else{digitalWrite(LED, HIGH);
    
  }
}
