/*
 * planificador.c
 *
 *  Created on: Dec 4, 2019
 *      Author: osvaldofdez
 */

#include "main.h"
#include "pcb.h"

Procces proccess[N];
int current_proccess = 0;
int users_proccess = 0;
int counter = 0;
sem_t *aux;
int* Parametros;

int fork(){
	asm("MOV r3, #1;SVC 1;");
	return proccess[current_proccess].id;
}

void sem_init(sem_t* semaphore, uint32_t value){
	asm("MOV r3, #2;SVC 1;");
}

void sem_wait(sem_t* semaphore) {
	while(*semaphore <= 0) {
		continue;
	}
	asm("MOV r3, #3;SVC 1;");
}

void sem_post(sem_t* semaphore) {
	asm("MOV r3, #4;SVC 1;");
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void) {
  /* USER CODE BEGIN SVCall_IRQn 0 */
	register int p1 asm("r0");
	register int p2 asm("r1");
	register int p3 asm("r2");
	register int p4 asm("r3");

	switch(p4) {
		case 1:
			users_proccess++;
			proccess[users_proccess].id = users_proccess;
			__asm("TST lr, #4");
			__asm("MRS r0, MSP;");
			stack_pointer = (int*)p1;
			stack_pointer += 6;
			for(int i = 0;i < 8;i++) {
				proccess[users_proccess].core_registers[i] = stack_pointer[i];
			}
			__asm("MOV %0, r4" : "=r" (proccess[users_proccess].user_registers[0]));
			__asm("MOV %0, r5" : "=r" (proccess[users_proccess].user_registers[1]));
			__asm("MOV %0, r6" : "=r" (proccess[users_proccess].user_registers[2]));
			__asm("MOV %0, r7" : "=r" (proccess[users_proccess].user_registers[3]));
			__asm("MOV %0, r8" : "=r" (proccess[users_proccess].user_registers[4]));
			__asm("MOV %0, r9" : "=r" (proccess[users_proccess].user_registers[5]));
			__asm("MOV %0, r10" : "=r" (proccess[users_proccess].user_registers[6]));
			__asm("MOV %0, r11" : "=r" (proccess[users_proccess].user_registers[7]));
			break;
		case 2:
			users_proccess++;
			aux = (sem_t*)p1;
			*aux = p2;
			users_proccess--;
			break;
		case 3:
			users_proccess++;
			aux = (sem_t*)p1;
			*aux = *aux - 1;
			users_proccess--;
			break;
		case 4:
			users_proccess++;
			aux = (sem_t*)p1;
			*aux = *aux + 1;
			users_proccess--;
			break;
		default:
			__asm("TST lr, #4");
			__asm("MRS r0, MSP;");
			/*Parametros = (int*)p1;
			p1 = Parametros[4];
			LlamadaSistema(p1, p2, p3, p4);
			Parametros[4]=p1;*/
			ServicioEscribir(p1, p2, p3);
			break;
	}
  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void) {
  /* USER CODE BEGIN SysTick_IRQn 0 */
	counter++;
	if(counter >= 10 && users_proccess > 0) {
		counter = 0;
		register int p1 asm("r0");
		__asm("TST lr, #4");
		__asm("MRS r0, MSP;");
		stack_pointer = (int*)p1;
		stack_pointer += 4;
		for(int i = 0;i < 8;i++) {
			proccess[current_proccess].core_registers[i] = stack_pointer[i];
		}
		__asm("MOV %0, r4" : "=r" (proccess[current_proccess].user_registers[0]));
		__asm("MOV %0, r5" : "=r" (proccess[current_proccess].user_registers[1]));
		__asm("MOV %0, r6" : "=r" (proccess[current_proccess].user_registers[2]));
		__asm("MOV %0, r7" : "=r" (proccess[current_proccess].user_registers[3]));
		__asm("MOV %0, r8" : "=r" (proccess[current_proccess].user_registers[4]));
		__asm("MOV %0, r9" : "=r" (proccess[current_proccess].user_registers[5]));
		__asm("MOV %0, r10" : "=r" (proccess[current_proccess].user_registers[6]));
		__asm("MOV %0, r11" : "=r" (proccess[current_proccess].user_registers[7]));

		current_proccess = (current_proccess == 0)?1:0;

		for (int i = 0;i < 8;i++) {
			stack_pointer[i] = proccess[current_proccess].core_registers[i];
		}
		__asm("MOV r4, %0" :: "r" (proccess[current_proccess].user_registers[0]));
		__asm("MOV r5, %0" :: "r" (proccess[current_proccess].user_registers[1]));
		__asm("MOV r6, %0" :: "r" (proccess[current_proccess].user_registers[2]));
		__asm("MOV r8, %0" :: "r" (proccess[current_proccess].user_registers[4]));
		__asm("MOV r9, %0" :: "r" (proccess[current_proccess].user_registers[5]));
		__asm("MOV r10, %0" :: "r" (proccess[current_proccess].user_registers[6]));
		__asm("MOV r11, %0" :: "r" (proccess[current_proccess].user_registers[7]));
	}
  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}
