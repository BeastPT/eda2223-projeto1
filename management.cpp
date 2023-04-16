#include <iostream>

#include "LEspera.h"
#include "structs.h"
#include "ETs.h"
#include "management.h"

using namespace std;

void printCars(Data* data, LEspera& f, ET* ETsArray, bool alpha) {
	// put both arrays in one
	Car** LEsperaArray = LEsperaToArray(f);
	int LESize = sizeof(LEsperaArray);

	int ETSize = data->ETs;
	int totalCarsETs = totalCars(ETSize, ETsArray);

	Car* ETsCarArray = ETsCarsArray(ETSize, totalCarsETs, ETsArray);

	int TotalCars = LESize + totalCarsETs;
	Car* Cars= new Car[TotalCars];

	for (int i = 0; i < LESize; i++) {
		Cars[i] = *LEsperaArray[i];
	}

	for (int i = 0; i < totalCarsETs; i++) {
		Cars[i + LESize] = ETsCarArray[i];
	}

	if (alpha) { // Sort by Alpha
		for (int i = 0; i < TotalCars; i++) {
			for (int j = 0; j < TotalCars - 1; j++) {
				string marca1 = Cars[j].marca;
				string marca2 = Cars[j + 1].marca;
				int k = 0;
				while (k < marca1.length() && k < marca2.length() && toLower(marca1[k]) == toLower(marca2[k])) {
					k++;
				}
				if (k < marca1.length() && k < marca2.length() && toLower(marca1[k]) > toLower(marca2[k])) {
					Car temp = Cars[j];
					Cars[j] = Cars[j + 1];
					Cars[j + 1] = temp;
				}
			}
		}
	}
	else { // Sort by Repair Time
		for (int i = 0; i < TotalCars; i++) {
			for (int j = 0; j < TotalCars - 1; j++) {
				if (Cars[j].temporeparar > Cars[j + 1].temporeparar) {
					Car temp = Cars[j];
					Cars[j] = Cars[j + 1];
					Cars[j + 1] = temp;
				}
			}
		}
	}

	for (int i = 0; i < TotalCars; i++) {
		cout << "Carro: ID:  " << Cars[i].id << " | " << Cars[i].marca << "-" << Cars[i].modelo << " | Prioritário: " << ((Cars[i].prioritario) ? "Sim" : "Não") << " | Tempo de reparacao: " << Cars[i].temporeparar << " | Dias na ET: " << Cars[i].tempoet << endl;
	}

	delete[] Cars;
	delete[] ETsCarArray;
	delete[] LEsperaArray;
}

/*
void managementMenu(Data* data, LEspera& f, ET* ETsArray) {
	// Variaveis
	bool sair = false;
	char opcoes = ' ';

	do {
		cout << " " << endl;
		cout << "*****" << " Bem Vindo Gestor " << "*****" << endl;
		cout << "(1).Reparação Manual" << endl;
		cout << "(2).Atualizar tempo de reparação" << endl;
		cout << "(3).Adicionar Prioridade" << endl;
		cout << "(4).Remover Mecânico" << endl;
		cout << "(5).Gravar Oficina" << endl;
		cout << "(6)" << endl;
		cout << "(7).Carregar Oficina" << endl;
		cout << "(8).Imprimir Oficina" << endl;
		cout << "Selecione a sua opcão: ";
		cin >> opcoes;

		cout << " " << endl;
		switch (opcoes) {
			// WRITE 
		case '0':
			cout << "Selecionou a opcao sair!" << endl;
			sair = true;
			break;
		default:
			cout << "Selecione uma opção válida!" << endl;
		}
	} while (!sair);
	cin.ignore();
}
*/