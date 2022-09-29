

int ButtonValue = 0;
int Button = 3;
int LED = 5;
const int DUTY = 255;
const int DUTY2 = 127;

void setup() {
  // put your setup code here, to run once:
  pinMode(Button,INPUT);
  pinMode(LED, OUTPUT);  
}

void loop() {
  // put your main code here, to run repeatedly:
  ButtonValue = digitalRead(Button);

  if(ButtonValue != 0){
    analogWrite(LED,DUTY2);
    }
  else{
    analogWrite(LED,DUTY);
    }
}
