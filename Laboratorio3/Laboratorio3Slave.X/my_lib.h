/* 
 * File:   my_lib.h
 * Author: Diego
 *
 * Created on July 14, 2021, 12:15 AM
 */

#ifndef MY_LIB_H
#define	MY_LIB_H

#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ      4000000 //Definir la frecuencia de operacion
void initOsc(uint8_t frec){
    OSCCONbits.SCS = 1;   //utilizar oscilador interno para reloj del sistema
        switch(frec){
            case 8:
                OSCCONbits.IRCF0 = 1;
                OSCCONbits.IRCF1 = 1;   //8MHz
                OSCCONbits.IRCF2 = 1;
                break;
                
            case 4:
                OSCCONbits.IRCF0 = 0;
                OSCCONbits.IRCF1 = 1;       //4MHZ
                OSCCONbits.IRCF2 = 1;
                break;
            case 2:
                OSCCONbits.IRCF0 = 1;
                OSCCONbits.IRCF1 = 0;       //2MHZ
                OSCCONbits.IRCF2 = 1;
                break;
             case 1:
                OSCCONbits.IRCF0 = 0;
                OSCCONbits.IRCF1 = 0;       //1MHZ
                OSCCONbits.IRCF2 = 1;
                break;
             case 50:
                OSCCONbits.IRCF0 = 0;
                OSCCONbits.IRCF1 = 1;       //500kHZ
                OSCCONbits.IRCF2 = 1;
                break;
             case 25:
                OSCCONbits.IRCF0 = 0;
                OSCCONbits.IRCF1 = 1;       //250MHZ
                OSCCONbits.IRCF2 = 0;
                break;
              case 12:
                OSCCONbits.IRCF0 = 1;
                OSCCONbits.IRCF1 = 0;       //125kHZ
                OSCCONbits.IRCF2 = 0;
                break;
              case 31:
                OSCCONbits.IRCF0 = 0;
                OSCCONbits.IRCF1 = 1;       //31kHZ
                OSCCONbits.IRCF2 = 1;
                break;
              default:
                OSCCONbits.IRCF0 = 0;
                OSCCONbits.IRCF1 = 1;       //4MHZ
                OSCCONbits.IRCF2 = 1;
                break;
        }

}

void initAN(uint8_t bin, uint8_t just){ //just 0 es izquierda, 1 derecha
        
     ANSEL = bin;  //Apagar analogo
     ANSELH = 0b00000000;
     
     
     ADCON0bits.CHS= 0;
     __delay_us(100);

     ADCON0bits.ADON = 1;      //Activar modulo
     ADCON0bits.ADCS = 1;      //ADC clock Fosc/8



     ADCON1bits.ADFM = just;      //Justificado izquierdo
     ADCON1bits.VCFG0 = 0;     //Referencia alta 
     ADCON1bits.VCFG1 = 0;     //Referencia baja
     
     PIE1bits.ADIE= 1;         //Encender activar interrupcion del ADS
   }

/*uint8_t readAN (uint8_t canal){
    uint8_t lec; 
    switch(canal){    //Ver canal 0
         case 0:
            lec = ADRESH;     //Mover a leds
            break;
         case 1:
            lec = ADRESH;
            break;
         case 2:
            lec = ADRESH;
            break;
         case 3:
            lec = ADRESH;
            break;
         case 4:
            lec = ADRESH;
            break;
         case 5:
            lec = ADRESH;
            break;
         case 6:
            lec = ADRESH;
            break;
         case 7:
            lec = ADRESH;
            break;
         case 8:
            lec = ADRESH;
            break;
         case 9:
            lec = ADRESH;
            break;
         case 10:
            lec = ADRESH;
            break;
         case 11:
            lec = ADRESH;
            break;
         case 12:
            lec = ADRESH;
            break;
         case 13:
            lec = ADRESH;
            break;
        }
    return(lec);
}*/


