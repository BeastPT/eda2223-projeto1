#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <locale>

#include "structs.h"
#include "files.h"

using namespace std;


int main(int argc, char* argv[]) {

	srand(time(NULL));
	locale::global(locale(""));

	Filepaths* filepaths = new Filepaths;
	Data* data = new Data;

	filepaths->pathMarcas = "marcas.txt";
	filepaths->pathModelos = "modelos.txt";

	bool args = argv[1] && argv[2];	// main.exe savedETs.txt savedCars.txt

	filepaths->pathETs = (args == NULL) ? "savedETs.txt" : argv[1];
	data->ETs = calculateSizeofFile(filepaths->pathETs);
	
	filepaths->pathCars = (args == NULL) ? "savedCars.txt" : argv[2];
	data->Cars = calculateSizeofFile(filepaths->pathCars);

	//internalData->sizeofArea = calculateSizeofFile(gardenFilepaths->pathAreas);  // Size of file area
	//internalData->sizeofProvider = calculateSizeofFile(gardenFilepaths->pathProviders);  // Size of file providers
	//internalData->sizeofProductname = calculateSizeofFile(gardenFilepaths->pathProducts);  // Size of file name

	//internalData->areaArray = getContentFromFiles(gardenFilepaths->pathAreas, internalData->sizeofArea); // Content of file area to array
	//internalData->providerArray = getContentFromFiles(gardenFilepaths->pathProviders, internalData->sizeofProvider); // Content of file provider to array
	//internalData->productnameArray = getContentFromFiles(gardenFilepaths->pathProducts, internalData->sizeofProductname); // Content of file product to array

	//internalData->numberofGardens = rand() % 6 + 5; // Number of Gardens the plantation is going to have
	//cout << "A plantação tem " << internalData->numberofGardens << " hortas." << endl;
	//internalData->numberofProductsToCreate = 15;

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
