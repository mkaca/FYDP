  // TRIED:    
  /// OUTB1 GRND 
  /// OUTB1 OUTB2 nothing
  // OUTB1 OUTA1 nothing
#define in1 7  
#define in2 8  
#define sel0 10
#define pwm 11

void setup() {
  // put your setup code here, to run once:
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(sel0, OUTPUT);
  pinMode(pwm, OUTPUT);

  digitalWrite(sel0,LOW);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //digitalWrite(pwm, HIGH);
  
  delay(500);
  runCW(3000);
  delay(4000);
  runCCW(3000);  
  delay(3500);

}

void stopMotor(){
  digitalWrite(in2, LOW);
  digitalWrite(in1,LOW);
  Serial.println("STOPPED");
  delay(25); // delays 25 ms to attenuate transient errors
}

void runCW(int duration){
  float initTime = millis();
  float endTime = millis();
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  
  Serial.print(initTime);
    Serial.print(" MOVING CW ");
    Serial.println(endTime);
  while (endTime - initTime < duration){ // %10 duty cycle for testing
    endTime = millis();
    digitalWrite(pwm, 1);
    delayMicroseconds(100);
    digitalWrite(pwm, 0);
    delayMicroseconds(900);
  }
  stopMotor();
}

void runCCW(int duration){
  float initTime = millis();
  float endTime = millis();
  digitalWrite(in2,LOW);
  digitalWrite(in1,HIGH);
  
  Serial.print(initTime);
    Serial.print(" MOVING CCW ");
    Serial.println(endTime);
  while (endTime - initTime < duration){ // %10 duty cycle for testing
    endTime = millis();
    digitalWrite(pwm, 1);
    delayMicroseconds(100);
    digitalWrite(pwm, 0);
    delayMicroseconds(900);
  }
  stopMotor();
}

