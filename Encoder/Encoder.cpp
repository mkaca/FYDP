/*
  Encoder.cpp - Source code for encoder Libary
  Created by Deempeen on 12/03/19
  When the function is called a counter for rotations is initialized
*/

#include "Encoder.h"


Encoder::Encoder()
{
  volatile unsigned long rRots = 0;
  volatile unsigned long lRots = 0;
  int wheelBase = 25.5 * 2.54;

}

void Encoder::updateLeft(uint8_t direction)
{
    //Call this when the left wheel hits a magnet
    //If direction is 1 -> CW; if 0 -> CCW
    if (direction == 1)
    {lRots++;}
    else {lRots--;}
}

void Encoder::updateRight(uint8_t direction)
{
    //Call this when the right wheel hits a magnet
    //If direction is 1 -> CW; if 0 -> CCW
    if (direction == 1)
    {rRots++;}
    else {rRots--;}
}

void Encoder::reset()
{
  rRots = 0;
  lRots = 0;
}

int Encoder::posConverter(add params)
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
