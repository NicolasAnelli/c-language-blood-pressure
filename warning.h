/*
 * warning.h
 *
 *  Created on: Oct 16, 2020
 *      Author: nicolasanelli
 */
#include <stdio.h>
#include "layout.h"

#ifndef WARNING_H_
#define WARNING_H_

char _warning[255];
void setWarning(char* msg) {
	strcpy(_warning, msg);
}
void printWarning() {
	if(strcmp(_warning, "")) {
		line(_warning, 'C');
		strcpy(_warning, "");
	} else {
		emptyLine();
	}
}

#endif /* WARNING_H_ */

















