#include <Time.h>
#include <TimeLib.h>

int sensorValue = 0;
//int sensor2Value = 0;
//int sensor3Value = 0;

#define valve1 6
#define valve2 7

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(A1); //NDIR O2
  //sensor2Value = analogRead(A0); // WINSEN CO
  //sensor3Value = analogRead(A2); // O2 Me2O2
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.print(second());
  Serial.print("     ");
  Serial.println(sensorValue);
//  Serial.print("    ");
//Serial.print(sensor2Value);
//  Serial.print("    ");
//Serial.println(sensor3Value);

delay(2500);

//toggle valves


delay(2500);
}
