// implement LEspera.h

#include <iostream>

#include "LEspera.h"
#include "structs.h"

using namespace std;

void createLEspera(LEspera& f) {
	f.primeiro = NULL;
}

bool isEmptyLEspera(LEspera& f) {
	return f.primeiro == NULL;
}

void addToLEspera(LEspera& f, Car* car) {
	LEspera::Item* novo = new LEspera::Item;
	novo->car = car;
	novo->seguinte = NULL;
	if (f.primeiro == NULL) {
		f.primeiro = novo;
	}
	else {
		LEspera::Item* aux = f.primeiro;
		while (aux->seguinte != NULL) {
			aux = aux->seguinte;
		}
		aux->seguinte = novo;
	}
}

void removeFromLEspera(LEspera& f) {
	if (f.primeiro == NULL) {
		throw Car();
	}
	else {
		LEspera::Item* aux = f.primeiro;
		f.primeiro = f.primeiro->seguinte;
		delete aux;
	}
}

Car firstFromLEspera(LEspera& f) {
	if (f.primeiro == NULL) {
		throw Car();
	}
	else {
		return *f.primeiro->car;
	}
}

void printLEspera(LEspera& f) {
	if (f.primeiro == NULL) {
		cout << "Lista de espera vazia" << endl;
	}
	else {
		LEspera::Item* aux = f.primeiro;
		while (aux != NULL) {
			cout << "ID: " << aux->car->id << endl;
			cout << "Marca: " << aux->car->marca << endl;
			cout << "Modelo: " << aux->car->modelo << endl;
			cout << "Fila: " << aux->car->fila << endl;
			cout << "Prioritario: " << aux->car->prioritario << endl;
			cout << "Reparado: " << aux->car->reparado << endl;
			cout << "IDET: " << aux->car->idet << endl;
			cout << "Tempo de reparacao: " << aux->car->temporeparar << endl;
			cout << "Tempo de espera: " << aux->car->tempoet << endl;
			aux = aux->seguinte;
		}
	}
}

void addCarPriority(LEspera& f, int ID) {
	if (f.primeiro == NULL) {
		throw Car();
	}
	else {
		LEspera::Item* aux = f.primeiro;
		while (aux != NULL) {
			if (aux->car->id == ID) {
				aux->car->prioritario = true;
			}
			aux = aux->seguinte;
		}
	}
}