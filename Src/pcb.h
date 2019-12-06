/*
 * pcb.h
 *
 *  Created on: Nov 22, 2019
 *      Author: osvaldofdez
 */

#ifndef PCB_H_
#define PCB_H_

#define N 2

typedef struct {
	int id;
	int core_registers[8]; //r0-r3,r12,lr,pc,xpsr
	int user_registers[8]; //r4-r11
}Procces;

typedef uint32_t sem_t;
int* stack_pointer;
int fork();
void sem_wait(sem_t* semaphore);
void sem_post(sem_t* semaphore);
void sem_init(sem_t* semaphore, uint32_t value);

#endif /* PCB_H_ */
