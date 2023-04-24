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

void createCarLEspera(Data* data, LEspera& f, int amount) {
	for (int i = 0; i < amount; i++)
	{
		Car* car = new Car;
		car->id = data->Cars++;
		car->marca = data->Marcas[rand() % data->ETs];
		car->modelo = data->Modelo[rand() % data->sizeModelos];
		car->temporeparar = rand() % 4 + 2;
		car->prioritario = (rand() % 100 < 5) ? true : false;
		addToLEspera(f, car);
	}
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

Car removeFromLEsperaByMarca(LEspera& f, string marca) {
	if (f.primeiro == NULL) {
		throw Car();
	}
	else {
		LEspera::Item* aux = f.primeiro;
		bool found = false;
		while (aux != NULL) { // procura prioritario + marca
			if (aux->car->prioritario && aux->car->marca == marca) {
				found = true;
				break;
			}
			aux = aux->seguinte;
		}
		if (!found) {
			aux = f.primeiro;
			while (aux != NULL) { // procura marca
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
			Car result = *aux->car;
			f.primeiro = aux->seguinte;
			delete aux;
			return result;
			
		}
	}
}

bool existsInArray(string* array, int size, string value) {
	for (int i = 0; i < size; i++) {
		if (array[i] == value) {
			return true;
		}
	}
	return false;
}

Car removeFirstPossibleCar(LEspera& f, string* marcas, int ETs) {
	if (f.primeiro == NULL) {
		throw Car();
	}
	else {
		LEspera::Item* prevaux = nullptr;
		LEspera::Item* aux = f.primeiro;
		bool found = false;
		while (aux != NULL) { // procura carro prioritario
			if (aux->car->prioritario && existsInArray(marcas, ETs, aux->car->marca)) {
				found = true;
				break;
			}
			prevaux = aux;
			aux = aux->seguinte;
		}
		if (!found) {
			prevaux = nullptr;
			aux = f.primeiro;
			while (aux != NULL) { // procura carro
				if (existsInArray(marcas, ETs, aux->car->marca)) {
					found = true;
					break;
				}
				prevaux = aux;
				aux = aux->seguinte;
			}
		}
		if (aux == NULL) {
			throw Car();
		}
		else {
			aux->car->fila = false;
			Car result = *aux->car;
			if (prevaux == nullptr) {
				f.primeiro = aux->seguinte;
			}
			else {
				prevaux->seguinte = aux->seguinte;
			}
			delete aux;
			return result;
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
		return NULL;
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

void deleteLEspera(LEspera& f) {
	if (f.primeiro == NULL) {
		cout << "Lista de espera vazia deleteLEspera" << endl;
	}
	else {
		LEspera::Item* aux = f.primeiro;
		while (aux != NULL) {
			LEspera::Item* temp = aux;
			aux = aux->seguinte;
			delete temp;
		}
		f.primeiro = NULL;
	}
}

void Atreparacao(LEspera& f) {
	string marcaat, modelat;
	int trep;
	cout << "Qual a marca que pretende :" << endl;
	cin >> marcaat;
	cout << "Qual o modelo que pretende :" << endl;
	cin >> modelat;
	cout << "Qual o tempo que pretende para a reparação (2 a 5):" << endl;
	cin >> trep;
	if (f.primeiro == NULL) 
		cout << "Lista de espera vazia" << endl;
	else {
		LEspera::Item* aux = f.primeiro;
		while (aux != NULL) {
			if (aux->car->marca == marcaat && aux->car->modelo == modelat) {
				aux->car->temporeparar = trep;
				aux = aux->seguinte;
			}
			else
				aux = aux->seguinte;
		}
	}
}
