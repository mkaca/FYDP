#include <EncoderKanary.h>
#include <TimeLib.h>

#define intrL 10
#define intrR 11

// init encoder to go forward FIRST: left wheel = 0, right wheel = 1 with 8 magnets
EncoderKanary posTrack = EncoderKanary(intrL, intrR, 0, 1, 8 * 2.54, 25.5 * 2.54);

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
  Serial.println("TEST");

delay(200);

}
