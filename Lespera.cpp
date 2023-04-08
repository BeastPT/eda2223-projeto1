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

int sizeLEspera(LEspera& f) {
	LEspera::Item* aux = f.primeiro;
	int comp = 0;
	while (aux != 0) {
		comp++;
		aux = aux->seguinte;
	}
	return comp;
}

Car removeFromLEspera(LEspera& f) {
	if (f.primeiro == NULL) {
		throw Car();
	}
	else {
		LEspera::Item* aux = f.primeiro;
		f.primeiro = f.primeiro->seguinte;
		aux->car->fila = false;
		return *aux->car;
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

void printLEsperaByAlphaOrder(LEspera& f) {
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

		//ordena alpha
		for (int i = 0; i < size - 1; i++) {
			for (int j = 0; j < size - i - 1; j++) {
				string marca1 = vec[j]->marca;
				string marca2 = vec[j + 1]->marca;
				string modelo1 = vec[j]->modelo;
				string modelo2 = vec[j + 1]->modelo;
				int k = 0;
				int l = 0;
				while (k < marca1.length() && k < marca2.length() && toLower(marca1[k]) == toLower(marca2[k])) {
					k++;
				}
				if (k < marca1.length() && k < marca2.length() && toLower(marca1[k]) > toLower(marca2[k])) {
					Car* temp = vec[j];
					vec[j] = vec[j + 1];
					vec[j + 1] = temp;
				}
				if (marca1 == marca2) {
					while (l < modelo1.length() && l < modelo2.length() && toLower(modelo1[l]) == toLower(modelo2[l])) {
						l++;
					}
					if (l < modelo1.length() && l < modelo2.length() && toLower(modelo1[l]) > toLower(modelo2[l])) {
						Car* temp = vec[j];
						vec[j] = vec[j + 1];
						vec[j + 1] = temp;
					}
				}
			}
		}

		for (int i = 0; i < size; i++) {
			cout << "-------------------------------------" << endl;
			cout << "Carro: ID: " << vec[i]->id << " | " << vec[i]->marca << "-" << vec[i]->modelo << " | Prioritario: " << ((vec[i]->prioritario) ? "Sim" : "Não") << " | Tempo de reparacao: " << vec[i]->temporeparar << " | Tempo de espera: " << vec[i]->tempoet << endl;
		}

		delete[] vec;

	}
}

void printLEsperaByRepairTime(LEspera& f) {
	if (f.primeiro == NULL) {
		cout << "Lista de espera vazia" << endl;
	}
	else {
		int size = sizeLEspera(f);
		Car** vec = new Car * [size];
		LEspera::Item* atual = f.primeiro;
		for (int i = 0; i < size; i++) {
			vec[i] = atual->car;
			atual = atual->seguinte;
		}

		//ordena repairtime
		for (int i = 0; i < size - 1; i++) {
			for (int j = 0; j < size - i - 1; j++) {
				int repairTime1 = vec[j]->temporeparar;
				int repairTime2 = vec[j + 1]->temporeparar;
				if (repairTime1 > repairTime2) {
					Car* temp = vec[j];
					vec[j] = vec[j + 1];
					vec[j + 1] = temp;
				}
			}
		}

		for (int i = 0; i < size; i++) {
			cout << "-------------------------------------" << endl;
			cout << "Carro: ID: " << vec[i]->id << " | " << vec[i]->marca << "-" << vec[i]->modelo << " | Prioritario: " << ((vec[i]->prioritario) ? "Sim" : "Não") << " | Tempo de reparacao: " << vec[i]->temporeparar << " | Tempo de espera: " << vec[i]->tempoet << endl;
		}

		delete[] vec;

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

void addCarPriority(LEspera& f, int repairTime, string Marca, string Modelo) {
	if (f.primeiro == NULL) {
		throw Car();
	}
	else {
		LEspera::Item* aux = f.primeiro;
		while (aux != NULL) {
			if (aux->car->marca == Marca && aux->car->modelo == Modelo) {
				aux->car->temporeparar = repairTime;
			}
			aux = aux->seguinte;
		}
	}
}