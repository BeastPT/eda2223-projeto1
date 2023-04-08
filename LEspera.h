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

void createLEspera(LEspera& f);

void addToLEspera(LEspera& f, Car* car);

int sizeLEspera(LEspera& f);

Car removeFromLEspera(LEspera& f);

bool isEmptyLEspera(LEspera& f);

void printLEspera(LEspera& f);

void printLEsperaByAlphaOrder(LEspera& f);

void printLEsperaByRepairTime(LEspera& f);

void addCarPriority(LEspera& f, int ID);