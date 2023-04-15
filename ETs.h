#pragma once
#include "structs.h"

void initializeETs(Data* data, ET* ETsArray);

void printETs(int ETs, ET* ETsArray);

Car* ETsCarsArray(int ETs, int TotalCars, ET* ETsArray);

int totalCars(int ETs, ET* ETsArray);

//void reparaCarros(int ETs, ET* ETsArray );