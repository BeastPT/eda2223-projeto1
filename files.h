#pragma once

#include "structs.h"
using namespace std;

int calculateSizeofFile(string path);

string* getContentFromFiles(string path, int sizeofFile);

//struct LEspera {
//	Car car;
//	LEspera* seguinte;
//};
//
//LEspera* createLEspera(Car* car);
//
//void addCarToLEspera(LEspera*& LEspera, Car* car);
//
//void removeCarFromLEspera(LEspera** LEspera);
//
//void printLEspera(LEspera* LEspera);
//
//void addCarPriority(LEspera* LEspera, int ID);