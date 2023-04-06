#include <Wire.h>
#include <SoftwareSerial.h>
#include <Stepper.h>
#include <string.h>

const int stepsPerRevolution = 200;

SoftwareSerial MyBlue(2, 3); //rx2, tx3
Stepper myStepper(stepsPerRevolution, 4, 5, 6, 7);
const unsigned int MAX_MESSAGE_LENGTH = 12;

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
    static char message[MAX_MESSAGE_LENGTH];
    static unsigned int message_pos = 0;
    
    char inByte = MyBlue.read();
    if ( inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1) )
    {
      message[message_pos] = inByte;
      message_pos++;
    }
    // Gdy odebrana cala wiadomosc
    else
    {
      message[message_pos] = '\0';

      if (strcmp(message, "read") == 0) {
        // CPH - czujnik PH w aplikacji
        Serial.println("Wysylam czujniki");
        MyBlue.print("CPH ");
        MyBlue.print(phSensor());
        MyBlue.print("\n");
      }
      // podnies kabel
      if (strcmp(message, "up") == 0) {
        Serial.println("Podnosze kabel");
        myStepper.step(-stepsPerRevolution);
      }
      // opusc kabel
      if (strcmp(message, "down") == 0) {
        Serial.println("Opuszczam kabel");
        myStepper.step(-stepsPerRevolution);
      }
      message_pos = 0;
    }
  }
}
