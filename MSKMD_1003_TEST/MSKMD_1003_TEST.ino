
#include <MSKMD_1003.h>

#define in1R 7  
#define in2R 8  
#define sel0 10
#define pwmR 11

#define in1L 12  
#define in2L 13 
#define pwmL 15

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
 delayMicroseconds(10000);
 driveSystem.moveRobot(1, 45); // go straight at 45% duty cycle
 delayMicroseconds(10000);
 
 // Checks for errors / faults
 if(!driveSystem.stateOK())
 {
  Serial.println(driveSystem.stateOK());
 }
}


