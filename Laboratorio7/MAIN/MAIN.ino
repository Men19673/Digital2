/*
 Diego A. Méndez
 Carné 19673
 Laboratorio 7
 19 Sep. 2021

 */
#include <SPI.h>
#include <SD.h>
#define PB1 PUSH1

File myFile;



int Flag = 0;
volatile char INSER = '0';
int IN =0;

void setup() {
   // initialize serial:
  Serial.begin(9600);
  SPI.setModule(0);   //COnectar bien los pines
  pinMode(PB1, INPUT_PULLUP);
  pinMode(12, OUTPUT);

  if(!SD.begin(12)){  //PIN PA_3 para ChannelSelect
    Serial.println("Initialization failed");
    return;
  }
  Serial.println("Initialization done.");
 
}

void loop() {
  if(digitalRead(PB1) == 0){
     Flag = 1;    //ANtirrebote
  }
  if( Flag && digitalRead(PB1)){
  Serial.print("\n Elija la imagen que desea");
  Serial.print("\n (a) McDonalds");
  Serial.print("\n (b) Gioconda");
  Serial.print("\n (c) VW \n");
  Flag = 0;
    }
  while(Serial.available()){
    INSER = (char)Serial.read();
    IN = int(INSER);
    switch(IN){
      case 97 :
        
        
         myFile = SD.open("MC.txt");
        if (myFile) {
          Serial.println("MC.txt:");
      
          // read from the file until there's nothing else in it:
          while (myFile.available()) {
            Serial.write(myFile.read());
          }
          // close the file:
          myFile.close();
        } else {
          // if the file didn't open, print an error:
          Serial.println("error opening MC.txt");
  }
          
        break;
      case 98 :
        
        myFile = SD.open("GIOCONDA.txt");
        if (myFile) {
          Serial.println("GIOCONDA.txt:");
      
          // read from the file until there's nothing else in it:
          while (myFile.available()) {
            Serial.write(myFile.read());
          }
          // close the file:
          myFile.close();
        } else {
          // if the file didn't open, print an error:
          Serial.println("error opening GIOCONDA.txt");
        }
        break;
      case 99 :
        

         myFile = SD.open("VW.txt");
        if (myFile) {
          Serial.println("VW.txt:");
      
          // read from the file until there's nothing else in it:
          while (myFile.available()) {
            Serial.write(myFile.read());
          }
          // close the file:
          myFile.close();
        } else {
          // if the file didn't open, print an error:
          Serial.println("error opening VW.txt");
        }
        
        break;
      default:
        break;
      
        
      }
}
  
  }

 
