#include <iostream>

#include "structs.h"
#include "ETs.h"
#include "LEspera.h"

void initializeETs(Data* data, ET* ETsArray) {
	for (int i = 0; i < data->ETs; i++) {
		ETsArray[i].id = i + 1;
		cout << "Qual será o mecânico para a ET " << i + 1 << "? ";
		cin >> ETsArray[i].mecanico;
		ETsArray[i].marca = data->Marca[rand() % data->sizeMarcas];
		ETsArray[i].capacidade = rand() % 6 + 3;
	}
}

void printETs(int ETs, ET* ETsArray) {
	for (int i = 0; i < ETs; i++) {
		cout << "ET: " << ETsArray[i].id << " | Mecânico: " << ETsArray[i].mecanico << " | Capacidade: " << ETsArray[i].capacidade << " | Carros: " << ETsArray[i].lotacao << " | Marca: " << ETsArray[i].marca << " | Total Faturação: " << ETsArray[i].faturacao << endl;
		for (int j = 0; j < ETsArray[i].lotacao; j++) {
			cout << "Carro: ID:  " << ETsArray[i].Reparando[j].id << " | " << ETsArray[i].Reparando[j].marca << "-" << ETsArray[i].Reparando[j].modelo << " | Prioritário: " << ((ETsArray[i].Reparando[j].prioritario) ? "Sim" : "Não") << " | Tempo de reparacao: " << ETsArray[i].Reparando[j].temporeparar << " | Dias na ET: " << ETsArray[i].Reparando[j].tempoet << endl;
		}
		cout << "-------------------------------------" << endl;
	}
}

int totalCars(int ETs, ET* ETsArray) {
	int TotalCars = 0;
	for (int i = 0; i < ETs; i++) {
		TotalCars = TotalCars + ETsArray[i].lotacao;
	}
	return TotalCars;
}

Car* ETsCarsArray(int ETs, int TotalCars, ET* ETsArray) {
	Car* auxx = new Car[TotalCars];

	for (int i = 0; i < ETs; i++) {
		for (int j = 0; j < ETsArray[i].lotacao; j++) {
			auxx[j] = ETsArray[i].Reparando[j];
		}
	}
	return auxx;
}

void repararCarros(int ETs, ET* ETsArray) {
	for (int i = 0; i < ETs; i++) {
		ET currentET = ETsArray[i];
		for (int j = 0; j < currentET.lotacao; j++) {
			Car aux = ETsArray[i].Reparando[j];
			if (rand() % 100 < 15) {
				// Sucesso
				currentET.lotacao--;
				currentET.Reparados[currentET.reparados] = aux;
				currentET.reparados++;
				
			}
			//else if (dia== ETsArray[i].Reparando[j].temporeparar){
			//	// Erro
			//}
		}
	}
}

