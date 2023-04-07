#pragma once

// make a FIFO queue for struct Car

#include <iostream>

#include "structs.h"

using namespace std;

struct LEspera {
	struct Item { 
		Car* car;
		Item* next;
	};
	Item* inicio;
};

void addCarToLEspera(LEspera*& LEspera, Car* car);

void removeCarFromLEspera(LEspera*& LEspera, Car* car);

void printLEspera(LEspera* LEspera);

void addCarPriority(LEspera*& LEspera, int ID);