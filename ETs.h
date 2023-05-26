#pragma once
#include "structs.h"
#include "LEspera.h"

void initializeETs(Data* data);

void printETs(int ETs, ET* ETsArray);

Car* ETsCarsArray(int ETs, int TotalCars, ET* ETsArray);

void addCarToET(Data* data, LEspera& f);

int totalCars(int ETs, ET* ETsArray);

void repararCarros(int ETs, ET* ETsArray);

void addReparados(ET* ETsArray, Car car, int x);

void repararManual(int ETs, ET* ETsArray);

void removerMecanico(int ETs, ET* ETsArray, LEspera& f, Data* data);

void AddET(Data* data);
