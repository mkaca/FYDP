/*************************************************** 
  This is a library for the custom encoder system 
    used for position tracking

  INPUTS : current X,Y, Yaw

  Initializes with pins (intrEncL, intrEncR) 
     one interrupt for each encoder

     Authors: Michael Kaca, Dmytro Shumeyko

     Requires comparative Op-amp for setting interrupts with
        analog output of hall effect sensor

      MUst initialize static positions in arduino class initially

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
  static int currentPosX, currentPosY, currentPosYaw; // static variables for position tracking
  static int rRots, lRots;
  
  EncoderKanary(int8_t _intrEncL, int8_t _intrEncR,
  bool _directionCWL, bool _directionCWR, int _numOfMangets,
  float _wheelDiam = 8 * 2.54, float _wheelBase = 25.5 * 2.54); //Constructor for the class

  void begin(void);
  void changeDirection(bool, bool);
  void reset(void);
  void updateCurrentPosition(void);

  void updateLeft(void);
  void updateRight(void);

private:
  int8_t intrEncL, intrEncR;
  bool directionCWR, directionCWL;
  int numOfMangets; 
  float wheelBase, wheelDiam;
  bool initialized;
  
};

#endif
