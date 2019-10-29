/*
 * llamadasalsistema.c
 *
 *  Created on: Oct 12, 2019
 *      Author: osvaldofdez
 */
int ServicioLeer(int a,char* b,int t);
int ServicioEscribir(int a,char* b,int t);
void ServicioTicks(int* ticks);
void ServicioInitPWM();
void ServicioPWMDutyCycle(uint16_t pulsos);
void ServicioStopPWM();

void LlamadaSistema(int p1,int p2,int p3,int p4) {
	//Eligiendo el servicio a consumir
   switch(p4) {
   case 1:
	   ServicioLeer(p1,(char*)p2,p3);
	   break;
   case 2:
	   ServicioEscribir(p1,(char*)p2,p3);
	   break;
   case 3:
	   ServicioTicks(p1);
	   break;
   case 4:
	   ServicioInitPWM();
	   break;
   case 5:
	   ServicioStopPWM();
	   break;
   case 6:
	   ServicioPWMDutyCycle(p1);
	   break;
   }
   return 0;
}

