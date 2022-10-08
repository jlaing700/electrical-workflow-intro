int button = 3; //Set button to be used as an input for pin 3
int led = 5; //Set led to be used as output for pin 5 (selected as a pin that supports PWM output, allowing brightness to be varied)
int state = 0; //State is set to 0 to represent the button not being pressed
int brightness = 255; //Led brightness value, 255 is max, 0 is min

void setup()
{
  pinMode(button, INPUT); //Set pin 3 to be an input
  pinMode(led, OUTPUT); //Set pin 5 to be an output
}

void loop()
{  
  analogWrite(led, brightness); //Set led to brightness value given 
  state = digitalRead(button); //Set state to read the pin input of the button

  //If button is pressed then turn off LED
  if(state == HIGH){   
    brightness = 0; //Set brightness to 0 to turn it off 
  }

  //If the button is not pressed, leave the LED at full brightness
  else{
    brightness = 255;    
  }  
}
