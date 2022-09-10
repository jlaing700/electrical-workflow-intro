// C++ code
// LED brightness control with PushButton

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
    analogWrite(pin_LED, 128);} //50% brightness
  else{
    analogWrite(pin_LED, 255);} //100% brightness
}
