/*
 * Archivo: Main.c
 * Dispositivo: PIC16F887
 * Autor: Diego Mendez
 * Compilador: XC8 (v2.32), MPLABX v5.40
 * Programa: Utilizando Interrupts, un contadores decimales y luces
 * Hardware: Pushbuttons, 1Displays y Leds
 * Created on April 19, 2021, 6:10 PM
 */
#include <xc.h>
#include <stdint.h>

/***************************Configuration Words********************************/
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RC oscillator: 
                                // CLKOUT function on RA6/OSC2/CLKOUT pin, 
                                // RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and
                                // can be enabled by SWDTEN bit of the WDTCON
                                //register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR 
                                // pin function is digital input, MCLR 
                                // internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code 
                                // protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code 
                                // protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/
                                // External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit 
                                // (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit 
                                // (RB3 pin has digital I/O, HV on MCLR must be 
                                // used for programming)
// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out 
                                // Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits
                                // (Write protection off)


#define _XTAL_FREQ      4000000 //Definir la frecuencia de operacion

/******************************Prototipos**************************************/

void setup(void);   //Anunciar funcion setup

uint8_t table(uint8_t);     //Funcion tabla
void final (void);
void inicio(void);
/********************************TABLA*****************************************/

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
        
        default:
            tempo = 0b00111111;
    }
    return(tempo);
}

/********************************Variables*************************************/
uint8_t flagint;
uint8_t startfinal;
uint8_t start;
uint8_t valor = 4;
uint8_t disp0;
uint8_t contador;
uint8_t j1;
uint8_t j2;
/********************************Interrupcion**********************************/
void __interrupt()isr(void){
  
    if(TMR1IF == 1){
        TMR1IF   = 0;
        TMR1H	 = 0x3C; //Setear en 100ms
        TMR1L	 = 0xB0;
        contador++;        //Sumar el contador 
        if(contador <= 10){ //Testear si ya funciono
            flagint =0;
        }
        else{
            flagint = 1;
            contador = 0;
        }
    }
    
    if(RBIF == 1){
        if(RB0 == 0){ //Revisar si cambio algun boton
            start = 1;
            j1 =0;
            j2 =0;
        }
        if(RB1 == 0){
            if(startfinal == 1){
            j1++;
           
            switch (j1){
            
                case(1):
                    RA0 = 1;
                    break;
                case(2):
                    RA1 = 1;
                    RA0 = 0;
                    break;
                case(3):
                    RA2 = 1;
                    RA1 =0;
                    break;
                case(4):
                    RA3 = 1;
                    RA2 = 0;
                    break;
                case(5):
                    RA4 = 1;
                    RA3 = 0;
                    break;
                case(6):
                    RA5 = 1;
                    RA4 = 0;
                    break;
                case(7):
                    RA6 = 1;
                    RA5 = 0;
                    break;
                case(8):
                    RA7 = 1;
                    RA6 = 0;
                    break;            
               }
            }
        }
        if(RB2 == 0){
           if(startfinal == 1){
        
            j2++;
             switch (j2){
            
                case(1):
                    RC0 = 1;
                    break;
                case(2):
                    RC1 = 1;
                    RC0 = 0;
                    break;
                case(3):
                    RC2 = 1;
                    RC1 = 0;
                    break;
                case(4):
                    RC3 = 1;
                    RC2 = 0;
                    break;
                case(5):
                    RC4 = 1;
                    RC3 = 0;
                    break;
                case(6):
                    RC5 = 1;
                    RC4 = 0;
                    break;
                case(7):
                    RC6 = 1;
                    RC5 = 0;
                    break;
                case(8):
                    RC7 = 1;
                    RC6 = 0;
                    break;            
            }
            
           }
        }
        
     RBIF = 0;
    }
        
}
/****************************** MAIN ******************************************/
void main(void) {
    setup();
    

/****************************** LOOP ******************************************/
while(1) {
    
   
    if(start == 1){
        inicio();
        }
    final();
    }
}



/********************************Subrutinas************************************/
void setup(void){
  
  ANSEL  = 0b00000000;  //Apagar analogo
  ANSELH = 0b00000000;
  
  TRISA = 0b00000000;     //Output     
  TRISB = 0b00000111; //Output excepto por pin 0, 1 y 2   
  TRISC = 0x00;     //Output
  TRISD = 0x00;     //Output
  TRISE = 0x00;     //Output
  
  WPUB = 0b00000111;
  IOCB = 0b00000111;
  
  OPTION_REG = 0b01000100; //prescaler en 32, activar PULLUP y WDT en timer0
  T1CON	 = 0x11;
  TMR1IF = 0;
  TMR1H	 = 0x3C;
  TMR1L	 = 0xB0;
  

  
  OSCCONbits.SCS = 1;   //utilizar oscilador interno para reloj del sistema
 
  PORTA = 0x00;
  PORTB = 0x00;
  PORTC = 0x00; //Poner todos los puertos en 0
  PORTD = 0x00;
  PORTE = 0x00;
 //Interrupciones
  
  INTCON = 0b11001000;  //GIE, PIE, toie, inte, RBIE, t0if, intf, rbif
  PIE1 = 0b00000001; // 0, adie, rcie, txie, sspie, ccp1ie, tmr2, TMR1
  PIE2 = 0b00000000; // osfie, c2ie, c1ie, eeie, bclie, 0, ccpie2
  PIR1 = 0x00; //Limpiar banderas
}
    
void inicio(void){
    RB6 = 0;
    RB7 = 0;
    if(flagint == 1){   //Ver si la bandera de un segundo esta arriba
        valor--;  
        if(valor == 3){
            PORTD = table(3);   //3seg antes
            RB3 = 1;            //Encender luz roja
            flagint = 0;
        }
        if(valor == 2){         //2 seg antes                    
            PORTD = table(2);   //Display en 2
            flagint = 0;
        }
        if(valor == 1){
            RB3 = 0;
            RB4 = 1;    //Apagar luz roja y encender amarilla 
            PORTD = table(1);   //Display en uno
            flagint = 0;
        }
        if(valor == 0){
            RB5 = 1;    //Apagr amarilla y encender verde
            RB4 = 0;
            PORTD = table(0);   //Display en 0
            startfinal = 1;
            flagint = 0;
        }
        if(flagint == 1){
            valor = 4;
            PORTD = 0;      //Reiniciar
            start = 0;
            
            RB5=0;
            
        }
    }
}  
void final(void){
        if (j1>=9){
            j1 = 0; //Resetear contador de jugador1
            RB6 = 1;
            PORTC =0;
            PORTA = 0;
            startfinal=0;
        }
        
        if (j2>=9){
            j2 =0; //Resetear contador de jugador2
            RB7 = 1; //encender luz de ganador
            PORTC =0;
            PORTA = 0;
            startfinal =0;
        }
    
    }
   