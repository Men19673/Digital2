/* 
 * File:   HX711.c
 * Author: Diego A. Méndez
 * Libreria para utilizar el ADC HX711
 * Created on August 24, 2021, 7:24 PM
 */
#include "HX711.h"

int32_t offset;  //guarda el offset

void hx711_init()
{  TRISAbits.TRISA0=0;
   TRISAbits.TRISA1=1;
   ck=0;                //Iniciamos en 0 el clock
   __delay_ms(500);
}

int8_t hx711_pulso(){
    uint8_t lec;
    ck=1;           //Ponemos en HIGH el reloj
    __delay_us(1);
    lec=dat;
    ck=0;           //Ponemos en LOW el reloj
    __delay_us(1);
    return lec;
}

int32_t hx711_lectura(uint8_t ganancia){
    uint8_t cont;
    int32_t dato=0;


    while (dat==1);
  //da los primeros 24 pulsos
  for (cont=23; cont>=0; cont--){
     if (hx711_pulso()==1){
       dato = dato +( 1L<<cont);
     }
  }     //end for
      __delay_us(100);
      
     if (ganancia==128)  hx711_pulso();
     else if (ganancia==32){
      hx711_pulso();
      __delay_us(100);
      hx711_pulso();

      }
     else if (ganancia==64){
      hx711_pulso();
      __delay_us(100);
      hx711_pulso();
      __delay_us(100);
      hx711_pulso();
      }


  // Verifica si es negativo
    if ((dato & 0x800000)!=0)
    {
    dato= dato | 0xff000000;  //lo convierte a 32 bit con signo
    return  (-dato);// Se coloca - si no se quiere regersar valor negado
    }
    else     return  (dato);

}

int32_t hx711_promedio(uint8_t veces, uint8_t ganancia)   //numero de datos, a que ganancia
 {
        int32_t prom = 0;
        uint8_t cont;

        for (cont = 0; cont < veces; cont++){
          prom = prom +  hx711_lectura(ganancia);
           __delay_ms(100);
        }
        return (prom / cont);
}

void tarar(uint8_t veces, uint8_t ganancia)   //numero de datos, a que ganancia
 {
         offset = hx711_promedio(veces,ganancia);

}