#define in1L 52 
#define in2L 53  
#define pwmL 2

#define in1R 31 
#define in2R 30  
#define pwmR 3

void stopMotorL(){
  digitalWrite(in2L, LOW);
  digitalWrite(in1L,LOW);
  Serial.println("STOPPED");
  delay(25); // delays 25 ms to attenuate transient errors
}


void stopMotorR(){
  digitalWrite(in2R, LOW);
  digitalWrite(in1R,LOW);
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
    delayMicroseconds(300);
    digitalWrite(pwmL, 0);
    delayMicroseconds(700);
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
  while (endTime - initTime < duration){ // %10 duty cycle for testing
    endTime = millis();
    digitalWrite(pwmL, 1);
    delayMicroseconds(300);
    digitalWrite(pwmL, 0);
    delayMicroseconds(700);
  }
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
    delayMicroseconds(300);
    digitalWrite(pwmR, 0);
    delayMicroseconds(700);
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
    delayMicroseconds(300);
    digitalWrite(pwmR, 0);
    delayMicroseconds(700);
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
  delay(3000);
  runCWL(10000);
  runCWR(10000);
  delay(2500);
  runCCWL(5000);
  runCCWR(5000);  
  delay(2500);

}
