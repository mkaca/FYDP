/*************************************************** 
  This is a library for the custom Motor Driver 
   Uses the IC: VNH7070AS, rated up to 15 Amps

  INPUTS: action (0-6),speed(0-100), 

  Initializes with pins (IN1,IN2,PWM,OPTIONAL:CS, OPTIONAL: SEL0)
   starting with all left wheel pins, then all right wheel pins

 ****************************************************/

#include "MSKMD_1003.h"

#include <stdlib.h>  // do I need this?


// Constructor
MSKMD_1003::MSKMD_1003(int8_t _in1L, int8_t _in2L, int8_t _pwmL,
  int8_t _in1R, int8_t _in2R, int8_t _pwmR) {

  in1L = _in1L;
  in1R = _in1R;
  in2R = _in2R;
  in2L = _in2L;
  pwmL = _pwmL;
  pwmR = _pwmR;

  initialized = false;
  currSensAvail = false;
}

// Constructor
MSKMD_1003::MSKMD_1003(int8_t _in1L, int8_t _in2L, int8_t _pwmL, 
  int8_t _csL, int8_t _sel0L,
  int8_t _in1R, int8_t _in2R, int8_t _pwmR,
  int8_t _csR, int8_t _sel0R) {

  in1L = _in1L;
  in1R = _in1R;
  in2R = _in2R;
  in2L = _in2L;
  pwmL = _pwmL;
  pwmR = _pwmR;
  sel0L = _sel0L;
  sel0R = _sel0R;
  csL = _csL;
  csR = _csR;

  initialized = false;
  currSensAvail = true;
}

void MSKMD_1003::begin(void) {
  //define pin modes
  pinMode(in1L, OUTPUT);
  pinMode(in2L, OUTPUT);
  pinMode(pwmL, OUTPUT);
  pinMode(in1R, OUTPUT);
  pinMode(in2R, OUTPUT);
  pinMode(pwmR, OUTPUT);

  // set pins iff connected
  if (currSensAvail) {
    pinMode(sel0L, OUTPUT);
    pinMode(csL, INPUT);
    pinMode(sel0R, OUTPUT);
    pinMode(csR, INPUT);
  } 

  stop();

  initialized = true;
  errorPresent = false; 
}

// Stops all motors
int MSKMD_1003::stop(void) {
  digitalWrite(in1L, 0); 
  digitalWrite(in2L, 0);
  digitalWrite(in1R, 0); 
  digitalWrite(in2R, 0);

  if (currSensAvail){
      // Add the currentSense check here
    // return 2 if currentSense is not verifying stop 
    // errorCode = 2;
    // errorPresent = true;
  }
  return 1;
}

// INPUT: speed percentage from 10 to 100
// sets speed of PWM signal for left or right motor
boolean MSKMD_1003::setPWM(int speed, int8_t pwmPin) {

  if (speed > 100 || speed < 10){
    errorCode = 3;
    errorPresent = true;
    return 0; // throw error code : set correct speed pls
  }
// speeed = x/255
  double conversion = (speed/100)*255;
  int roundedConv = (int) conversion;
  analogWrite(pwmPin, roundedConv);
  return 1;
}

// Spins motor CW ... must specify left or right
boolean MSKMD_1003::moveCW(int8_t inp1, int8_t inp2) {
  // stops it first
  digitalWrite(inp1, 0); 
  digitalWrite(inp2, 0);
  
  digitalWrite(inp1, 1); 
  digitalWrite(inp2, 0);
  if (currSensAvail){
    // Add the currentSense check here
    // return 4 if currentSense is not verifying stop 
    // errorCode = 4;
    // errorPresent = true; 
  }
  return 1;
}

// Spins motor CCW .... must specify left or right
boolean MSKMD_1003::moveCCW(int8_t inp1, int8_t inp2) {
  // stops it first
  digitalWrite(inp1, 0); 
  digitalWrite(inp2, 0);

  digitalWrite(inp1, 0); 
  digitalWrite(inp2, 1);
  if (currSensAvail){
    // Add the currentSense check here
    // return 5 if currentSense is not verifying stop 
    // errorCode = 5;
    // errorPresent = true;
  }
  return 1;
}

// Returns 1 if state is OK, otherwise, returns error code
int MSKMD_1003::stateOK(void){
  return (errorPresent) ? (errorCode) : (1);
}


//////////// HIGH LEVEL CONTROLS GO HERE ///////////////////

// INPUT: action for moving robot + its speed
//  default speed = 50% duty cycle
// 
// TODO: make turning radius be a variable
void MSKMD_1003::moveRobot(int inputAction, int speed){
  setPWM(speed, pwmL);
  setPWM(speed, pwmR);
  switch (inputAction) {
    case '1' :
      // Move robot forward, right wheel turns CW
      moveCW(in1R, in2R);
      moveCCW(in1L, in2L);
    case '2' :
      // Move robot in reverse, right wheel turns CCW
      moveCCW(in1R, in2R);
      moveCW(in1L, in2L);
    case '3' :
      // turn left, various pwm for both wheels (slower left wheel)
      setPWM(speed*0.75, pwmL);
      setPWM(speed, pwmR);
      moveCW(in1R, in2R);
      moveCCW(in1L, in2L);
    case '4' :
      // turn right, various pwm for both wheel (slower right wheel)
      setPWM(speed, pwmL);
      setPWM(speed*0.75, pwmR);
      moveCW(in1R, in2R);
      moveCCW(in1L, in2L);
    case '5' : 
      // rotate robot CW, wheels turn CCW
      moveCCW(in1L, in2L);
      moveCCW(in1R, in2R);
    case '6' :
      // rotate robot CCW, wheels turn CW
      moveCW(in1L, in2L);
      moveCW(in1R, in2R);
    default :
       // stops robot motors
       stop();

  }
}