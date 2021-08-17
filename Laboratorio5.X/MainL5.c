/*
 * Archivo: Main.c
 * Dispositivo: PIC16F887
 * Autor: Diego Mendez
 * Compilador: XC8 (v2.32), MPLABX v5.40
 * Programa: Utilizando Adafruit
 * Hardware: 2Pot, 1DisplaysLCD y Leds
 * Created on July 26, 2021, 6:10 PM
 */
#include <xc.h>
#include <stdint.h>
#include "my_lib.h"



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


#define _XTAL_FREQ      4000000 //Definir la frecuencia de operacion, cambiar en 
                                //Cambiar en libreria

/******************************Prototipos**************************************/

void setup(void);   //Anunciar funcion setup
uint8_t table(uint8_t);     //Funcion tabla
void final (void);  //
void inicio(void);  //
void dispasign(uint8_t , uint8_t );
void hexconv(uint8_t );
void decimal(uint8_t );

/********************************Variables*************************************/
uint8_t RXREC;
uint8_t var0;
uint8_t var1;
uint8_t contador;
uint8_t flaglec;
uint8_t varUART;
char unidades;
char decenas;
char centenas;
float valor;

/********************************Interrupcion**********************************/
void __interrupt()isr(void){
 
    
    if(PIR1bits.ADIF){
       
        PIR1bits.ADIF = 0;
        
    }
    
    if(PIR1bits.RCIF == 1){
        RXREC = RCREG;      //Guardar el dato que se recibe en uart 
        if (RXREC == 0xFF){
            flaglec = 1;
        }
        if (RXREC == 0x01){
            while(TXIF == 0){}
            PORTD = RCREG;
        
        }
        
        PIR1bits.RCIF =0;   //Limpiar la bandera
    }
    
    if(RBIF == 1){
       if(RB0 == 0){ //Revisar si cambio algun boton
           contador++;

       }
       if(RB1 == 0){
           contador--; 
       } 
    RBIF = 0;
    }
        
}
/****************************** MAIN ******************************************/
void main(void) {
    setup();
   
    

/****************************** LOOP ******************************************/
while(1) {
   
    
    if  (flaglec ==1){
        decimal(contador);
        if(TXIF == 1){
               TXREG = centenas; //Enviar a terminal palabras
               }
            __delay_ms(10);

        if(TXIF == 1){
            TXREG = decenas; //Enviar a terminal palabras
           }
        __delay_ms(10);
        if(TXIF == 1){
            TXREG = unidades; //Enviar a terminal palabras
           }
        __delay_ms(10);
        if(TXIF == 1){
            TXREG = 13; //Enviar enter
           }


        __delay_ms(100);

         }
 
    }
}



/********************************Subrutinas************************************/
void setup(void){
  
  
  ANSELH = 0b00000000;
  
  TRISA = 0b00000000;     //Output     
  TRISB = 0b00000000; //Output excepto por pin 0, 1 y 2   
  TRISC = 0b10000000;     //Output
  TRISD = 0x00;     //Output
  TRISE = 0x00;     //Output
  
  OPTION_REG = 0b01000100; //pullup on, INTEDG, TOSC(int),Presc TMR0, Presc val
  
  

  initOsc(4);   //utilizar oscilador interno para reloj del sistema a 4MHz
  initEUSART(0,1); //Encender el modulo EUSART (txie, RXIE)
  pushPORTB(0b00000011);
  PORTA = 0x00;
  PORTB = 0x00;
  PORTC = 0x00; //Poner todos los puertos en 0
  PORTD = 0x00;
  PORTE = 0x00;
  
 //Interrupciones
  
  PIE1 = 0b00100000; // 0, adie, RCIE, txie, sspie, ccp1ie, tmr2, tmr1
  PIE2 = 0b00000000; // osfie, c2ie, c1ie, eeie, bclie, 0, ccpie2
  PIR1 = 0x00; //Limpiar banderas
  PIR2 = 0x00;
  INTCON = 0b11001000;  //GIE, PIE, toie, inte, RBIE, t0if, intf, rbif
}
    
 


void decimal(uint8_t variable){
    
    valor = variable;   
    //valor = (valor/255)*100;//convertir a volt
    centenas = (valor/100) ;       //dividir entre 100 para centenas
    valor = (valor - (centenas*100));
    decenas = (valor/10);         //dividir entre 10 para decenas
    valor = (valor - (decenas*10));
    unidades = (valor);         //dividir entre 1 para unidades*/
     
    
    
    centenas = centenas + 48; //Sumar 48 para que case con ASCII
    decenas = decenas + 48;
    unidades = unidades + 48;
    
    
}
