#include <iostream>

#include "structs.h"
#include "ETs.h"
#include "LEspera.h"

void initializeETs(Data* data, ET* ETsArray) {
	for (int i = 0; i < data->ETs; i++) {
		ETsArray[i].id = i + 1;
		cout << "Qual ser� o mec�nico para a ET " << i + 1 << "? ";
		cin >> ETsArray[i].mecanico;
		ETsArray[i].marca = data->Marca[rand() % data->sizeMarcas];
		ETsArray[i].capacidade = rand() % 6 + 3;
	}
}

void printETs(int ETs, ET* ETsArray) {
	for (int i = 0; i < ETs; i++) {
		cout << "ET: " << ETsArray[i].id << " | Mec�nico: " << ETsArray[i].mecanico << " | Capacidade: " << ETsArray[i].capacidade << " | Carros: " << ETsArray[i].lotacao << " | Marca: " << ETsArray[i].marca << " | Total Fatura��o: " << ETsArray[i].faturacao << endl;
		for (int j = 0; j < ETsArray[i].lotacao; j++) {
			cout << "Carro: ID:  " << ETsArray[i].Reparando[j].id << " | " << ETsArray[i].Reparando[j].marca << "-" << ETsArray[i].Reparando[j].modelo << " | Priorit�rio: " << ((ETsArray[i].Reparando[j].prioritario) ? "Sim" : "N�o") << " | Tempo de reparacao: " << ETsArray[i].Reparando[j].temporeparar << " | Dias na ET: " << ETsArray[i].Reparando[j].tempoet << endl;
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

void reparaCarros(int ETs, ET* ETsArray, int dia) {
	for (int i = 0; i < ETs; i++) {
		for (int j = 0; j < ETsArray[i].lotacao; j++) {
			int numerordm = rand() % 100;
			if (numerordm < 15) {
				ETsArray[i].Reparando[j] = ETsArray[i].Reparados[j];
			}
			else if (dia== ETsArray[i].Reparando[j].temporeparar){
				
				cout << "Event did not occur." << endl;
			}
		}
	}
}


/*
void oficinaMenu(int ETs, Data* data, int TotalCars, ET* ETsArray) {
	// Variaveis
	char option = ' ';
	bool sair = false;

	do {
		display(data, ETsArray);


		cout << " (s)eguinte  ***********  (g)est�o  ***********  (0)sair" << endl;
		cout << "Selecione a sua op��o:";
		cin >> option;
		cout << endl << "---------------------------------" << endl;

		switch (option) {
		case 's':
			 initializeETs( data, ETsArray);

			 printETs( ETs, ETsArray);

			 ETsCarsArray( ETs, TotalCars, ETsArray);

			 totalCars( ETs, ETsArray);

			 reparaCarros( ETs, ETsArray);
		
		//CASE G

		case'0':
			sair = true;
			break;
		default:
			cout << "Inseriu uma op��o inv�lida!" << endl;

			break;
		}
	} while (!sair);
}
*/