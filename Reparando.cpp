#include <iostream>

#include "structs.h"
#include "ETs.h"
#include "Reparando.h"

using namespace std;

Reparando* newReparando(Car car) {
	Reparando* rep = new Reparando;
	rep->car = car;
	rep->Next = NULL;
	return rep;
}

//string toLowerCase(string str) {
//	string result;
//	for (char c : str) {
//		result += tolower(c);
//	}
//	return result;
//}

Reparando* insertReparando(Reparando* reparando, Car car) {
	if (reparando == NULL) {
		return newReparando(car);
	}
	else {
		Reparando* aux = reparando;
		Reparando* newR = newReparando(car);
		while (aux->Next != NULL) {
			aux = aux->Next;
		}
		aux->Next = newR;
	}
	return reparando;
}


Reparando* removeReparando(Reparando* reparando, int id) {
	if (reparando == NULL) {
		return NULL;
	}
	Reparando* aux = reparando;
	Reparando* prev = NULL;
	while (aux != NULL && aux->car.id != id) {
		prev = aux;
		aux = aux->Next;
	}

	if (aux != NULL) {
		if (prev == NULL) {
			reparando = aux->Next;
		}
		else {
			prev->Next = aux->Next;
		}
		delete aux;
		return reparando;
	}
	else {
		return reparando;
	}
		
}

Car getCar(Reparando* reparando, string modelo){
	Reparando* aux = reparando;
	while (aux != NULL && aux->car.modelo != modelo) {
		aux = aux->Next;
	}
	if (aux == NULL)
		throw;
	else
		return aux->car;
}

Car* carArray(Reparando* reparando, int size) {
	Car* cars = new Car[size];
	int i = 0;
	Reparando* aux = reparando;
	while (i < size) {
		cars[i] = aux->car;
		aux = aux->Next;
		i++;
	}
	return cars;
}

void printReparando(Reparando* reparando) {
	Reparando* aux = reparando;
	while (aux != NULL) {
		cout << "  Carro: ID:  " << aux->car.id << " | " << aux->car.marca << "-" << aux->car.modelo << " | Prioritário: " << ((aux->car.prioritario) ? "Sim" : "Não") << " | Tempo de reparacao: " << aux->car.temporeparar << " | Dias na ET: " << aux->car.tempoet << endl;
		aux = aux->Next;
	}
}

void testReparando(Reparando* reparando) {
	Reparando* aux = reparando;
	while (aux != NULL) {
		cout << aux->car.modelo << endl;
		aux = aux->Next;
	}
}

//void printInOrder(No* root, int lvl) {
//	if (root == nullptr) {
//		cout << endl;
//		return;
//	}
//	printInOrder(root->Left, lvl + 1);
//	for (int i = 1; i < lvl; i++)
//	{
//		cout << "\t";
//	}
//	cout << root->car.modelo << endl;
//	printInOrder(root->Right, lvl + 1);
//}