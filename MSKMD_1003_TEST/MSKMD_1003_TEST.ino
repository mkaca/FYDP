
#include <MSKMD_1003.h>

#define in1R 52  
#define in2R 53 
#define pwmR 2

#define in1L 31
#define in2L 30 
#define pwmL 3

// initialize the driver
MSKMD_1003 driveSystem(in1L, in2L, pwmL, in1R, in2R, pwmR);
//initialize controller

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  driveSystem.begin();

}

void loop() {
 driveSystem.stop();
 delay(4000);
 driveSystem.moveRobot('1', 10); // go straight at 45% duty cycle
 delay(4000);

 /*
 // Checks for errors / faults
 if(!driveSystem.stateOK())
 {
  Serial.println(driveSystem.stateOK());
 }
 */
}


