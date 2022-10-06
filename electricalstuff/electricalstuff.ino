
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  11;     // the number of the LED pin
const int DUTY = 127;

int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
 
  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {
    digitalWrite(ledPin, HIGH);
    delay(1000);
    analogWrite(ledPin,DUTY);
    delay(1000);
    digitalWrite(ledPin, LOW);
  }
}
