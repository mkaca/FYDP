
#include <MSKMD_1003.h>

#define in1R 7  
#define in2R 8  
#define pwmR 11

#define in1L 12  
#define in2L 13 
#define pwmL 15

String readString; // for reading serial
unsigned short timeStart, timeEnd, timeDiff;  // required to find out how fast bus is

// initialize the driver
MSKMD_1003 driveSystem(in1L, in2L, pwmL, in1R, in2R, pwmR);
//initialize controller

void setup() {
  // ends any previously unclosed serial connections
  Serial.end();
  //Start serial
  Serial.begin(57600);
  while (!Serial) ; //wait until Serial ready
  Serial.println("Serial Ready");

  // begin drive system module
  driveSystem.begin();

}

/* converts data (thermocouples, 2D position vector (with orientation),
    EC sensor values, timestamp) into a single string
     input: multiple string / ints / whatever the values are in/ and converts to a single string message 
        with 0000 indicating beggining, 1111 indicating termination of each data packet,
*/ 
String encode(String A, StringB .... etc){
  
}


/*
 * Decode incoming string packet to tell us: action of user + acknolwedgement that things are okay
 *  decode message (starts with 0000 and ends with 1111) to extract single action string from message --> SUPER SIMPLE
 */
String decode(String inComingMsg){
  
}

void loop() {

  /*  OVERVIEW of LOGIC
    - wait to receive message from PC to arduino via serial
    - decode message   --> make decode function
    - perform appropriate actions based on message
    - Get sensor data/error codes/ position from system actions
    - Encode sensor data / outputs
    - send via Serial to PC
  */

  // Real serial from PC
  while (!Serial.available()) {} // wait for data to arrive
  // serial read section
  while (Serial.available())
  {
    timeStart = micros();
    delayMicroseconds(10000);  //delay 10ms to allow buffer to fill 
    if (Serial.available() >0)
    {
      char c = Serial.read();  //gets one byte from serial buffer   NOTE: THIS MAY BE TOO SHORT
      readString = c; // converts to string
    }
   if (readString.length() >0)
   {
    
    //==================================================================================  
   unsigned long startTime = micros();
   
   ///   DO STUFFFFFF HEREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE ////////////////////////////////


   
     driveSystem.moveRobot(1, 45); // go straight at 45% duty cycle
     delayMicroseconds(10000);
     
     // Checks for errors
     int errorCode = driveSystem.stateOK();
     if(errorCode != 1)
     {
      // include error code here when sending.... also stop motors
      driveSystem.stop();
     }


   // STOP DOING STUFF HEREEEEEE /////////////////////////////////////////////
   
   timeEnd = micros();
   timeDiff = timeEnd - timeStart;
   //Serial.print("time diff: ");  Serial.println(timeDiff);  // prints out duration of loop
  }

  delayMicroseconds(1000);  // waits 1 ms


  // WRITE TO PC HERE 

  // arduino encodes data to send
  // ENCODED STRING IS HERE
    //Serial.write(ecodedString);
  Serial.write("0349102943");
  Serial.flush();
  }

  // END CYCLE ..... REPEAT
}


