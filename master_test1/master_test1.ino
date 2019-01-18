#include <Wire.h>

int var = 0;
void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);
  Serial.println("Start!");
  Serial.print("Start value is = ");
  Serial.println(var);
}

void loop()
{
  Wire.beginTransmission(8);
  Wire.requestFrom(8, 6);    // request 6 bytes from slave device #8
  Wire.write(var);
  while (Wire.available())
  { // slave may send less than requested
    var = Wire.read(); // receive a byte as character
    Serial.print("I've got: ");
 
    Serial.println(var);         // print the character
  }
  Wire.endTransmission(8);
  
  var++;
  delay(500); 
}
