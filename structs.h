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
	string* Marca = new string;
	string* Modelo = new string;
	int sizeMarcas;
	int sizeModelos;

	int ETs = 0;
	int Cars = 0;

	ET* ETsArray = new ET;
	string* CarsArray = new string;
};

struct ET {
	int id;
	string mecanico;
	string marca;
	int capacidade;
	int lotacao;
	int faturacao;
	Car* Reparando = new Car;
	Car* Reparados = new Car;
};

struct Car {
	int id;
	string marca;
	string modelo;
	bool prioritario = false;
	int tempo = 1;
};