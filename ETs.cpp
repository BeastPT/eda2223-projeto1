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
		ETsArray[i].capacidade = rand() % 5 + 2;
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

void printETsByAlphaOrder(int ETs, ET* ETsArray) {
	ET* aux = ETsArray;
	for (int i = 0; i < ETs - 1; i++) {
		for (int j = 0; j < ETs - i - 1; j++) {
			string marca1 = aux[j].marca;
			string marca2 = aux[j + 1].marca;
			int k = 0;
			while (k < marca1.length() && k < marca2.length() && toLower(marca1[k]) == toLower(marca2[k])) {
				k++;
			}
			if (k < marca1.length() && k < marca2.length() && toLower(marca1[k]) > toLower(marca2[k])) {
				ET temp = aux[j];
				aux[j] = aux[j + 1];
				aux[j + 1] = temp;
			}
		}
	}
	printETs(ETs, aux);
	delete[] aux;
}