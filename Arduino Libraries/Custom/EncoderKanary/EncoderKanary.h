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

#ifndef EncoderKanary_H
#define EncoderKanary_H

#include <stdlib.h>  // do I need this?

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class EncoderKanary
{
public:
  EncoderKanary(int8_t _intrEncL, int8_t _intrEncR,
  bool _directionCWL, bool _directionCWR, int _numOfMangets,
  float _wheelDiam = 8 * 2.54, float _wheelBase = 25.5 * 2.54); //Constructor for the class

  void begin(void);
  void changeDirection(bool leftDirCW, bool rightDirCW);
  void reset(void);
  int checkPosition(int currentX, int currentY, int currentYaw);

private:
  int8_t intrEncL, intrEncR;
  bool directionCWR, directionCWL;
  volatile unsigned long rRots, lRots;
  int numOfMangets; 
  float wheelBase, wheelDiam;
  bool initialized;
  void updateLeft(void);
  void updateRight(void);
};

#endif
