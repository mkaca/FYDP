

#include <MSKMD_1003.h>
#include <Adafruit_MAX31856.h>


#define in1R 18  
#define in2R 19  
#define pwmR 20

#define in1L 13  
#define in2L 14 
#define pwmL 15

#define tc1CS 5 
#define TCMOSI 10
#define TCMISO 11
#define TCCLK 12
 
// DEFINE remaining pins for other circuits here!! 

String readString; // for reading serial
unsigned short timeStart, timeEnd, timeDiff;  // required to find out how fast bus is

// declare functions
void writeString(String stringData);
String encode(int tc1, int tc2, int tc3, int tc4, int EC_O2, int EC_CO, int EC_CO2, int posX, int posY, int posYaw, int Time);

// Init data variables and setting them all to 0
int tc1 = 0, tc2 = 0, tc3 = 0, tc4 = 0, EC_O2 = 0, EC_CO = 0, EC_CO2 = 0, posX = 0, posY = 0, posYaw = 0, Time = 0;

// initialize the driver
MSKMD_1003 driveSystem(in1L, in2L, pwmL, in1R, in2R, pwmR);

//initialize thermocouples with software SPI: CS, DI, DO, CLK
Adafruit_MAX31856 maxTc1 = Adafruit_MAX31856(tc1CS, TCMOSI, TCMISO, TCCLK);

void setup() {
  // ends any previously unclosed serial connections
  Serial.end();
  //Start serial
  Serial.begin(57600);
  while (!Serial) ; //wait until Serial ready
  //Serial.println("Serial Ready");

  // begin drive system module
  driveSystem.begin();

  //begin thermocouples
  maxTc1.begin();
  maxTc1.setThermocoupleType(MAX31856_TCTYPE_K);

}


// main loop
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
    delayMicroseconds(80000);  //delay 80ms to allow buffer to fill 
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
     

     tc1 = int(maxTc1.readThermocoupleTemperature());
     //Serial.print("Thermocouple #1 Temp: "); 
     //Serial.println(tc1);


     /*
     * Call updatePositionFunction  from ENCODER
     * Assign x,y,yaw to transferrable ints
     */


   // STOP DOING STUFF HEREEEEEE /////////////////////////////////////////////
   
   }

  delayMicroseconds(10000);  // waits 10 ms


  // WRITE TO PC HERE 

  // arduino encodes data to send
  // ENCODED STRING IS HERE
  String encodedMsgToSend = encode(tc1, tc2, tc3, tc4, EC_O2, EC_CO, EC_CO2, posX, posY, posYaw, Time);
  //Serial.println(encodedMsgToSend);
  writeString(encodedMsgToSend);
  //Serial.write("22220432431111");
  Serial.flush();
  break;   // ensure this break isn't messing anything up
  }

  // END CYCLE ..... AAND REPEAT
}


// write serial
void writeString(String stringData) { // Used to serially push out a String with Serial.write()

  for (int i = 0; i < stringData.length(); i++)
  {
    Serial.write(stringData[i]);   // Push each char 1 by 1 on each loop pass
  }
}// end writeString



 /* converts data (thermocouples, 2D position vector (with orientation),
      EC sensor values, timestamp) into a single string
       input: multiple string / ints / whatever the values are in/ and converts to a single string message 
          with 0000 indicating beggining, 1111 indicating termination of each data packet,
  
          To call: 
          String encoded = encode(tc1, tc2, tc3, tc4, EC_O2, EC_CO, EC_CO2, posX, posY, posYaw, Time);
  */ 
  String encode(int tc1, int tc2, int tc3, int tc4, int EC_O2, int EC_CO, int EC_CO2, int posX, int posY, int posYaw, int Time){

    String start, end;
    start = "2222";
    end = "1111";

    // Transforms int -->string
    String str_tc1 = start + "11" + String(tc1) + end;
    String str_tc2 = start + "12" + String(tc2) + end;
    String str_tc3 = start + "13" +  String(tc3) + end;
    String str_tc4 = start + "14" +  String(tc4) + end;
    String str_EC_O2 =start + "21" +  String(EC_O2) + end;
    String str_EC_CO = start + "22" +  String(EC_CO) + end;
    String str_EC_CO2 = start+ "23" +  String(EC_CO2) + end;
    String str_PosX = start + "31" + String(posX) + end;
    String str_PosY = start + "32" + String(posY) + end;
    String str_PosYaw = start + "33" + String(posYaw) + end;
    String str_Time = start + "91" +  String(Time) + end;
  
     //Combines strings
    String out;
    out = str_tc1 + str_tc2 + str_tc3 + str_tc4 + str_EC_O2 + str_EC_CO + str_EC_CO2 + str_PosX + str_PosY + str_PosYaw + str_Time ;
    return out;
    }
