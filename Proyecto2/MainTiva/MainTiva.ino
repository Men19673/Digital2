// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup()
{
  Wire.setModule(1); //PA6 SCL y PA7 SDA
  Wire.begin(); // join i2c bus (address optional for master)
}


int  X;
int  Y;
int  PUSH;
void loop()
{
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write("X");        // sends one byte
  X = Wire.read(); 
  delay(100); 
  Wire.write("Y");        // sends one byte
  Y = Wire.read();
  delay(100); 
  Wire.write("P");        // sends one byte
  PUSH = Wire.read();
  delay(100); 
  Wire.endTransmission();    // stop transmitting

  Serial.print(X);   // send a X
  Serial.print('\n');   // send a capital enter
  Serial.print(Y);   // send a capital Y
  Serial.print('\n');   // send a capital enter
  Serial.print(PUSH);   // send a capital Push
  delay(500);
}
