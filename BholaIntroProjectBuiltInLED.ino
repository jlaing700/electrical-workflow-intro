void setup()
{
pinMode(LED_BUILTIN, OUTPUT); //Set on-board LED to output
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH); //Turn LED on
  delay(1000); //Wait for 1000 millisecond(s)
  digitalWrite(LED_BUILTIN, LOW); //Turn LED off
  delay(1000); //Wait for 1000 millisecond(s)
}
