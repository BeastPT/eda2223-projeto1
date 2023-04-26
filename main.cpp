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

// app.exe savedETs.txt savedCars.txt
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

	if (argv[1] && argv[2]) {
		filepaths->pathETs = argv[1];
		filepaths->pathCars = argv[2];
		cout << argv[1] << "  " << argv[2] << endl;
	}
	else {
		filepaths->pathETs = "savedETs.txt";
		filepaths->pathCars = "savedCars.txt";
	}

	data->ETs = rand() % 6 + 3; // Number of ETs is going to have
	cout << "A Oficina tem " << data->ETs << " Estações de Trabalho." << endl;
	data->Marcas = new string[data->ETs];
	data->ETsArray = new ET[data->ETs];

	initializeETs(data);


	// Create LEspera and add 10 cars to it
	LEspera FilaLEspera{};
	createLEspera(FilaLEspera);
	createCarLEspera(data, FilaLEspera, 10);

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
		if (letra == 's' || letra == 'S') {
			createCarLEspera(data, FilaLEspera, 10);
			repararCarros(data->ETs, data->ETsArray);
			for (int i = 0; i < 8; i++)
			{
				addCarToET(data, FilaLEspera);
			}
			printLEspera(FilaLEspera);
			printETs(data->ETs, data->ETsArray);
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
				Atreparacao(FilaLEspera);
				break;
			case 3:
				int id;
				cout << "Introduza o ID do carro que quer adicionar prioridade: " << endl;
				cin >> id;
				addCarPriority(FilaLEspera, id);
				break;
			case 4:
				removerMecanico(data->ETs, data->ETsArray, FilaLEspera, data);
				printETs(data->ETs, data->ETsArray);
				break;
			case 5:
				saveCars(FilaLEspera, data, filepaths);
				saveETs(data, filepaths);
				cout << "Oficina guardada com sucesso!" << endl;
				break;
			case 6:
				delete[] data->Marcas;
				delete[] data->ETsArray;
				deleteLEspera(FilaLEspera);
				loadETs(data, filepaths);
				loadCars(FilaLEspera, data, filepaths);
				cout << "Oficina carregada com sucesso!" << endl;
				break;
			case 7:
				cout << "**** Oficina ****" << endl;
				cout << "1. Mostrar por ordem Alfabética" << endl;
				cout << "2. Mostrar por Tempo de Reparação" << endl;
				int opc;
				cin >> opc;
				if (opc == 1)
					printCars(data, FilaLEspera, data->ETsArray, true);
				else
					printCars(data, FilaLEspera, data->ETsArray, false);
				break;
			default:
				cout << "Opção inexistente" << endl;
				break;
			}
		}
		else
			cout << "Opção inexistente" << endl;
	}

	delete filepaths;
	delete data;
}

