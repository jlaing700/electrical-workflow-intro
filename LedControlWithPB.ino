// C++ code
// LED control with PushButton

#define pin_LED 3
#define pin_PB 2

void setup()
{
  pinMode(pin_LED, OUTPUT);
  pinMode(pin_PB, INPUT);
}

void loop()
{
  if (digitalRead(pin_PB)){
    digitalWrite(pin_LED, HIGH);}
  else{
    digitalWrite(pin_LED, LOW);}
}
