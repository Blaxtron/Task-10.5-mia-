#include <Wire.h>

float yaw;
long gyroY;
long gyroX;
long gyroZ;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(0b1101000);
  Wire.write(0x6B);
  Wire.write(0b00000000);
  Wire.endTransmission();

  Wire.beginTransmission(0b1101000);
  Wire.write(0X1B);
  Wire.write(0b00000000);
  Wire.endTransmission();
}

void readGyroscope(){
  Wire.beginTransmission(0b1101000);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6);
  while(Wire.available() < 6);{
    gyroX = Wire.read()<<8 | Wire.read();
    gyroY = Wire.read()<<8 | Wire.read();
    gyroZ = Wire.read()<<8 | Wire.read();
    calcGyroscope();
  }



}
void calcGyroscope(){
  yaw = gyroZ / 131.0;

}
void printGyroscope(){
  Serial.print("Yaw: ");
  Serial.println(yaw);
  
}
void loop() {
  // put your main code here, to run repeatedly:
  readGyroscope();
  printGyroscope();
  delay(100);
}
