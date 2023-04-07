// implement LEspera.h

#include <iostream>

#include "LEspera.h"
#include "structs.h"


using namespace std;

void createLEspera(LEspera & LEsperaC) {
	LEsperaC.inicio = NULL;
}


void addCarToLEspera(LEspera & LEsperaC, LEspera::Item* car) {
	if (LEsperaC.inicio == NULL) {
		LEsperaC.inicio = car;
		car->next = NULL;
	}
	else {
		car->next = LEsperaC.inicio;
		LEsperaC.inicio = car;
	}
}

// size of LEspera

int numElementos(LEspera* LEspera) {
	LEspera* aux = LEspera;
	int numElems = 0;
	while (aux != NULL) {
		numElems++;
		aux = aux->next;
	}
	return numElems;
}

void removeCarFromLEspera(LEspera*& LEsperaC) {
	int numElems = numElementos
}

void printLEspera(LEspera* LEspera) {
	LEspera* aux = LEspera;
	while (aux != NULL) {
		cout << aux->car->id << endl;
		aux = aux->next;
	}
}

void addCarPriority(LEspera*& LEspera, int ID) {
	LEspera* aux = LEspera;
	LEspera* aux2 = NULL;
	while (aux != NULL) {
		if (aux->car->id == ID) {
			if (aux2 == NULL) {
				return;
			}
			else {
				aux2->next = aux->next;
				aux->next = LEspera;
				LEspera = aux;
				return;
			}
		}
		aux2 = aux;
		aux = aux->next;
	}
}