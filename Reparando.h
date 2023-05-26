#pragma once

#include "structs.h"

using namespace std;

Reparando* newReparando(Car car);

Reparando* insertReparando(Reparando* reparando, Car car);

Reparando* removeReparando(Reparando* reparando, int id);

Car getCar(Reparando* reparando, string modelo);

Car* carArray(Reparando* reparando, int size);

//void printReparando(Reparando* reparando);
void printReparando(Reparando* reparando);

void testReparando(Reparando* reparando);