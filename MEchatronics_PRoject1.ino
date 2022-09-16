
int LEDpin=3;
int bright=255;
int half=127;
int buttonPin=2;
int buttonRead;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(LEDpin,OUTPUT);
pinMode(buttonPin,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
buttonRead=digitalRead(buttonPin);
Serial.println(buttonRead);
if(buttonRead==1) {analogWrite(LEDpin,bright);
}
if(buttonRead==0){analogWrite(LEDpin,half);}


}
