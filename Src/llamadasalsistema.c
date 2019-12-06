/*
 * llamadasalsistema.c
 *
 *  Created on: Oct 12, 2019
 *      Author: osvaldofdez
 */
#include <stdint.h>

int ServicioLeer(int a,char* b,int t);
int ServicioEscribir(int a,char* b,int t);
void ServicioTicks(uint32_t* ticks);
void ServicioInitPWM();
void ServicioPWMDutyCycle(uint16_t pulsos);
void ServicioStopPWM();

void LlamadaSistema(int p1,int p2,int p3,int p4) {
	//Eligiendo el servicio a consumir
   switch(p4) {
   case 5:
	   ServicioLeer(p1,(char*)p2,p3);
	   break;
   case 6:
	   ServicioEscribir(p1,(char*)p2,p3);
	   break;
   case 7:
	   ServicioTicks(p1);
	   break;
   case 8:
	   ServicioInitPWM();
	   break;
   case 9:
	   ServicioStopPWM();
	   break;
   case 10:
	   ServicioPWMDutyCycle(p1);
	   break;
   }
}

