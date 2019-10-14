/*
 * llamadasalsistema.c
 *
 *  Created on: Oct 12, 2019
 *      Author: osvaldofdez
 */
int ServicioLeer(int a,char* b,int t);
int ServicioEscribir(int a,char* b,int t);
void ServicioTicks(uint32_t* ticks);

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
   }
   return 0;
}

