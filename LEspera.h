#pragma once

// make a FIFO queue for struct Car

#include <iostream>

#include "structs.h"

using namespace std;

// Create FIFO for a list of Cars waiting to be moved to a ET

struct LEspera {
	struct Item {
		Car* car;
		Item* seguinte;
	};
	Item* primeiro;
};
char toLower(char c);

void createLEspera(LEspera& f);

void createCarLEspera(Data* data, LEspera& f, int amount);

void addToLEspera(LEspera& f, Car* car);

int sizeLEspera(LEspera& f);

Car removeFromLEsperaByMarca(LEspera& f, string marca);

Car removeFirstPossibleCar(LEspera& f, string* marcas, int ETs);

Car firstFromLEspera(LEspera& f);

bool isEmptyLEspera(LEspera& f);

void printLEspera(LEspera& f);

Car** LEsperaToArray(LEspera& f);

void addCarPriority(LEspera& f, int ID);

void Atreparacao(LEspera& f);