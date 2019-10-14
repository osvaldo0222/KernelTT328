/*
 * ioc.h
 *
 *  Created on: Oct 12, 2019
 *      Author: osvaldofdez
 */

#ifndef IOC_H_
#define IOC_H_

typedef struct{
	//Identificador
	int id;
	//Archivo de donde se estara haciendo lectura y escritura
	void* harchivo;
	//Buffer circular
	char buffer[1024];
	int posIni;
	int posFin;
}sArchivo;

#endif /* IOC_H_ */

