#pragma once

#include "structs.h"

using namespace std;

No* newNo(Car car);

No* insert(No* root, Car car);

void printInOrder(No* root, int lvl);