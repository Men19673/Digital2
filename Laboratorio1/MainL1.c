/*
 * Archivo: Main.c
 * Dispositivo: PIC16F887
 * Autor: Diego Mendez
 * Compilador: XC8 (v2.32), MPLABX v5.40
 * Programa: Utilizando Interrupts, un contadores decimales y luces
 * Hardware: Pushbuttons, 1Displays y Leds
 * Created on July 13, 2021, 6:10 PM
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

/********************************Variables*************************************/
uint8_t flagint;
uint8_t startfinal;
uint8_t start;
uint8_t valor = 4;
uint8_t multiplex;
uint8_t var;
uint8_t contador;
uint8_t disp0;
uint8_t disp1;
uint8_t nibblelow;
uint8_t nibblehigh;
/********************************Interrupcion**********************************/
void __interrupt()isr(void){
  
    
    if (T0IF==1){ 
    TMR0		 = 100;         //Resetear timer0
    INTCONbits.T0IF = 0; 
    PORTB = 0x00;
    switch(multiplex){      //Multiplexado de las displays 
        case 0:
            PORTC = disp0;
            RB4 = 1;
            multiplex++;
            break;
            
        case 1:
            PORTC = disp1;
            RB5 = 1;
            multiplex= 0x00;
            break;
            
        
        }       
    }
    
    if(PIR1bits.ADIF){
        var = readAN(ADCON0bits.CHS);
        PIR1bits.ADIF = 0;
    }
    
    if(TMR1IF == 1){
        PIR1bits.TMR1IF =0;
    }
    
    if(RBIF == 1){
        if(RB0 == 0){ //Revisar si cambio algun boton
            PORTD++;
           
        }
        if(RB1 == 0){
            PORTD--; 
        }
        
        
     RBIF = 0;
    }
        
}
/****************************** MAIN ******************************************/
void main(void) {
    setup();
    

/****************************** LOOP ******************************************/
while(1) {
    chselect(1); //el uno simboliza que solo se esta utilizando un canal
    hexconv(var);
    dispasign(nibblehigh, nibblelow);
    if(var>=PORTD){
        RB3 =1;
    }
    else{
        RB3 =0;
    }
 
    }
}



/********************************Subrutinas************************************/
void setup(void){
  
  ANSEL  = 0b00000000;  //Apagar analogo
  ANSELH = 0b00000000;
  
  TRISA = 0b00000001;     //Output     
  TRISB = 0b00000011; //Output excepto por pin 0, 1 y 2   
  TRISC = 0x00;     //Output
  TRISD = 0x00;     //Output
  TRISE = 0x00;     //Output
  
  initAN(0b00000001, 0);
  
  WPUB = 0b00000011; //Activar el weak pull up
  IOCB = 0b00000011; //Activar interrupt on change
  
  OPTION_REG = 0b01000100; //prescaler en 32, activar PULLUP y WDT en timer0
  T1CON	 = 0x11;
  TMR1IF = 0;
  TMR1H	 = 0x3C;
  TMR1L	 = 0xB0;
  

  initOsc(4);
  OSCCONbits.SCS = 1;   //utilizar oscilador interno para reloj del sistema
 
  PORTA = 0x00;
  PORTB = 0x00;
  PORTC = 0x00; //Poner todos los puertos en 0
  PORTD = 0x00;
  PORTE = 0x00;
  
 //Interrupciones
  
  PIE1 = 0b00000000; // 0, adie, rcie, txie, sspie, ccp1ie, tmr2, tmr1
  PIE2 = 0b00000000; // osfie, c2ie, c1ie, eeie, bclie, 0, ccpie2
  PIR1 = 0x00; //Limpiar banderas
  PIR2 = 0x00;
  INTCON = 0b11101000;  //GIE, PIE, TOIE, inte, RBIE, t0if, intf, rbif
}
    
  

void dispasign(uint8_t arg1, uint8_t arg2){
    disp0 = table(arg1);
    disp1 = table(arg2); //Convertimos de numero binario al compatible con
   
    
}

void hexconv(uint8_t num){
    nibblelow = num & 0x0F;
    nibblehigh = num & 0xF0;
    
    nibblehigh >>= 4;

}
