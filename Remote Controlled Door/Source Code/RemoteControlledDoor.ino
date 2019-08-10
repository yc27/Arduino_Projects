#include <Servo.h> 
Servo servo;

const int buttonPin = 3;
const int led = 4;

int val;
boolean currentState = LOW;
boolean lastState = LOW;
boolean pos = true;

void setup(){  
  servo.attach(5);
  servo.write(0);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void openDoor()
{
  for(int i = 0; i <= 120; ++i)
    servo.write(i);
}

void closeDoor()
{
  for(int i = 120; i >= 0; --i)
    servo.write(i);
}

void loop(){
  if(Serial.available() > 0)
  {
    val = Serial.read();
    
    if(val == 120)
    {
      pos = false;
      digitalWrite(led, HIGH);
      openDoor();
    }
    else
    {
      pos = true;
      digitalWrite(led, LOW);
      closeDoor();
    }
    delay(200);
  } 
  
  currentState = digitalRead(buttonPin);
  
  if (currentState == LOW && lastState == HIGH)
  {
    if (pos == true)
    {
      pos = false;
      digitalWrite(led, HIGH);
      openDoor();
    }
    
    else
    {
      pos = true;
      digitalWrite(led, LOW);
      closeDoor();
    }
    delay(200);
  }  
  lastState = currentState;
}
