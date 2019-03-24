#define in1L 52 
#define in2L 53  
#define pwmL 50

#define in1R 48
#define in2R 5  
#define pwmR 6

int offTime = 850;
int onTime = 1000 - offTime;


void stopMotorL(){
  digitalWrite(in2L, LOW);
  digitalWrite(in1L,LOW);
  //digitalWrite(pwmL,LOW);
  Serial.println("STOPPED");
  delay(25); // delays 25 ms to attenuate transient errors
}


void stopMotorR(){
  digitalWrite(in2R, LOW);
  digitalWrite(in1R,LOW);
  //digitalWrite(pwmR,LOW);
  Serial.println("STOPPED");
  delay(25); // delays 25 ms to attenuate transient errors
}

void runCWL(int duration){
  float initTime = millis();
  float endTime = millis();
  digitalWrite(in1L,LOW);
  digitalWrite(in2L,HIGH);
  
  Serial.print(initTime);
    Serial.print(" MOVING CWL ");
    Serial.println(endTime);
  while (endTime - initTime < duration){ // %10 duty cycle for testing
    endTime = millis();
    digitalWrite(pwmL, 1);
    delayMicroseconds(onTime);
    digitalWrite(pwmL, 0);
    delayMicroseconds(offTime);
  }
  stopMotorL();
}

void runCCWL(int duration){
  float initTime = millis();
  float endTime = millis();
  digitalWrite(in2L,LOW);
  digitalWrite(in1L,HIGH);

  Serial.print(initTime);
  Serial.print(" MOVING CCWL ");
  Serial.println(endTime);
  //analogWrite(pwmL, 55);
  digitalWrite(pwmL,HIGH);
  delay(duration);
  /*while (endTime - initTime < duration){ // %10 duty cycle for testing
    endTime = millis();
    digitalWrite(pwmL, 1);
    delayMicroseconds(onTime);
    digitalWrite(pwmL, 0);
    delayMicroseconds(offTime);
  }*/
  
  stopMotorL();
}

void runCWR(int duration){
  float initTime = millis();
  float endTime = millis();
  digitalWrite(in1R,LOW);
  digitalWrite(in2R,HIGH);
  
  Serial.print(initTime);
    Serial.print(" MOVING CWR ");
    Serial.println(endTime);
  while (endTime - initTime < duration){ // %10 duty cycle for testing
    endTime = millis();
    digitalWrite(pwmR, 1);
    delayMicroseconds(onTime);
    digitalWrite(pwmR, 0);
    delayMicroseconds(offTime);
  }
  stopMotorR();
}

void runCCWR(int duration){
  float initTime = millis();
  float endTime = millis();
  digitalWrite(in2R,LOW);
  digitalWrite(in1R,HIGH);
  
  Serial.print(initTime);
    Serial.print(" MOVING CCWR ");
    Serial.println(endTime);
  while (endTime - initTime < duration){ // %10 duty cycle for testing
    endTime = millis();
    digitalWrite(pwmR, 1);
    delayMicroseconds(onTime);
    digitalWrite(pwmR, 0);
    delayMicroseconds(offTime);
  }
  stopMotorR();
}

void setup() {
  // put your setup code here, to run once:
  pinMode(in1L, OUTPUT);
  pinMode(in2L, OUTPUT);
  pinMode(pwmL, OUTPUT);

  pinMode(in1R, OUTPUT);
  pinMode(in2R, OUTPUT);
  pinMode(pwmR, OUTPUT);

  Serial.begin(9600);
  delay(2000);
  stopMotorR();
  stopMotorL();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //digitalWrite(pwm, HIGH);
  //stopMotor();
  delay(200);
  //runCWR(5000);
  //runCWL(3000);
  //delay(2500);
  //runCCWR(5000);  
  runCCWL(5000);
  //delay(2500);

}
