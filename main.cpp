#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <locale>

#include "structs.h"
#include "files.h"
#include "LEspera.h"

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


	bool args = argv[1] && argv[2];	// main.exe savedETs.txt savedCars.txt

	filepaths->pathETs = (args == NULL) ? "savedETs.txt" : argv[1];
	// Get Current ETs ID/Size
	data->ETs = calculateSizeofFile(filepaths->pathETs);
	
	filepaths->pathCars = (args == NULL) ? "savedCars.txt" : argv[2];
	// Get Current Cars ID/Size
	data->Cars = calculateSizeofFile(filepaths->pathCars);

	//internalData->areaArray = getContentFromFiles(gardenFilepaths->pathAreas, internalData->sizeofArea); // Content of file area to array
	//internalData->providerArray = getContentFromFiles(gardenFilepaths->pathProviders, internalData->sizeofProvider); // Content of file provider to array
	//internalData->productnameArray = getContentFromFiles(gardenFilepaths->pathProducts, internalData->sizeofProductname); // Content of file product to array

	data->ETs = rand() % 8 + 3; // Number of ETs is going to have
	cout << "A Oficina tem " << data->ETs << " Estações de Trabalho." << endl;

	ET* ETsArray = new ET[data->ETs];

	LEspera FilaLEspera = new LEspera;

	//Garden* myplantation = new Garden[internalData->numberofGardens];
	//Storage* plantationstorage = new Storage;

	//inicializeGardens(internalData, myplantation);
	//getAreasChoosen(internalData, myplantation);

	//plantationstorage->inStorage = inicializeProducts(internalData);
	//internalData->numberofProductsToCreate = 10;

	//plantationMenu(internalData, myplantation, plantationstorage, gardenFilepaths);

	//delete[] myplantation;
	//delete internalData;
	//delete gardenFilepaths;
	//delete plantationstorage;
}
