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
#include "SPI.h"
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


#define _XTAL_FREQ      4000000 //Definir la frecuencia de operacion, cambiar en 
                                //Cambiar en libreria

/******************************Prototipos**************************************/

void setup(void);   //Anunciar funcion setup
uint8_t table(uint8_t);     //Funcion tabla


/********************************Variables*************************************/
uint8_t flagint;
uint8_t startfinal;
uint8_t start;
uint8_t inSPI;
uint8_t varPot0;
uint8_t varPot1;
/********************************Interrupcion**********************************/
void __interrupt()isr(void){
  
    
    if (T0IF==1){ 
    //TMR0		 = 100;         //Resetear timer0
    INTCONbits.T0IF = 0;         
    }
    
    if(TMR1IF == 1){
        PIR1bits.TMR1IF =0;     //Resetear tmr1
    }
    
    if(PIR1bits.ADIF){
        if(ADCON0bits.CHS == 0){    //Ver canal 0
            varPot0 = ADRESH;     //Mover a leds
        }
        else{                   //ver canal 1
            varPot1 = ADRESH;       //Guardar en variable para display
        }
        PIR1bits.ADIF = 0;
        
    }
    
    if(SSPIF == 1){
        inSPI = 0;
        inSPI = spiRead();      //Verificamos que valor se le solicita al Slave
     
        if (inSPI == 0x01){
            spiWrite(varPot0);
        }
        if (inSPI == 0x02){
            spiWrite(varPot1);
        }
        SSPIF = 0;
    }
    
    
        
}
/****************************** MAIN ******************************************/
void main(void) {
    setup();
    
    

/****************************** LOOP ******************************************/
while(1) {
    chselect(2);        //el dos simboliza que solo se esta utilizando un canal
    PORTB = varPot0;
    PORTD = varPot1;
 }
}



/********************************Subrutinas************************************/
void setup(void){
  
  
  ANSELH = 0b00000000;
  
  TRISA = 0b00100011;     //Output     input para AN0y1, input SS'
  TRISB = 0b00000000; //Output   
  TRISC = 0b00011000;     //Output
  TRISD = 0x00;     //Output
  TRISE = 0x00;     //Output
  
  initAN(0b00000011, 0); //Inicializar AN y justificar a izquierda (0)  
  WPUB = 0b00000000; //Activar el weak pull up
  IOCB = 0b00000000; //Activar interrupt on change
  
  OPTION_REG = 0b11000100; //pullup off, INTEDG, TOSC(int),Presc TMR0, Presc val
  T1CON	 = 0x00;
  TMR1IF = 0;
  TMR1H	 = 0x3C;
  TMR1L	 = 0xB0;
  

  initOsc(4);   //utilizar oscilador interno para reloj del sistema a 4MHz
  spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
  
  PORTA = 0x00;
  PORTB = 0x00;
  PORTC = 0x00; //Poner todos los puertos en 0
  PORTD = 0x00;
  PORTE = 0x00;
  
 //Interrupciones
  
  PIE1 = 0b01001000; // 0, ADIE, rcie, txie, SSPIE, ccp1ie, tmr2, tmr1
  PIE2 = 0b00000000; // osfie, c2ie, c1ie, eeie, bclie, 0, ccpie2
  PIR1 = 0x00; //Limpiar banderas
  PIR2 = 0x00;
  INTCON = 0b11000000;  //GIE, PIE, toie, inte, rbie, t0if, intf, rbif
}
    
 

    
