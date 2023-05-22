#pragma once
#include "structs.h"
#include "structs.h"

struct No {
	Car car;
	No* Left;
	No* Right;
};

No* newNo(Car car);

No* insert(No* root, Car car);

void printInOrder(No* root, int lvl);