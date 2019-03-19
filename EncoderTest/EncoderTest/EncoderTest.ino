#include "EncoderKanary.h"

#define intrL 10
#define intrR 11

EncoderKanary posTrack = EncoderKanary(intrL, intrR);

void setup() {
  Serial.begin(9600);
}

void loop() {
  
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

}
