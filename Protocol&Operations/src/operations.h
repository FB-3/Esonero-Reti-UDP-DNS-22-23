/*
 ============================================================================
 Name        : operations.h
 Author      : Basile Federico 759524
 Version     : 1.0
 Copyright   : //
 Description : Server operations header
 ============================================================================
 */

#ifndef SRC_OPERATIONS_H_
#define SRC_OPERATIONS_H_

// Prototypes
int sum(int, int);
int subtraction(int, int);
int multiplication(int, int);
double division(int, int);


int sum(int op1, int op2) {

	return op1 + op2;
}

int subtraction(int op1, int op2) {

	return op1 - op2;
}

int multiplication(int op1, int op2) {

	return op1 * op2;
}

double division(int op1, int op2) {

	return (double) op1 / op2;
}


#endif /* SRC_OPERATIONS_H_ */
