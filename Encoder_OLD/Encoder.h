/*
  Encoder.h - Library to be used with encoder for Kanary Firebot
  Created by Deempeen on 12/03/19

*/

//The following prevents issues if library included more than once:
#ifndef Encoder_h
#define Encoder_h

//Gives access to standard types and constants
#include "Arduino.h"


class Encoder
{
public:
  Encoder(int pin); //Constructor for the class

private:
  int _ePin1;
  int _ePin2;
  int _ePin3;
  int _ePin4;


};

#endif
