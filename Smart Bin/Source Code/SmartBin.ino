#include <Servo.h>

Servo servo;
 
int echo = 9, trig = 10;
double distance, duration;
 
void setup()
{
  servo.attach(11);
  servo.write(0);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
} 
 
void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);

  distance = duration* 34 / 2000;

  if(distance <= 40)
  {
    servo.write(100);
    delay(5000);
  }
  
  servo.write(0);
  delay(200);
}
