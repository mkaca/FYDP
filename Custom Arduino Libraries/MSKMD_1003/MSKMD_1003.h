/*************************************************** 
  This is a library for the custom Motor Driver 
   Uses the IC: VNH7070AS, rated up to 15 Amps

  INPUTS: action (0-6),speed(0-100), 

  Initializes with pins (IN1,IN2,PWM,OPTIONAL:CS, OPTIONAL: SEL0)

 ****************************************************/

#ifndef MSKMD_1003_H
#define MSKMD_1003_H

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

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

#endif
