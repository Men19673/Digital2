/*
 * Archivo: Main.c
 * Dispositivo: PIC16F887
 * Autor: Diego Mendez
 * Compilador: XC8 (v2.32), MPLABX v5.40
 * Programa: Utilizando SPI
 * Hardware: 2Pot, Leds
 * Created on July 26, 2021, 6:10 PM
 */
#include <xc.h>
#include <stdint.h>
#include "my_lib.h"
#include "I2C.h"
#include <pic16f887.h>

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


#define _XTAL_FREQ      8000000 //Definir la frecuencia de operacion, cambiar en 
                                //Cambiar en libreria

/******************************Prototipos**************************************/

void setup(void);   //Anunciar funcion setup
uint8_t table(uint8_t);     //Funcion tabla


/********************************Variables*************************************/
uint8_t flagint;
uint8_t z;
uint8_t cont;
uint8_t inI2C;
uint8_t varPot0;

/********************************Interrupcion**********************************/
void __interrupt()isr(void){
  
    
    
    
    if(INTCONbits.RBIF){
        if(RB0 == 0){
            cont++;
            if(cont > 0x0F){
                cont = 0;
            }
        }
        if(RB1 == 0){
            cont--;
            if(cont > 0x0F){
                cont = 0x0F;
            }
        }
        INTCONbits.RBIF = 0;  
    }
    
     if(PIR1bits.SSPIF == 1){ 

        SSPCONbits.CKP = 0;
       
        if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)){
            z = SSPBUF;                 // Read the previous value to clear the buffer
            SSPCONbits.SSPOV = 0;       // Clear the overflow flag
            SSPCONbits.WCOL = 0;        // Clear the collision bit
            SSPCONbits.CKP = 1;         // Enables SCL (Clock)
        }

        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {
            //__delay_us(7);
            z = SSPBUF;                 // Lectura del SSBUF para limpiar el buffer y la bandera BF
            //__delay_us(2);
            PIR1bits.SSPIF = 0;         // Limpia bandera de interrupción recepción/transmisión SSP
            SSPCONbits.CKP = 1;         // Habilita entrada de pulsos de reloj SCL
            while(!SSPSTATbits.BF);     // Esperar a que la recepción se complete
            inI2C = SSPBUF;             // Guardar en el PORTD el valor del buffer de recepción
            __delay_us(250);
            
        }
        else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
            z = SSPBUF;
            BF = 0;
            SSPBUF = cont;
            SSPCONbits.CKP = 1;
            __delay_us(250);
            while(SSPSTATbits.BF);
        }
       
        PIR1bits.SSPIF = 0;    
    }
    
    
        
}
/****************************** MAIN ******************************************/
void main(void) {
    setup();
    
    

/****************************** LOOP ******************************************/
while(1) {
    PORTD = cont;
 }
}



/********************************Subrutinas************************************/
void setup(void){
  
  
  ANSELH = 0b00000000;
  
  TRISA = 0b00000000;     //Output     input para AN0y1, input SS'
  TRISB = 0b00000011; //Output   
  TRISC = 0b00000000;     //Output
  TRISD = 0x00;     //Output
  TRISE = 0x00;     //Output
  
  OPTION_REG = 0b11000100; //pullup off, INTEDG, TOSC(int),Presc TMR0, Presc val
  
 
  
  pushPORTB(0b00000011); //Activar weak pullup y interrupt on change
  initOsc(8);   //utilizar oscilador interno para reloj del sistema a 4MHz
  I2C_Slave_Init(0x70);
  
  PORTA = 0x00;
  PORTB = 0x00;
  PORTC = 0x00; //Poner todos los puertos en 0
  PORTD = 0x00;
  PORTE = 0x00;
  
 //Interrupciones
  
  PIE1 = 0b00001000; // 0, adie, rcie, txie, SSPIE, ccp1ie, tmr2, tmr1
  PIE2 = 0b00000000; // osfie, c2ie, c1ie, eeie, bclie, 0, ccpie2
  PIR1 = 0x00; //Limpiar banderas
  PIR2 = 0x00;
  INTCON = 0b11001000;  //GIE, PIE, toie, inte, RBIE, t0if, intf, rbif
}