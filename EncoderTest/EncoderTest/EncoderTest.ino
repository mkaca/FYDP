//#include <EncoderKanary.h>
#include <TimeLib.h>

#define intrL 10
#define intrR 11

// for interrupt encoder
// Wheel is going STRAIGHT if coutner is positive
volatile unsigned long rRotsLocal, lRotsLocal;

// init static variables
int currentPosX = 0;
int currentPosY = 0;
int currentPosYaw = 0;

bool directionCWR = 1;
bool directionCWL = 0;

// init encoder to go forward FIRST: left wheel = 0, right wheel = 1 with 8 magnets
float wheelBase = 25.5 * 2.54;
float wheelDiam = 8 * 2.54;
int numOfMagnets = 8;
//EncoderKanary encoderInst = EncoderKanary(intrL, intrR, false, true, 8, wheelDiam, bodyBase);

/*
 * motor driver to be updated so that it returns CWL and CWR directions 
 */



// updates leftCounter
void updateLeft(){
  if (directionCWL == 0)
    {lRotsLocal++;}
  else {lRotsLocal--;}
}

// updates rightCounter
void updateRight(){
  if (directionCWR == 1)
    {lRotsLocal++;}
  else {lRotsLocal--;}
}

//resets counter
void reset(){
  lRotsLocal = 0;
  rRotsLocal = 0;
}

// TODO: add currentX,Y,Yaw in 3 int calculations somewhere
// Input: 3 current positions
void updateCurrentPosition(int &curPosX, int &curPosY, int &curPosYaw)
{
  //This will convert the current motor rotations into x and y coordinates in cm
  int lDist = (lRotsLocal * M_PI * wheelDiam) / numOfMagnets;
  int rDist = (rRotsLocal * M_PI * wheelDiam) / numOfMagnets;

  /*
  Assuming the robot travels in an arc and knowing how far each wheel travels
  can build two arcs sharing center and angle and thus determine turnRadius
  then convert into XY coordinates using starting location as origin
  */

  int turnRadius = (lDist * wheelBase) / (rDist - lDist);

  ////
  // ADD previous positions into here somewhere
  ///////
  //////
  int yaw = lDist/(M_PI * turnRadius * 2) * 360;
  int yCoord = (turnRadius + (0.5 * wheelBase)) * sin(yaw) ;
  int xCoord = (turnRadius + (0.5 * wheelBase)) - (turnRadius + (0.5 * wheelBase)) * cos(yaw);

  curPosX = xCoord;
  curPosY = yCoord;
  curPosYaw = yaw;

  // resets position to prevent position arrray from amalgamating error
  reset();
}

void setup() {
  reset(); // sets encoder counts to 0
  Serial.begin(9600);
  pinMode(intrL, INPUT_PULLUP);
  pinMode(intrR, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(intrR), updateRight, RISING);
  attachInterrupt(digitalPinToInterrupt(intrL), updateLeft, RISING);
}

void loop() {
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.print(second());
  Serial.print("     ");
  Serial.println(currentPosX);
  Serial.println(currentPosY);
  Serial.println(currentPosYaw);
  Serial.println(" ");
  updateCurrentPosition(currentPosX,currentPosY,currentPosYaw);

delay(200);

}
