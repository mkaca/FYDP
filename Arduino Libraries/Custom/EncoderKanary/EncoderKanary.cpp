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

#include <stdlib.h>  // do I need this?


// Constructor
EncoderKanary::EncoderKanary(int8_t _intrEncL, int8_t _intrEncR){

  intrEncL = _intrEncL;
  intrEncR = _intrEncR;

  initialized = false;
}

/*
EncoderKanary::EncoderKanary()
{
  volatile unsigned long rRots = 0;
  volatile unsigned long lRots = 0;
  int wheelBase = 25.5 * 2.54;

}
*/

void EncoderKanary::begin(void) {
  //define pin modes
  pinMode(intrEncR, INPUT);
  pinMode(intrEncL, INPUT);

  // init variables
  rRots = 0;  // counter rotations for each encoder
  lRots = 0;
  wheelBase = 25.5 * 2.54; // value in cm

  initialized = true;
}

void EncoderKanary::updateLeft(uint8_t direction)
{
    //Call this when the left wheel hits a magnet
    //If direction is 1 -> CW; if 0 -> CCW
    if (direction == 1)
    {lRots++;}
    else {lRots--;}
}

void EncoderKanary::updateRight(uint8_t direction)
{
    //Call this when the right wheel hits a magnet
    //If direction is 1 -> CW; if 0 -> CCW
    if (direction == 1)
    {rRots++;}
    else {rRots--;}
}

void EncoderKanary::reset()
{
  rRots = 0;
  lRots = 0;
}

int EncoderKanary::posConverter(add params)
{
  //This will convert the current motor rotations into x and y coordinates in cm
  int lDist = (lRots * M_Pi * 8 * 2.54) / 4;
  int rDist = (rRots * M_Pi * 8 * 2.54) / 4;

  /*
  Assuming the robot travels in an arc and knowing how far each wheel travels
  can build two arcs sharing center and angle and thus determine turnRadius
  then convert into XY coordinates using starting location as origin
  */

  int turnRadius = (lDist * wheelBase) / (rDist - lDist);
  int yew = lDist/(M_Pi * turnRadius * 2) * 360;
  int yCoord = (turnRadius + (0.5 * wheelBase)) * M_sin(yew);
  int xCoord = (turnRadius + (0.5 * wheelBase)) - (turnRadius + (0.5 * wheelBase)) * M_cos(yew);


  int position[2] = {0};
  position[0] = xCoord;
  position[1] = yCoord;
  position[2] = yew;
  return position;
}