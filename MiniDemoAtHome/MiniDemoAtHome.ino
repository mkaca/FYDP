#define in1 52
#define in2 53  
#define pwm 50

int onTime = 100; // in micros
int offTime = 1000 - onTime;

void stopSystem(){
  digitalWrite(in1, LOW);
  digitalWrite(in2,LOW);
  //digitalWrite(pwmL,LOW);
  Serial.println("STOPPED");
  delay(25); // delays 25 ms to attenuate transient errors
}


void runFwd(int duration){
  float initTime = millis();
  float endTime = millis();
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  
  Serial.print(initTime);  Serial.print(" MOVING CWL "); Serial.println(endTime);
  while (endTime - initTime < duration){ // %X duty cycle for testing
    endTime = millis();
    digitalWrite(pwm, 1);
    delayMicroseconds(onTime);
    digitalWrite(pwm, 0);
    delayMicroseconds(offTime);
  }
  stopSystem();
}

void runBwd(int duration){
  float initTime = millis();
  float endTime = millis();
  digitalWrite(in2,LOW);
  digitalWrite(in1,HIGH);

  Serial.print(initTime); Serial.print(" MOVING CCWL "); Serial.println(endTime);
  //analogWrite(pwmL, 55);
  //delay(duration);
  while (endTime - initTime < duration){ // %10 duty cycle for testing
    endTime = millis();
    digitalWrite(pwm, 1);
    delayMicroseconds(onTime);
    digitalWrite(pwm, 0);
    delayMicroseconds(offTime);
  }
  stopSystem();
}

void setup() {
  Serial.begin(9600);
  Serial.println("Enter 1 to move forward and 2 to move backward");
  Serial.println("Enter 8 to increase speed and 6 to decrease speed");
  stopSystem();
}

char rx_byte = 0;

void loop() {
  if (Serial.available() > 0) {    // is a character available?
    rx_byte = Serial.read();       // get the character
  
    // check if a number was received
    if ((rx_byte >= '0') && (rx_byte <= '9')) {
      Serial.print("Number received: ");
      Serial.println(rx_byte);
      if (rx_byte == '1'){
        runFwd(3000);
        Serial.println("Going Forward");
      }
      else if(rx_byte == '2'){
        runBwd(3000);
        Serial.println("Going backwards");
      }
      else if(rx_byte == '6'){
        onTime = onTime - 50;
        offTime = offTime + 50;
        Serial.print("Decreased speed to: "); Serial.print(onTime); Serial.println(" microseconds On cycle");
      }
      else if(rx_byte == '8'){
        onTime = onTime + 50;
        offTime = offTime - 50;
        Serial.print("Decreased speed to: "); Serial.print(onTime); Serial.println(" microseconds On cycle");
      }
    }
    else {
      Serial.println("Not a number.");
    }
  } // end: if (Serial.available() > 0)
}

