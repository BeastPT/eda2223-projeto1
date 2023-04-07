#pragma once
#include <string>

using namespace std;

struct Filepaths {
	string pathMarcas;
	string pathModelos;
	string pathETs;
	string pathCars;
};

struct Data {
	int ETs;
	int Cars;
};

struct ET {
	int id;
	string* mecanico;
	string* marca;
	int capacidade;
	int* lotacao;
	int* faturacao;
};