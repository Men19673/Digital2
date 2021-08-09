/*
 * File: LCD.h
 * Se utilizo y se adaptaron las librerias de Ligo George
 * de la pagina www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
 * Revision history:
 */

// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef    LCD8bits8_H
#define    LCD8bits8_H

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 8000000
#endif
// Definido con respecto al esquematico de proteus
#ifndef RS
#define RS PORTEbits.RE0 
#endif

#ifndef EN
#define EN RE1
#endif

#ifndef D0
#define D0 RD0
#endif

#ifndef D1
#define D1 RD1
#endif

#ifndef D2
#define D2 RD2
#endif

#ifndef D3
#define D3 RD3
#endif

#ifndef D4
#define D4 RD4
#endif

#ifndef D5
#define D5 RD5
#endif

#ifndef D6
#define D6 RD6
#endif

#ifndef D7
#define D7 RD7
#endif

#include <xc.h> // include processor files - each processor file is guarded.

//LCD Functions Developed by electroSome


void Lcd_Port(char a);

void Lcd_Cmd(char a);

void Lcd_Clear(void);

void Lcd_Set_Cursor(char a, char b);

void Lcd_Init(void);

void Lcd_Write_Char(char a);

void Lcd_Write_String(char *a);

void Lcd_Shift_Right(void);

void Lcd_Shift_Left(void);


#endif