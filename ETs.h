#pragma once
#include "structs.h"

void initializeETs(Data* data);

void printETs(int ETs, ET* ETsArray);

Car* ETsCarsArray(int ETs, int TotalCars, ET* ETsArray);

int totalCars(int ETs, ET* ETsArray);