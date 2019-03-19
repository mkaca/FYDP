#include <Time.h>
#include <TimeLib.h>

int sensorValue = 0;
int sensor2Value = 0;
int sensor3Value = 0;

#define valve1 5
#define valve2 6
#define valve3 7

void setup() {

  pinMode(valve1, OUTPUT);
  pinMode(valve2, OUTPUT);
  pinMode(valve3, OUTPUT);
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(A0); //CO
  sensor2Value = analogRead(A1); // WINSEN CO2
  sensor3Value = analogRead(A3); // O2 Me2O2
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.print(second());
  Serial.print("     ");
  Serial.print(sensorValue);
  Serial.print("    ");
  Serial.print(sensor2Value);
  Serial.print("    ");
  Serial.println(sensor3Value);
  delay(250);
/*
delay(2500);

digitalWrite(valve1, LOW);
digitalWrite(valve2, LOW);
delay(500);
digitalWrite(valve3, HIGH);
//toggle valves

delay(2500);

digitalWrite(valve1, HIGH);
digitalWrite(valve2, HIGH);
delay(500);
digitalWrite(valve3, LOW);
*/

}
