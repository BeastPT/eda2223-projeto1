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

int sizeLEspera(LEspera& f) {
	LEspera::Item* aux = f.primeiro;
	int comp = 0;
	while (aux != 0) {
		comp++;
		aux = aux->seguinte;
	}
	return comp;
}

Car removeFromLEspera(LEspera& f, string marca) {
	if (f.primeiro == NULL) {
		throw Car();
	}
	else {
		LEspera::Item* aux = f.primeiro;
		bool found = false;
		while (aux != NULL) {
			if (aux->car->prioritario && aux->car->marca == marca) {
				found = true;
				break;
			}
			aux = aux->seguinte;
		}
		if (!found) {
			aux = f.primeiro;
			while (aux != NULL) {
				if (aux->car->marca == marca) {
					found = true;
					break;
				}
				aux = aux->seguinte;
			}
		}
		if (aux == NULL) {
			cout << "Carro not found" << endl;
			throw NULL;
		}
		else {
			aux->car->fila = false;
			return *aux->car;
			delete aux;
		}
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
			cout << "-------------------------------------" << endl;
			cout << "Carro: ID: " << aux->car->id << " | " << aux->car->marca << "-" << aux->car->modelo << " | Prioritario: " << ((aux->car->prioritario) ? "Sim" : "Não") << " | Tempo de reparacao: " << aux->car->temporeparar << " | Tempo de espera: " << aux->car->tempoet << endl;
			aux = aux->seguinte;
		}
	}
}

char toLower(char c) {
	if (c >= 'A' && c <= 'Z') {
		return c - ('A' - 'a');
	}
	else {
		return c;
	}
}

Car** LEsperaToArray(LEspera& f) {
	if (f.primeiro == NULL) {
		cout << "Lista de espera vazia" << endl;
	}
	else {
		int size = sizeLEspera(f);
		Car** vec = new Car* [size];
		LEspera::Item* atual = f.primeiro;
		for (int i = 0; i < size; i++) {
			vec[i] = atual->car;
			atual = atual->seguinte;
		}

		return vec;
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