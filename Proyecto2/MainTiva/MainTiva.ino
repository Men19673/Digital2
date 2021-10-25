// Comunicacion Serial
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
  Serial5.begin(9600);
  }
  





void loop(){
  Serial5.write('V'); 
  delay(5);
  if (Serial5.available()) {
      X = Serial5.read(); 
  }
  Serial.print(X);         // print the character
  delay(5); 
  
  
  
  Serial5.write('P'); 
   delay(5);
  if (Serial5.available()) {
      PUSH = Serial5.read(); 
  }
  Serial.print(PUSH);         // print the character
  delay(5); 
  
 
  
  
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

  delay(500);
}
