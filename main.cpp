#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale>

#include "structs.h"
#include "files.h"
#include "LEspera.h"
#include "ETs.h"
#include "management.h"

using namespace std;


int main(int argc, char* argv[]) {

	srand(time(NULL));
	locale::global(locale(""));

	Filepaths* filepaths = new Filepaths;
	Data* data = new Data;

	filepaths->pathMarcas = "marcas.txt";
	filepaths->pathModelos = "modelos.txt";

	data->sizeMarcas = calculateSizeofFile(filepaths->pathMarcas);
	data->sizeModelos = calculateSizeofFile(filepaths->pathModelos);
	data->Marca = getContentFromFiles(filepaths->pathMarcas, data->sizeMarcas);
	data->Modelo = getContentFromFiles(filepaths->pathModelos, data->sizeModelos);

	bool args = argv[1] && argv[2];	// main.exe savedETs.txt savedCars.txt

	//filepaths->pathETs = (args == NULL) ? "savedETs.txt" : argv[1];
	// Get Current ETs ID/Size
	//data->ETs = calculateSizeofFile(filepaths->pathETs);
	
	//filepaths->pathCars = (args == NULL) ? "savedCars.txt" : argv[2];
	// Get Current Cars ID/Size
	//data->Cars = calculateSizeofFile(filepaths->pathCars);

	data->ETs = 2; //rand() % 8 + 3; // Number of ETs is going to have
	cout << "A Oficina tem " << data->ETs << " Estações de Trabalho." << endl;

	ET* ETsArray = new ET[data->ETs];

	initializeETs(data, ETsArray);


	// Create LEspera and add 10 cars to it
	LEspera FilaLEspera{};
	createLEspera(FilaLEspera);
	for (int i = 0; i < 10; i++)
	{
		Car* car = new Car;
		car->id = i + 1;
		car->marca = data->Marca[rand() % data->sizeMarcas];
		car->modelo = data->Modelo[rand() % data->sizeModelos];
		car->temporeparar = rand() % 5 + 2;
		car->prioritario = (rand() % 100 < 50) ? true : false; // 100 < 5
		addToLEspera(FilaLEspera, car);
		data->Cars++;
	}
	printLEspera(FilaLEspera);
	cout << endl;
	cout << endl;
	cout << endl;
	// End of Create LEspera and add 10 cars to it
	printCars(data, FilaLEspera, ETsArray, true); // print all cars alpha

	delete[] ETsArray;
	delete filepaths;
	delete data;
}
