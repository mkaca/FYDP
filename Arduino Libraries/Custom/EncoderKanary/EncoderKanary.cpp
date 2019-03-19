/*************************************************** 
  This is a library for the custom encoder system 
    used for position tracking

  INPUTS : current X,Y, Yaw

  Initializes with pins (intrEncL, intrEncR) 
     one interrupt for each encoder

     Authors: Michael Kaca, Dmytro Shumeyko

     Requires comparative Op-amp for setting interrupts with
        analog output of hall effect sensor

 ****************************************************/

#include "EncoderKanary.h"


// Constructor
// Wheelbase and wheel diameter are in centimeters since x and y position are
//   returned in cm
EncoderKanary::EncoderKanary(int8_t _intrEncL, int8_t _intrEncR,
  bool _directionCWL, bool _directionCWR, int _numOfMangets,
  float _wheelDiam = 8 * 2.54, float _wheelBase = 25.5 * 2.54){

  intrEncL = _intrEncL;
  intrEncR = _intrEncR;
  directionCWL = _directionCWL; 
  directionCWR = _directionCWR;
  numOfMangets = _numOfMangets; // # of magnets on each encoder
  wheelDiam = _wheelDiam;
  wheelBase = _wheelBase;

  initialized = false;
}

// Sets pins
void EncoderKanary::begin(void) {
  //define pin modes
  pinMode(intrEncR, INPUT_PULLUP);
  pinMode(intrEncL, INPUT_PULLUP);
  // define interrupt to be triggerred upon RISING edge (low to high)
  attachInterrupt(digitalPinToInterrupt(intrEncR), updateRight(), RISING);
  attachInterrupt(digitalPinToInterrupt(intrEncL), updateLeft(), RISING);

  // init variables
  rRots = 0;  // counter rotations for each encoder
  lRots = 0;

  initialized = true;
}

//sets direction variable for when motors spin the other way
// NEED TO manually set direction everytime motor function is called
//   TODO: link motor driver with encoder 
void EncoderKanary::changeDirection(bool leftDirCW, bool rightDirCW){
  directionCWL = (leftDirCW) ? 1 : 0;
  directionCWR = (rightDirCW) ? 1 : 0;
}

void EncoderKanary::updateLeft(void)
{
    //Call this when the left wheel hits a magnet
    //If direction is 1 -> CW; if 0 -> CCW
    if (directionCWL == 1)
    {lRots++;}
    else {lRots--;}
}

void EncoderKanary::updateRight(void)
{
    //Call this when the right wheel hits a magnet
    //If direction is 1 -> CW; if 0 -> CCW
    if (directionCWR == 1)
    {rRots++;}
    else {rRots--;}
}

void EncoderKanary::reset(void)
{
  rRots = 0;
  lRots = 0;
}

// returns position array of robot

// TODO: add currentX,Y,Yaw in here somewhere!!!!!!!!
int EncoderKanary::checkPosition(int currentX, int currentY, int currentYaw)
{
  //This will convert the current motor rotations into x and y coordinates in cm
  int lDist = (lRots * M_PI * wheelDiam) / numOfMangets;
  int rDist = (rRots * M_PI * wheelDiam) / numOfMangets;

  /*
  Assuming the robot travels in an arc and knowing how far each wheel travels
  can build two arcs sharing center and angle and thus determine turnRadius
  then convert into XY coordinates using starting location as origin
  */

  int turnRadius = (lDist * wheelBase) / (rDist - lDist);
  int yaw = lDist/(M_PI * turnRadius * 2) * 360;
  int yCoord = (turnRadius + (0.5 * wheelBase)) * sin(yaw) ;
  int xCoord = (turnRadius + (0.5 * wheelBase)) - (turnRadius + (0.5 * wheelBase)) * cos(yaw);


  int position[2] = {0};
  position[0] = xCoord;
  position[1] = yCoord;
  position[2] = yaw;

  // resets position to prevent position arrray from amalgamating error
  reset();
  return position;
}