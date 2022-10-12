// constants don't change
const int BUTTON_PIN = 10; // Arduino pin connected to button's pin
const int LED_PIN    = 6; // Arduino pin connected to LED's pin

// variables will change:
int ledState = LOW;     // the current state of LED
int lastButtonState;    // the previous state of button
int currentButtonState; // the current state of button
int brightness; // brightness of LED

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); // set arduino pin to input pull-up mode
  pinMode(LED_PIN, OUTPUT);          // set arduino pin to output mode
}

void loop() {
  lastButtonState = currentButtonState;      // save the last state
  currentButtonState = digitalRead(BUTTON_PIN); // read new state
  digitalWrite(LED_PIN, ledState);
  analogWrite(LED_PIN, brightness);

  if(lastButtonState == HIGH && currentButtonState == LOW) {
    brightness = 255;     // %100 duty cycle
    ledState = !ledState; // toggle state of LED
  }
  else
  {
    brightness = 127;     // %50 duty cycle
  }
}
