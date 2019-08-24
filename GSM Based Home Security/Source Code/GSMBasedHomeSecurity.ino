#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 8);

int PIR = 3;                    // the pin that the sensor is atteched to
int ledCircuitStatus = 4;       // the pin that the Green LED is atteched to
int ledSensorStatus = 5;        // the pin that the RED LED is atteched to
int btnToggle = 10;             // the pin that the Enable/Disable button is atteched to
int btnBell = 11;               // the pin that the Bell button is atteched to

boolean currentState = LOW;
boolean lastState = LOW;
boolean flag = false;           // initially sensor off

void setup() {
  pinMode(PIR, INPUT);
  pinMode(ledCircuitStatus, OUTPUT);
  pinMode(ledSensorStatus, OUTPUT);
  Serial.begin(9600);
  
  mySerial.begin(9600);
  delay(5000);
  Serial.println("Ready");
  digitalWrite(ledCircuitStatus, HIGH);
  
  pinMode(btnToggle,INPUT_PULLUP);
  pinMode(btnBell,INPUT_PULLUP);
  digitalWrite(ledSensorStatus, LOW);
}


void loop(){  
  bool bell = digitalRead(btnBell);
  if(bell == LOW)                                         // Bell button Pressed
  {
    makeCall();
    sendText("There's somebody at the door!!!");
  }

  
  currentState = digitalRead(btnToggle);
  if(currentState==LOW and lastState==HIGH)
  {
    if(flag)
    {
      digitalWrite(ledSensorStatus, LOW);                 // Turn LED OFF
      flag = false;                                       // Disable Sensor
    }
    else
    {
      digitalWrite(ledSensorStatus, HIGH);                // Turn LED ON
      flag = true;                                        // Enable Sensor
    }
  }
  
  if(digitalRead(PIR)==HIGH and flag==true) {             // check if the Sensor is HIGH and is Enabled
    Serial.println("Motion detected!");

    makeCall();
    sendText("There's somebody inside the house!!!");
  }
  lastState = currentState;
}

void makeCall() {
  Serial.println("Calling...");
  mySerial.println("ATD + +8801779882804;");
  delay(100);
  mySerial.println();
  
  delay(30000);
  mySerial.println("ATH");                                // Hang Up Call
  Serial.println("Done");
}

void sendText(String txt) {
  Serial.println("Sendig Message...");
  mySerial.println("AT+CMGF=1");                          // Sets the GSM Module in Text Mode
  delay(500);    
  mySerial.println("AT+CMGS=\"+8801779882804\"\r");       // Receiver Mobile Number
  delay(500);

  mySerial.println(txt);
  delay(500);
  mySerial.println((char)26);                             // ASCII code of CTRL+Z
  Serial.println("Done");
}
