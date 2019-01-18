#include <Wire.h>

int var = 0;

void setup()
{
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void loop()
{
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  while (Wire.available())
  { // slave may send less than requested
    var = Wire.read(); // receive a byte as character
    var++;
    Wire.write(var);
  }
  //Wire.write("hello "); // respond with message of 6 bytes
  // as expected by master
}
