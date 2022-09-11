#define LED_PIN 9
#define BUTTON_PIN 7
int brightness = 0; 
int fadeAmount = 5;
void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}
void loop() {
  if (digitalRead(BUTTON_PIN) == HIGH) {
    analogWrite(LED_PIN, brightness);

    brightness = brightness + fadeAmount;
    
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
    delay(50);
  }
  else {
    digitalWrite(LED_PIN, LOW);
  }
}
