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

	// filepaths->pathETs = (args == NULL) ? "savedETs.txt" : argv[1];
	// Get Current ETs ID/Size
	//data->ETs = calculateSizeofFile(filepaths->pathETs);

	//filepaths->pathCars = (args == NULL) ? "savedCars.txt" : argv[2];
	// Get Current Cars ID/Size
	//data->Cars = calculateSizeofFile(filepaths->pathCars);

	data->ETs = rand() % 6 + 3; // Number of ETs is going to have
	cout << "A Oficina tem " << data->ETs << " Estações de Trabalho." << endl;
	data->Marcas = new string[data->ETs];
	data->ETsArray = new ET[data->ETs];

	initializeETs(data);


	// Create LEspera and add 10 cars to it
	LEspera FilaLEspera{};
	createLEspera(FilaLEspera);
	createCarLEspera(data, FilaLEspera, 10);

	printLEspera(FilaLEspera);
	cout << endl;
	printETs(data->ETs, data->ETsArray);
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		addCarToET(data, FilaLEspera);
	}


	printETs(data->ETs, data->ETsArray);


	char letra;
	int opcao;
	while (true){
		cout << "Pressione a letra 's' se quiser simular, ou então a letra 'g' se quiser aceder a gestão :" << endl;
		cin >> letra;
		if (letra == 's') {
			createCarLEspera(data, FilaLEspera, 10);
			repararCarros(data->ETs, data->ETsArray);
			for (int i = 0; i < 10; i++)
			{
				addCarToET(data, FilaLEspera);
			}
			printETs(data->ETs, data->ETsArray);
			//printCars(data, FilaLEspera, data->ETsArray, true);
		}
		else if (letra == 'g') {
			cout << "**** Bem vindo Gestor ****" << endl;
			cout << "1 - Reparação Manual " << endl;
			cout << "2 - Atualizar tempo de reparação" << endl;
			cout << "3 - Adicionar prioridade" << endl;
			cout << "4 - Remover mecanico" << endl;
			cout << "5 - Gravar oficina" << endl;
			cout << "6 - Carregar oficina" << endl;
			cout << "7 - Imprimir oficina" << endl;
			cout << "Escolha uma oppcao: " << endl;

			cin >> opcao;
			switch (opcao) {
			case 1:
				repararManual(data->ETs, data->ETsArray);
				printETs(data->ETs, data->ETsArray);
				break;
			case 2:
				printCars(data, FilaLEspera, data->ETsArray, true);
				Atreparacao(FilaLEspera);
			}
		}
		else
			break;
	}


	printCars(data, FilaLEspera, data->ETsArray, true);

	delete filepaths;
	delete data;
}

