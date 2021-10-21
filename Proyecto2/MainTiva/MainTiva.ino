// Comunicacion I2C
// Marerial de apoyo de Nicholas Zambetti <http://www.zambetti.com>
//DIEGO A. MENDEZ
//GABRIEL FONG


char  X;
char  Y;
char  PUSH;

void setup()
{
  
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  Serial.begin(9600);           // start serial for output
  
  
  Serial3.begin(9600);
  }
  





void loop(){
  Serial3.write('X'); 
  delay(5);
  if (Serial3.available()) {
      X = Serial3.read(); 
  }
  Serial.print(X);         // print the character
  delay(10); 
  
   Serial3.write('Y'); 
    delay(5);
  if (Serial3.available()) {
      Y = Serial3.read(); 
  }
  Serial.print(Y);         // print the character
  delay(10); 
  
  Serial3.write('P'); 
   delay(5);
  if (Serial3.available()) {
      PUSH = Serial3.read(); 
  }
  Serial.print(PUSH);         // print the character
  delay(10); 
  
 
  

  
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
//  Serial.setModule(0);
//  Serial.print(X);   // send a X
//  Serial.println('\n');   // send a capital enter
//  Serial.print(Y);   // send a capital Y
//  Serial.println('\n');   // send a capital enter
//  Serial.print(PUSH);   // send a capital Push
//  Serial.print("E \n");   // send a capital enter
  delay(500);
}
