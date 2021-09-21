/*
 Diego A. Méndez
 Carné 19673
 Laboratorio 7
 19 Sep. 2021

 */
//Definmos nombres faciles
 #define PB1 PUSH1
 #define PB2 PUSH2

uint8_t cont1 = 0;
uint8_t cont2 = 0;

int inc1 = 0;
int inc2 = 0;
int bandera = 0;
int alto =0;

void setup() {
  // put your setup code here, to run once:
  pinMode(PB1, INPUT_PULLUP);
  pinMode(PB2, INPUT_PULLUP);
  pinMode(PD_0, OUTPUT);
  pinMode(PD_1, OUTPUT);
  pinMode(PD_2, OUTPUT);
  pinMode(PD_3, OUTPUT);
  pinMode(PE_1, OUTPUT);
  pinMode(PE_2, OUTPUT);
  pinMode(PE_3, OUTPUT);
  pinMode(PF_1, OUTPUT);
  pinMode(PB_5, OUTPUT);
  pinMode(PB_0, OUTPUT);
  pinMode(PB_1, OUTPUT);
  pinMode(PE_4, OUTPUT);
  pinMode(PE_5, OUTPUT);
  pinMode(PB_4, OUTPUT);
  pinMode(PA_5, OUTPUT);
  pinMode(PA_6, OUTPUT);
  pinMode(PA_7, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  while(bandera == 0){
   if ((digitalRead(PB1) == 0)|(digitalRead(PB2) == 0)){ 
        cont1=0;
        cont2=0;
        alto=0;
        analogWrite(RED_LED, 255);
        delay(1000);
        analogWrite(GREEN_LED, 125);
        analogWrite(RED_LED, 125);
        delay(1000);
        analogWrite(GREEN_LED, 255);
        analogWrite(RED_LED, 0);
        delay(1000);
        analogWrite(GREEN_LED, 0);
        bandera = 1;
    
    }
    
    }
  
  while(bandera==1){
  if (alto==0) botones(); //hacer que ya no funcionen los pushes
  ledJ1();
  ledJ2();
  }
  
  
}

void botones(void) {
  if (digitalRead(PB1) == 0){ 
    inc1 = 1;    //Levantar bandera que se presiono el boton 1
    
    }
  if (digitalRead(PB1) && inc1){  //Ver que la bandera este levantada y el boton en su estado normal
    cont1++;        
    inc1 = 0;
    }
  if (digitalRead(PB2) == 0){
    inc2 = 1;  //Levantar bandera que se presiono el boton 2
    
    }
  if (digitalRead(PB2) && inc2){ //Ver que la bandera este levantada y el boton en su estado normal
    cont2++;
    inc2 = 0;
    }
  }

  void ledJ1(){
    switch(cont1){    //Ir apagando y encendiendo luces
      case 1:
      digitalWrite(PB_5, HIGH);
      break;
      
      case 2:
      digitalWrite(PB_5, LOW);
      digitalWrite(PB_0, HIGH);
      break;

      case 3: 
      digitalWrite(PB_0, LOW);
      digitalWrite(PB_1, HIGH);
      break;

      case 4:
      digitalWrite(PB_1, LOW);
      digitalWrite(PE_4, HIGH);
      break;

      case 5:
      digitalWrite(PE_4, LOW);
      digitalWrite(PE_5, HIGH);
      break;

      case 6: 
      digitalWrite(PE_5, LOW);
      digitalWrite(PB_4, HIGH);
      break;

      case 7:
      digitalWrite(PB_4, LOW) ;
      digitalWrite(PA_5, HIGH);
      break;

      case 8:
      digitalWrite(PA_5, LOW);
      digitalWrite(PA_6, HIGH);
      analogWrite(BLUE_LED, 255);
      alto = 1;   //Hacer que ya no funcionen los pushes
      bandera = 0;
      delay(1000);
      digitalWrite(PA_6, LOW);
      analogWrite(BLUE_LED, 0);
      delay(1000);
      digitalWrite(PA_6, HIGH);
      analogWrite(BLUE_LED, 255);
      delay(1000);
      digitalWrite(PA_6, LOW);
      analogWrite(BLUE_LED, 0);
      break;

      default:
      digitalWrite(PA_5, LOW);
      digitalWrite(PB_5, LOW);
      digitalWrite(PB_0, LOW);
      digitalWrite(PB_1, LOW);
      digitalWrite(PE_4, LOW);
      digitalWrite(PE_5, LOW);
      digitalWrite(PB_4, LOW);
      digitalWrite(PA_6, LOW);
      break;
      
      }
    }

  void ledJ2(){
    switch(cont2){    //Ir apagando y encendiendo luces
      case 1:
      digitalWrite(PD_0, HIGH);
      break;
      
      case 2:
      digitalWrite(PD_0, LOW);
      digitalWrite(PD_1, HIGH);
      break;

      case 3: 
      digitalWrite(PD_1, LOW);
      digitalWrite(PD_2, HIGH);
      break;

      case 4:
      digitalWrite(PD_2, LOW);
      digitalWrite(PD_3, HIGH);
      break;

      case 5:
      digitalWrite(PD_3, LOW);
      digitalWrite(PE_1, HIGH);
      break;

      case 6: 
      digitalWrite(PE_1, LOW);
      digitalWrite(PE_2, HIGH);
      break;

      case 7:
      digitalWrite(PE_2, LOW) ;
      digitalWrite(PE_3, HIGH);
      break;

      case 8:
      digitalWrite(PE_3, LOW);
      digitalWrite(PA_7, HIGH);
      analogWrite(BLUE_LED, 255); //Hacemos una secuencia de apagado donde muestra el ganador y el color en la led
      analogWrite(RED_LED, 255);
      alto = 1;
      bandera = 0;
      delay(1000);
      digitalWrite(PA_7, LOW);
      analogWrite(BLUE_LED, 0); //se realiza un titileo
      analogWrite(RED_LED, 0);
      delay(1000);
      digitalWrite(PA_7, HIGH);
      analogWrite(BLUE_LED, 255);
      analogWrite(RED_LED, 255);
      delay(1000);
      digitalWrite(PA_7, LOW);
      analogWrite(BLUE_LED, 0);
      analogWrite(RED_LED, 0);
      break;

      default:
      digitalWrite(PD_0, LOW);
      digitalWrite(PD_1, LOW);
      digitalWrite(PD_2, LOW);
      digitalWrite(PD_3, LOW);
      digitalWrite(PE_1, LOW);
      digitalWrite(PE_2, LOW);  //Si no existe el caso se apaga todo
      digitalWrite(PE_3, LOW);
      digitalWrite(PA_7, LOW);
      break;
      
      }
    }
