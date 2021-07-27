/*
 * Archivo: Main.c
 * Dispositivo: PIC16F887
 * Autor: Diego Mendez
 * Compilador: XC8 (v2.32), MPLABX v5.40
 * Programa: Utilizando LCD
 * Hardware: 2Pot, 1DisplaysLCD y Leds
 * Created on July 26, 2021, 6:10 PM
 */
#include <xc.h>
#include <stdint.h>
#include "my_lib.h"
#include "LCD8bits.h"


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
uint8_t flagint;
uint8_t startfinal;
uint8_t start;
uint8_t RXREC;
uint8_t var0;
uint8_t var1;
uint8_t contador;
uint8_t tempo1;
uint8_t varUART;
char unidades;
char decenas;
char centenas;
float valor;
unsigned char  str[50] = " Los valores de los potenciometros son:\r S1 \r S2";
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
            var0 = ADRESH;     //Mover a leds
        }
        else{                   //ver canal 1
            var1 = ADRESH;       //Guardar en variable para display
        }
        PIR1bits.ADIF = 0;
        
    }
    
    if(PIR1bits.RCIF == 1){
        RXREC = RCREG;      //Guardar el dato que se recibe en uart 
        if (RXREC == 43){
            contador++;     //Incrementar el valor con RX
        }
        if (RXREC == 45){
            contador--;     //Decrementar el valor con RX
        }
        PIR1bits.RCIF =0;   //Limpiar la bandera
    }
    
    if(RBIF == 1){        
     RBIF = 0;
    }
        
}
/****************************** MAIN ******************************************/
void main(void) {
    setup();
    Lcd_Init();
    

/****************************** LOOP ******************************************/
while(1) {
    chselect(2);            //el dos simboliza que solo se esta utilizando un canal
    Lcd_Clear();            //Limpiar LCD
    Lcd_Set_Cursor(1,1);    //cursor fila uno primera posicion 
    Lcd_Write_String("S1:   S2:  CONT:");
    
     while(varUART <= 50){      //verficar que no pase del limite 
           varUART++;           //Ir cambiando de character
                   
       if(TXIF == 1){
        TXREG = str[varUART];   //Enviar a terminal palabras
       }
        __delay_ms(10);
     }
    //Potenciometro 1
    decimal(var0);              //Convertir a decimales y a CHAR
    Lcd_Set_Cursor(2,1);        //Llevar el cursor a fila 2 primer espacio
    Lcd_Write_Char(centenas);
    Lcd_Write_String(".");
    Lcd_Write_Char(decenas);
    Lcd_Write_Char(unidades);
    Lcd_Write_String("  ");

    
         if(TXIF == 1){
            TXREG = centenas; //Enviar a terminal palabras
           }
        __delay_ms(10);
        if(TXIF == 1){
            TXREG = 46; //Enviar a terminal palabras
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
            TXREG = 13; //Enviar a terminal palabras
           }
        __delay_ms(10);
  
    //Potenciometro 2
    decimal(var1);              //Convertir a decimales y a CHAR
    Lcd_Write_Char(centenas);
    Lcd_Write_String(".");
    Lcd_Write_Char(decenas);        
    Lcd_Write_Char(unidades);
    Lcd_Write_String("  ");
  
        if(TXIF == 1){
            TXREG = centenas; //Enviar a terminal palabras
           }
        __delay_ms(10);
        if(TXIF == 1){
            TXREG = 46; //Enviar a terminal palabras
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
            TXREG = 13; //Enviar a terminal palabras
           }
        __delay_ms(10);
        
    //ContadorRX
    decimal(contador);          //Convertir a decimales y a CHAR
    Lcd_Write_Char(centenas);
    Lcd_Write_String(".");
    Lcd_Write_Char(decenas);
    Lcd_Write_Char(unidades);
    
    
    __delay_ms(100);
   
    
 
    }
}



/********************************Subrutinas************************************/
void setup(void){
  
  
  ANSELH = 0b00000000;
  
  TRISA = 0b00000011;     //Output     
  TRISB = 0b00000000; //Output excepto por pin 0, 1 y 2   
  TRISC = 0b10000000;     //Output
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
  initEUSART(0,1); //Encender el modulo EUSART (txie, RXIE)
  PORTA = 0x00;
  PORTB = 0x00;
  PORTC = 0x00; //Poner todos los puertos en 0
  PORTD = 0x00;
  PORTE = 0x00;
  
 //Interrupciones
  
  PIE1 = 0b01000000; // 0, ADIE, rcie, txie, sspie, ccp1ie, tmr2, tmr1
  PIE2 = 0b00000000; // osfie, c2ie, c1ie, eeie, bclie, 0, ccpie2
  PIR1 = 0x00; //Limpiar banderas
  PIR2 = 0x00;
  INTCON = 0b11000000;  //GIE, PIE, toie, inte, rbie, t0if, intf, rbif
}
    
 


void decimal(uint8_t variable){
    
    valor = variable;   
    valor = (valor/255)*500;//convertir a volt
    centenas = (valor/100) ;       //dividir entre 100 para centenas
    valor = (valor - (centenas*100));
    decenas = (valor/10);         //dividir entre 10 para decenas
    valor = (valor - (decenas*10));
    unidades = (valor);         //dividir entre 1 para unidades*/
     
    
    
    centenas = centenas + 48; //Sumar 48 para que case con ASCII
    decenas = decenas + 48;
    unidades = unidades + 48;
    
    
    
    
    
    
    
    
}
