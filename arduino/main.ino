#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial MyBlue(2, 3); //rx2, tx3
const unsigned int MAX_MESSAGE_LENGTH = 12;

//#define mq2Pin A0
#define phSensorPin A0
#define Offset 0.00

float mq2value;


// gaz
//float mq2() {
//  mq2value = analogRead(mq2Pin);
//  return mq2value;
//}

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
      Serial.println("pobiera");
      if (strcmp(message, "read") == 0) {
        MyBlue.print("CPH ");
        MyBlue.print(phSensor());
        MyBlue.print("\n");
      }


      //Reset for the next message
      message_pos = 0;
    }
  }
}
