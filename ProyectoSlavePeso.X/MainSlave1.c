/*
 * Archivo: Main.c
 * Dispositivo: PIC16F887
 * Autor: Diego Mendez y Gabriel Fong
 * Compilador: XC8 (v2.32), MPLABX v5.40
 * Programa: Conección del Motor DC, Sensor peso e IR
 * Hardware: 1 Motor DC, 1Sensor Peso y 1 Sensor IR
 * Created on August 21, 2021, 5:10 PM
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
void ctrservo(void);


/********************************Variables*************************************/
uint8_t flagint;
uint8_t z;
uint8_t cont;
uint8_t inI2C;
uint8_t outI2C;
uint8_t sensorIR;
uint8_t weight;
uint8_t PWM;
uint8_t cont;
uint8_t bandera;
/********************************Interrupcion**********************************/
void __interrupt()isr(void){
    
    
    if (PIR1bits.TMR1IF){ 
        PIR1bits.TMR1IF = 0;
        TMR1H	 = 0x3C;
        TMR1L	 = 0xB0;

//        TMR1H	 = 0xF8;
//        TMR1L	 = 0x30;
        
        if(bandera == 1){
            cont++;
        }
        else if(cont>= 100){
            cont=0;         //Reiniciar conteo
            bandera = 0;    //Apagar bandera
            RA2 = 0;        //Apagar banda
            PWM = 255;      //Regresar servo
        }
    }
  
     if(PIR1bits.ADIF){
        if(ADCON0bits.CHS == 0){    //Ver canal 0
            weight = ADRESL;     //Mover a leds
        }
        PIR1bits.ADIF = 0;
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
            z = SSPBUF;                 // Lectura del SSBUF para limpiar el buffer y la bandera BF 
            PIR1bits.SSPIF = 0;         // Limpia bandera de interrupción recepción/transmisión SSP
            SSPCONbits.CKP = 1;         // Habilita entrada de pulsos de reloj SCL
            while(!SSPSTATbits.BF);     // Esperar a que la recepción se complete
            inI2C = SSPBUF;             // Guardar en el PORTD el valor del buffer de recepción
            __delay_us(250);
            
            switch(inI2C){
                case(0x01):
                    outI2C = weight;
                    break;

                case(0x02):
                    outI2C = sensorIR;
                    break;
                    }
            }
        else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
            z = SSPBUF;
            BF = 0;
            SSPBUF = outI2C;
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
    chselect(1);        //Multiplexea solo un canal
    
        
    if(PORTAbits.RA1 == 1){ //Verficar estdo del sensor
        sensorIR = 0;
    }
    else {                  //Verficar estado del sensor
        sensorIR = 1;
        bandera = 1;
    }
  
    
    if(cont <= 49){          //Si conteo es menor a tres tener apagado el motor
        RA2 = 0;            // y posiscion del servo en 180
        PWM = 255;
        ctrservo();
    }
    
    if(cont == 50){
        RA2 = 1;            //Encender la banda
        for(PWM = 255; PWM > 0; PWM--){
            ctrservo();
        }
    }
    
    PORTD = weight;
 }
}



/********************************Subrutinas************************************/
void setup(void){
  
  
  ANSELH = 0b00000000;
  
  TRISA = 0b00000011;     //Output     input para AN0y1, input SS'
  TRISB = 0b00000000; //Output   
  TRISC = 0b00000010;     //Output
  TRISD = 0x00;     //Output
  TRISE = 0x00;     //Output
  
  OPTION_REG = 0b11000100; //pullup off, INTEDG, TOSC(int),Presc TMR0, Presc val
 
  initOsc(8);   //utilizar oscilador interno para reloj del sistema a 4MHz
  I2C_Slave_Init(0x50);
  initAN(0b00000001, 1); //Inicializar AN y justificar a derecha para mayor sens
  
  //Timer 1
  T1CON	 = 0x21;
  PIR1bits.TMR1IF = 0;
  TMR1H	 = 0x3C;
  TMR1L	 = 0xB0;


  
  //Timer 2
    T2CON= 0x4E; //20ms
    PR2	 = 250;
//  T2CON	 = 0x2D; //3ms
//  PR2	 = 250;

 //PWM
  CCP2CON = 0b00001111; //XX, PWM 1100
  PWM = 255;
  
  PORTA = 0x00;
  PORTB = 0x00;
  PORTC = 0x00; //Poner todos los puertos en 0
  PORTD = 0x00;
  PORTE = 0x00;
  
 //Interrupciones
  
  PIE1 = 0b01001001; // 0, ADIE, rcie, txie, SSPIE, ccp1ie, tmr2, TMR1
  PIE2 = 0b00000000; // osfie, c2ie, c1ie, eeie, bclie, 0, ccpie2
  PIR1 = 0x00; //Limpiar banderas
  PIR2 = 0x00;
  INTCON = 0b11000000;  //GIE, PIE, toie, inte, rbie, t0if, intf, rbif
  TRISCbits.TRISC1 =0;
}

void ctrservo (void) {
    
    CCPR2L = (((0.247 * PWM) + 62)*2);
   // CCPR2L = (((0.467*PWM)+31)*2);            //MAPEO DEL SERVO2
}