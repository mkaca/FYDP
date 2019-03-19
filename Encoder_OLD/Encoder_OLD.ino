// Meant to test encoder with magnets and with the encoder Custom library

int encoderValue= 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  encoderValue = analogRead(A1); //encoder vOUT

  Serial.print("value: ");
Serial.println(encoderValue);

delay(100);

/*
 * LOGIC: 
 * If, 500, count X revolutions, have an input of 8 for function
 * 
 * If change from 500 is greater than 100, count as toggle
 * 
 * 
 * 
 */


}
