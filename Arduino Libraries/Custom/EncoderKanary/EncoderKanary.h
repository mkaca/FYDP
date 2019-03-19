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

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class EncoderKanary
{
public:
  EncoderKanary(int8_t _intrEncL, int8_t _intrEncR); //Constructor for the class

private:
  int8_t intrEncL, intrEncR;
  volatile unsigned long rRots, lRots;
  int wheelBase; 

};

/*
class MSKMD_1003 {
 public:  // pin init
  MSKMD_1003(int8_t _in1L, int8_t _in2L, int8_t _pwmL, 
  int8_t _in1R, int8_t _in2R, int8_t _pwmR);

  MSKMD_1003(int8_t _in1L, int8_t _in2L, int8_t _pwmL, 
  int8_t _csL, int8_t _sel0L,
  int8_t _in1R, int8_t _in2R, int8_t _pwmR,
  int8_t _csR, int8_t _sel0R);

  void begin(void);
  int stop(void);
  int stateOK(void);
  void moveRobot(int inputAction, int speed = 50);
  boolean errorPresent;
  int errorCode;

 private:
  boolean initialized;
  boolean currSensAvail; // currentSense available 
  boolean setPWM(int speed, int8_t pwmPin);
  boolean moveCW(int8_t inp1, int8_t inp2);
  boolean moveCCW(int8_t inp1, int8_t inp2);

  int8_t in1L, in2L, pwmL, csL, sel0L;
  int8_t in1R, in2R, pwmR, csR, sel0R;
};
*/

#endif
