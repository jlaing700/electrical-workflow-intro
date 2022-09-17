#define LED 11  // The pin the LED is connected to (w/ pwm)
#define pushButton A0
int buttonPressed = 0;
int lightState = 250; // we use 250 here to make it cleanly turn off. It's not fully max brightness at 255, but it's very close 

void setup() {
  pinMode(LED, OUTPUT); // Declare the LED as an output
  pinMode(pushButton, INPUT); // button as input
}

void loop() {
  buttonPressed = digitalRead(pushButton);  
  delay(100);                       // have a slight delay 

   // Alter LED brightness with a button press
  if(digitalRead(pushButton) == LOW)
  {
    lightState = lightState - 25; // decrement by 25 each time to reach zero
    if(lightState < 0) // if value is below zero, reset the index
      lightState = 250;
  }
  
    if(lightState > 0) // if light state is greater than zero, then led can go on
    {
      analogWrite(LED,lightState);
    }
    else // otherwise, force it off 
    {
      digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
    }
}
