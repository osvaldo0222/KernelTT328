/*
 * ioc.c
 *
 *  Created on: Oct 12, 2019
 *      Author: osvaldofdez
 */
#include "ioc.h"
#include "main.h"
#include "usart.h"
#include "tim.h"

//Funcion que sirve para transmitir por el puerto serial
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
//Indica donde se guardan los datos cuando llegan al puerto serial
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
//Funcion que indica donde se va recibir cada caracter cuando llegue por la interrupcion en el puerto serial
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
//Funcion del standard que inicia el huart3
HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart);
//Nueva consola de la estructura creada en ioc.h
sArchivo consola;

void InitConsola() {
	//Poniendo un idetificador a la consola inicializada
	consola.id = 1;
	//Iniciando las posiciones del buffer circular en 0
	consola.posIni = 0;
	consola.posFin = 0;
	//Archivo de donde se va leer y escribir indicado como el HUART3
	consola.harchivo = (void*)&huart3;
	//Iniciando el huart3 mediante la funcion proporcionada por el standard HAL
	HAL_UART_Init(&huart3);
	//Indica que la informacion se va recibir en buffer con un tamaño de 1.
	//Se genera una interrupcion por cada caracter que llegue al buffer.
	HAL_UART_Receive_IT(&huart3, consola.buffer, 1);

}

int ServicioLeer(int a,char* b,int t) {
	//Cant contiene la cantidad de caracteres que aun no se han leidos
	int Cant = (consola.posFin-consola.posIni)%1024;
	//En caso de que la cantidad sea menor a lo que se esta tratando de leer
	//Entonces solo se lee lo disponible
	if(Cant < t)t=Cant;
	//Se va incrementando la posicion donde esta el puntero de lectura en el buffer circular
	for(int i=0;i<t;i++,consola.posIni++)
		//Se guarda cada caracter en el buffer (b)
		b[i]=consola.buffer[(i+consola.posIni)%1024];
	//Se retorna la cantidad de caracteres leidos.
    return t;
}

int ServicioEscribir(int a,char* b,int t) {
	//Archivo donde se va escribir, es decir, el archivo del huart3
	UART_HandleTypeDef* htmp = (UART_HandleTypeDef*)consola.harchivo;
	//Funcion HAL que me permite escribir en el archivo de un HUART
	HAL_UART_Transmit(htmp, b,t, 1000);
	//Retorna el numero de caracteres que se escribieron
	return t;
}

void ServicioTicks(uint32_t* ticks){
	//Usando la funcion Hal_GetTick() que retorna la cantidad de ticks del sistema
	//desde que comenzo. Se pasa el resultado por referencia.
	*ticks = HAL_GetTick()/1000;
}

void ServicioInitPWM(){
	//Start PWM
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}

void ServicioPWMDutyCycle(uint16_t pulsos){
	//Duty cycle
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pulsos);
}

void ServicioStopPWM() {
	//Stop PWM
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
}

int Leer(int a,char* b,int t) {
	//Guarda el valor de r0 (parametro a) en la variable r
	register int r asm("r0");
	//Ejecuta codigo ensamblador en C.
	//mov r3, 1 mueve un 1 a r3, que indica el servicio a consumir
	//svc 0 indica que se quiere realizar un interrupcion por software, lo cual es atendida por SVC_Handler
	__asm("mov r3,1;svc 0");
	//Retorna la cantidad de caracteres leidos
	return r;
}

int Escribir(int a,char* b,int t) {
	//Guarda el valor de r0 (parametro a) en la variable r
	register int r asm("r0");
	//Ejecuta codigo ensamblador en C.
	//mov r3, 2 mueve un 2 a r3, que indica el servicio a consumir
	//svc 0 indica que se quiere realizar un interrupcion por software, lo cual es atendida por SVC_Handler
	__asm("mov r3,2;svc 0");
	//Retorna la cantidad de caracteres escritos
	return r;
}

void Ticks(uint32_t* ticks) {
	//Guarda el valor de r0 (parametro a) en la variable r
	register int r asm("r0");
	//Ejecuta codigo ensamblador en C.
	//mov r3, 3 mueve un 3 a r3, que indica el servicio a consumir
	//svc 0 indica que se quiere realizar un interrupcion por software, lo cual es atendida por SVC_Handler
	__asm("mov r3,3;svc 0");
	//En la variable ticks, por referencia, se retorna el valor de los ticks
	*ticks = r;
}

void InitPWM(){
	//Servicio 4 es el de iniciar el PWM
	__asm("mov r3,4;svc 0");
}

void DutyCycle(uint16_t pulsos){
	//Servicio 6 es el de cambiar el ancho del PWM
	if(pulsos > htim1.Init.Period) pulsos = htim1.Init.Period;
	__asm("mov r3,6;svc 0");
}

void StopPWM(){
	//Servicio 5 es el de parar el PWM
	__asm("mov r3,5;svc 0");
}

//Manejador de interrupcion del UART3
void USART3_IRQHandler(void) {
  /* USER CODE BEGIN USART3_IRQn 0 */
  /* USER CODE END USART3_IRQn 0 */
  HAL_UART_IRQHandler(&huart3);
  /* USER CODE BEGIN USART3_IRQn 1 */
  //Incrementando la posicion de escritura del buffer circular
  consola.posFin++;
  //Indicando donde poner el caracter que llego por el puerto serial tras la interrupcion
  HAL_UART_Receive_IT(&huart3,&consola.buffer[consola.posFin%1024],1);
  /* USER CODE END USART3_IRQn 1 */
}

