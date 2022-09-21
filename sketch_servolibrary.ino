#include <Adafruit_TiCoServo.h>
#include <known_16bit_timers.h>
#include <avr/power.h>
Adafruit_TiCoServo myservo;
void setup(){
  #if (F_CPU == 16000000L)
    clock_prescale_set(clock_div_1);
  #endif
  pinMode(3,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  myservo.attach(9); //Note: there are specific pins that the servo accepts if the pin is ever incorrect it will not function.(TicoServo only)
}
void loop() {
  int buttonlpos;
  if(digitalRead(3)==LOW){
  myservo.write(10);
  }
  else if(digitalRead(6)==LOW){
  myservo.write(180);
  }
  else{
    myservo.write(90);
  }
  }
