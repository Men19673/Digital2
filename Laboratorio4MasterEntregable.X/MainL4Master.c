/*
 * Archivo: MainL4Master.c
 * Dispositivo: PIC16F887
 * Autor: Diego Mendez
 * Compilador: XC8 (v2.32), MPLABX v5.40
 * Programa: Utilizando I2C
 * Hardware: 2Pot, Leds, Sensor I2C, 3Pic16F887, LCD
 * Created on August 8, 2021, 10:10 PM
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


/********************************Variables*************************************/
uint8_t flagint;
uint8_t startfinal;
uint8_t start;
uint8_t RXREC;
uint8_t varPot0;
uint8_t valor;
uint8_t cont;
char unidades;
char decenas;
char centenas;

/********************************Interrupcion**********************************/
void __interrupt()isr(void){
    
    
    
    
        
}
/****************************** MAIN ******************************************/
void main(void) {
    setup();
   
    

/****************************** LOOP ******************************************/
while(1) {
    
    
    __delay_ms(200);
    
    I2C_Master_Start();
    I2C_Master_Write(0x91);
    varPot0 = I2C_Master_Read(0);
    I2C_Master_Stop();
    __delay_ms(200);
    
    
    
    
    
    PORTD = varPot0;
   __delay_ms(200);
    
    }
}



/********************************Subrutinas************************************/
void setup(void){
  
  
  ANSELH = 0b00000000;
  
  TRISA = 0b00000000;     //Output     
  TRISB = 0b00000000; //Output excepto por pin 0, 1 y 2   
  TRISC = 0b00000000;     //Output
  TRISD = 0b00000000;     //Output
  TRISE = 0x00;     //Output
  
  
  
  OPTION_REG = 0b11000100; //pullup off, INTEDG, TOSC(int),Presc TMR0, Presc val

  initOsc(8);   //utilizar oscilador interno para reloj del sistema a 8MHz
  I2C_Master_Init(100000);        // Inicializar Comuncación I2C
  
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
  INTCON = 0b00000000;  //GIE, PIE, toie, inte, rbie, t0if, intf, rbif
}
    
 





