const int ledPin = 9;
const int butPin = 12;
int ledState = 0;
int ledBright;
int butNew;
int butOld = 1;
int delayT = 100;

char myBright;
String brightLevel = "Enter your brightness level: ";
String msg2 = "Brightness level: ";



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(ledPin, OUTPUT);
pinMode(butPin, INPUT);


Serial.println("Enter letter for brightness level: ");
}

void loop() {
  // put your main code here, to run repeatedly:
ledBright = 255;

butNew = digitalRead(butPin);
if(butOld==0 && butNew==1){
  if(ledState == 0){
    digitalWrite(ledPin, ledBright);
    ledState = 1;
  }
  else{
    digitalWrite(ledPin, LOW);
    ledState = 0;
  }
}
butOld = butNew;

if(Serial.available() > 0){
  char comdata = char(Serial.read());
  
  if(comdata == 'A'){
    Serial.println("Brightness Level = 0%");
    ledBright = 0;
    analogWrite(ledPin, 0);
  }

   if(comdata == 'B'){
    Serial.println("Brightness Level = 20%");
    ledBright = 51;
    analogWrite(ledPin, ledBright);
  }

    if(comdata == 'C'){
    Serial.println("Brightness Level = 40%");
    ledBright = 102;
    analogWrite(ledPin, ledBright);
  }

    if(comdata == 'D'){
    Serial.println("Brightness Level = 60%");
    ledBright = 153;
    analogWrite(ledPin, ledBright);
  }

    if(comdata == 'E'){
    Serial.println("Brightness Level = 80%");
    ledBright = 204;
    analogWrite(ledPin, ledBright);
  }

    if(comdata == 'F'){
    Serial.println("Brightness Level = 100%");
    ledBright = 255;
    analogWrite(ledPin, 255);
  }

   if(comdata == '?'){
    Serial.print("Current Brightness Level = ");
    Serial.println(ledBright);
  }

  
}

}
