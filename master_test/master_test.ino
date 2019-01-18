#include <Wire.h>

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);
  Serial.println("Start!");
}

void loop()
{
  Wire.beginTransmission(8);
  Wire.requestFrom(8, 6);    // request 6 bytes from slave device #8

  while (Wire.available())
  { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
  }
  Wire.endTransmission(8);

  delay(500);
}
