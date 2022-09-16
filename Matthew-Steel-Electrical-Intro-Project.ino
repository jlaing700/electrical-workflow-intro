/* 
ATtiny 85 scematic: 
   top (has notch)
     _______
   -|Res  5V|-
  3-|A2   A1|-2
  4-|A3  PWM|-1
   -|GND PWM|-0
     -------
     
A1-3: Analog input
Res: Reset
GND: Ground
5V: 5 volt input
PWM: PWM output  
*/


int faded = 50; //percent brightness - 100 is brightest, 0 is off

const int ledPin = 0; //Attaches LED to PWM 
const int buttonPin = 4; //Attaches button to A3

int buttonState = false; //Set up for button toggle
int buttonPressed = false;
int state = 0;


void setup() {
  pinMode (ledPin, OUTPUT);
  pinMode (buttonPin, INPUT);
  buttonPressed = digitalRead(buttonPin);
}


void loop() {
  //detects when button is pressed
  buttonState = buttonPressed; 
  buttonPressed = digitalRead(buttonPin);
  
  //If the button is released, and was pressed down previously, the state is increased by 1
  if(buttonPressed == LOW && buttonState == HIGH){
    state += 1;
  }
  if(state >= 3){
    state = 0; 
  }


  //LED states: 0 = on, 1 = fade, anything else = off
  if(state == 0){
    digitalWrite(ledPin, HIGH);
  }
  else if(state == 1){
    //multiplies brightness by percentage set at the top - 255 is max brightness
    analogWrite(ledPin, (faded*255)/100);
  }
  else{ 
    digitalWrite(ledPin, LOW);  //turns the LED off 
  }
}
