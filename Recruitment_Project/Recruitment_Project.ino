const int buttonPin = 8;
const int LEDPin = 6;
int counter = 0;
int A = 0; 

void setup() {
  pinMode(buttonPin, OUTPUT); 
  Serial.begin(9600);
}

void loop() {
  A = digitalRead(buttonPin);

  if(A == LOW)
  {
  delay(10);
  A = digitalRead(buttonPin);
    if(A == HIGH){
    counter = counter + 1;  
    }  
  }
  delay(1);
  Serial.println(counter);

  if(counter % 2 == 0){
    analogWrite(LEDPin, 255);
  }
  else{
  analogWrite(LEDPin, 255/2);
  }

}
