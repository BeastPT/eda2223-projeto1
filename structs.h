#pragma once

#include <string>

using namespace std;

struct Filepaths {
	string pathMarcas = "";
	string pathModelos = "";
	string pathETs = "";
	string pathCars = "";
};

struct Car {
	int id = 0;
	string marca = "";
	string modelo = "";
	bool fila = true;
	bool prioritario = false;
	bool reparado = false;
	int idet = 0;
	int temporeparar = 0;
	int tempoet = 0;
};

struct No {
	Car car;
	No* Left;
	No* Right;
};

struct Reparando {
	Car car;
	Reparando* Next;
};

struct ET {
	int id = 0;
	string mecanico = "";
	string marca = "";
	int capacidade = 0;
	int lotacao = 0;
	int faturacao = 0;
	int reparados = 0;
	//Car* Reparando = new Car;
	Reparando* Reparando = NULL;
	//Car* Reparados = new Car;
	No* Reparados = nullptr;
};

struct Data {
	string* Marca = new string;
	string* Modelo = new string;
	int sizeMarcas = 0;
	int sizeModelos = 0;
	int ETs = 0;
	int Cars = 0;
	string* Marcas = new string;
	ET* ETsArray = new ET;
	//string* CarsArray = new string;
};