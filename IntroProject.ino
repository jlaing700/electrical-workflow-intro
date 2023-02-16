uint8_t led = 6;
uint8_t btn = 4;
bool btnFlag = true;
char inChar = '1';
uint8_t inVal = 9;
bool tgl = true;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(btn, INPUT);
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
      inChar = Serial.read();
      
      if (inChar >= '1' && inChar <= '9') {
        inVal = inChar - '0';
      }
  }

  if (digitalRead(btn) && !btnFlag) { tgl = !tgl; }

  analogWrite(led, inVal*25*tgl);
  btnFlag = digitalRead(btn);
  delay(50);
}
