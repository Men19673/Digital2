// Comunicacion I2C
// Marerial de apoyo de Nicholas Zambetti <http://www.zambetti.com>
//DIEGO A. MENDEZ
//GABRIEL FONG


#include <Wire.h>

void setup()
{
  
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  Serial.begin(9600);           // start serial for output
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  Serial.setModule(1);
  Serial.begin(9600);
  }
  
}


char  X;
char  Y;
char  PUSH;

void loop(){
  Serial1.write('X'); 
  if (Serial1.available()) {
      X = Serial1.read(); 
  }
  Serial.print(X);         // print the character
  delay(500); 
  
   Serial1.write('Y'); 
  if (Serial1.available()) {
      Y = Serial1.read(); 
  }
  Serial.print(Y);         // print the character
  delay(500); 
  
  Serial1.write('P'); 
  if (Serial1.available()) {
      PUSH = Serial1.read(); 
  }
  Serial.print(PUSH);         // print the character
  delay(500); 
  
 
  

  
//  Wire.write("Y");        // sends one byte
//  Y = Wire.read();
//  delay(100); 
//  Wire.write("P");        // sends one byte
//  PUSH = Wire.read();
//  delay(100); 
  
  if(X == '1'){
    analogWrite(BLUE_LED,255);
  }
  else if(X=='2'){
    analogWrite(RED_LED,255);
  }
  else{
    analogWrite(BLUE_LED,0);
    analogWrite(RED_LED,0);
  }
  Serial.setModule(0);
  Serial.print(X);   // send a X
  Serial.println('\n');   // send a capital enter
  Serial.print(Y);   // send a capital Y
  Serial.println('\n');   // send a capital enter
  Serial.print(PUSH);   // send a capital Push
  Serial.print("E \n");   // send a capital enter
  delay(500);
}
