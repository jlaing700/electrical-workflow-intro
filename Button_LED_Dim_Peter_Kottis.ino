int led = 3; //Set led to pin 3
int button = 2; //Set button to pin 2
int state = 0; //Set state to be 0 for the button
int brightness = 255; //This will keep track of the brightness level

void setup()
{
  pinMode(button, INPUT); //Set pin 2 to be an input
  pinMode(led, OUTPUT); //Set pin 3 to be an output
}

void loop()
{
  
  analogWrite(led, brightness); //Set led to be the value of the brightness
  state = digitalRead(button); //Set state to read the pin input of the button

  //If button is pressed then decrease brightness
  if(state == HIGH){
    
    brightness = brightness - 189; //Decrement brightness using recursion (-189)
      
  }

  //If brightness reaches 0 value then set brightness back to 255 and have LED at 100%
  if(brightness < 0){
    brightness = 255;
    analogWrite(led, brightness);
    
  }
  delay(200); //Delay by 200 millisecond(s)
}
