#include <Wire.h>
#include <SoftwareSerial.h>
#include <Stepper.h>
#include <string.h>

const int stepsPerRevolution = 200;

SoftwareSerial MyBlue(2, 3); //rx2, tx3
Stepper myStepper(stepsPerRevolution, 4, 5, 6, 7);
const unsigned int MAX_MESSAGE_LENGTH = 12;
int previous = 0;

#define phSensorPin A0
#define Offset 0.00

// czujnik PH
float phSensor() {
  static float pHValue, voltage;
  voltage = analogRead(phSensorPin) * 5.0 / 1024;
  pHValue = 3.5 * voltage + Offset;
  return pHValue;
}

void setup() {
  Serial.begin(9600);
  MyBlue.begin(9600);
  myStepper.setSpeed(60);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  while (MyBlue.available() > 0)
  {
    //Create a place to hold the incoming message
    static char message[MAX_MESSAGE_LENGTH];
    static unsigned int message_pos = 0;

    //Read the next available byte in the serial receive buffer
    char inByte = MyBlue.read();

    //Message coming in (check not terminating character) and guard for over message size
    if ( inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1) )
    {
      //Add the incoming byte to our message
      message[message_pos] = inByte;
      message_pos++;
    }
    //Full message received...
    else
    {
      //Add null character to string
      message[message_pos] = '\0';

      //Print the message (or do other things)
      // CPH - czujnik PH w aplikacji
      Serial.println("odczytuje dane");
      if (strcmp(message, "read") == 0) {
        MyBlue.print("CPH ");
        MyBlue.print(phSensor());
        MyBlue.print("\n");
      }
      if (strcmp(message, "up") == 0) {
        myStepper.step(-stepsPerRevolution);
      }
      if (strcmp(message, "down") == 0) {
        myStepper.step(-stepsPerRevolution);
      }
      //Reset for the next message
      message_pos = 0;
    }
  }
}