void chselect (uint8_t cant){
    if(ADCON0bits.GO == 0){
      switch (ADCON0bits.CHS){
            
          case 0:
            if (cant == 1){
                ADCON0bits.CHS = 0;            //Si solo hay un canal activo 
            }                                  //se mantiene en 0
            else{
                ADCON0bits.CHS = 1;        //Cambiar a canal 1
            }
            break;
         case 1:
            if (cant == 2){
                ADCON0bits.CHS = 0;            //Si solo se usan dos canales
            }                                  //Se regresa a 0
            else{
                ADCON0bits.CHS = 2;        //Cambiar a canal 2
            }
            break;
         case 2:
            if (cant == 3){
                ADCON0bits.CHS = 0;
            }
            else{
                ADCON0bits.CHS = 3;        //Cambiar a canal 3
            }
            break;
         case 3:
            if (cant == 4){
                ADCON0bits.CHS = 0;
            }
            else{
                ADCON0bits.CHS = 4;        //Cambiar a canal 4
            }
            break;
         case 4:
            if (cant == 5){
                ADCON0bits.CHS = 0;
            }
            else{
                ADCON0bits.CHS = 5;        //Cambiar a canal 5
            }
            break;
         case 5:
            if (cant == 6){
                ADCON0bits.CHS = 0;
            }
            else{
                ADCON0bits.CHS = 6;        //Cambiar a canal 1
            }
            break;
         case 6:
            if (cant == 7){
                ADCON0bits.CHS = 0;
            }
            else{
                ADCON0bits.CHS = 7;        //Cambiar a canal 1
            }
            break;
         case 7:
            if (cant == 8){
                ADCON0bits.CHS = 0;
            }
            else{
                ADCON0bits.CHS = 8;        //Cambiar a canal 1
            }
            break;
         case 8:
            if (cant == 9){
                ADCON0bits.CHS = 0;
            }
            else{
                ADCON0bits.CHS = 9;        //Cambiar a canal 1
            }
            break;
         case 9:
            if (cant == 10){
                ADCON0bits.CHS = 0;
            }
            else{
                ADCON0bits.CHS = 10;        //Cambiar a canal 1
            };
            break;
         case 10:
            if (cant == 11){
                ADCON0bits.CHS = 0;
            }
            else{
                ADCON0bits.CHS = 11;        //Cambiar a canal 1
            }
            break;
         case 11:
            if (cant == 12){
                ADCON0bits.CHS = 0;
            }
            else{
                ADCON0bits.CHS = 12;        //Cambiar a canal 1
            }
            break;
         case 12:
            if (cant == 13){
                ADCON0bits.CHS = 0;
            }
            else{
                ADCON0bits.CHS = 13;        //Cambiar a canal 1
            }
            break;
         case 13:
                ADCON0bits.CHS = 0; //obligatoriamente tiene que regresar a 0
            
            break;
        }
    }
        
    __delay_us(150);
    ADCON0bits.GO = 1;
}



uint8_t table(uint8_t val){
    uint8_t tempo;
    
    switch(val){
        case 0:
            tempo = 0b00111111;
            break;
        case 1:
            tempo = 0b00000110;
            break;
        case 2:
            tempo = 0b01011011;
            break;
        case 3:
            tempo = 0b01001111;
            break;
        case 4:
            tempo = 0b01100110;
            break;
        case 5:
            tempo = 0b01101101;
            break;
        case 6:
            tempo = 0b01111101;
            break;
        case 7:
            tempo = 0b00000111;
            break;
        case 8:
            tempo = 0b01111111;
            break;
        case 9:
            tempo = 0b01100111;
            break;
        case 10:    
            tempo = 0b01110111; // A
            break;
        case 11:
            tempo = 0b01111100; //b
            break;
        case 12: 
            tempo = 0b00111001; //C
            break;
        case 13: 
            tempo = 0b01011110; //d
            break;
        case 14:
            tempo = 0b01111001; //E
            break;
        case 15: 
            tempo = 0b01110001; //F
            break;
            
            default:
                tempo = 0b00111111;
        }
        return(tempo);
}

void initEUSART(uint8_t tx, uint8_t rx){ //Enable interrupt Tx y Rx
//CONFIG EUSART
    
  //TX CONFIG
  TXSTAbits.SYNC = 0;       //Modo Asincrono
  TXSTAbits.BRGH = 1;       //HIGH SPEED
  TXSTAbits.TX9 = 0;       //Desactivar envio de 9 bits
  TXSTAbits.TXEN= 1;        //Encender TX
  RCSTAbits.SPEN = 1;       //Activar Serial PORT
  
  //RX CONFIG
  RCSTAbits.RX9 = 0;        //Desactivar recepcion de 9 bits
  RCSTAbits.CREN = 1;       //Activa la recepcion continua 
  
  //BAUD RATE CONTROL
    BAUDCTLbits.BRG16 = 0;  //Generador de 8bits activo)
    SPBRG =25;
    SPBRGH = 1;
   
    PIE1bits.TXIE =tx; //Encender tx o rx interrupt
    PIE1bits.RCIE =rx;
}

void pushPORTB(uint8_t val){
  TRISB = val; //Activar el tris para input
  WPUB = val; //Activar el weak pull up
  IOCB = val; //Activar interrupt on change
  INTCONbits.RBIE = 1; //Activar la interrupción
}
#endif	/* MY_LIB_H */

