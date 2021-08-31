/* 
 * File:   HX711.h
 * Author: diego
 *
 * Created on August 24, 2021, 7:24 PM
 */


#include <xc.h> // include processor files - each processor file is guarded.  
#include <pic16f887.h>
#include <stdint.h>

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000
#endif

#ifndef ck
#define ck RA0 
#endif

#ifndef dat
#define dat RA1 
#endif


int32_t offset;


void hx711_init();   //inicia el hx711
int8_t hx711_pulso();       //un pulso para leer un bit
int32_t hx711_lectura(uint8_t ganancia);   //funcion de lectura general
int32_t hx711_promedio(uint8_t veces, uint8_t ganancia); //lectura con promedio
void tarar(uint8_t veces,uint8_t ganancia);   //captura el offset tara la balanza: numero de datos, a que ganancia