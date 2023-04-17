#include <iostream>

#include "structs.h"
#include "ETs.h"
#include "LEspera.h"

string getUnusedMarca(Data* data, string* marcas, int prev) {
	bool aux = false;
	string marca = data->Marca[rand() % data->sizeMarcas];
	for (int i = 0; i < prev; i++) {
		if (marca == marcas[i]) {
			aux = true;
		}
	}
	if (aux) {
		marca = marcas[rand() % data->sizeMarcas];
		return getUnusedMarca(data, marcas, prev);
	}
	else {
		return marca;
	}
}

void initializeETs(Data* data) {
	for (int i = 0; i < data->ETs; i++) {
		data->ETsArray[i].id = i + 1;
		cout << "Qual ser� o mec�nico para a ET " << i + 1 << "? ";
		cin >> data->ETsArray[i].mecanico;
		string marca = getUnusedMarca(data, data->Marca, i);
		data->ETsArray[i].marca = marca;
		data->Marcas[i] = marca;
		data->ETsArray[i].capacidade = rand() % 6 + 3;
		data->ETsArray[i].Reparando = new Car[data->ETsArray[i].capacidade];
	}
}

void printETs(int ETs, ET* ETsArray) {
	for (int i = 0; i < ETs; i++) {
		cout << "ET: " << ETsArray[i].id << " | Mec�nico: " << ETsArray[i].mecanico << " | Capacidade: " << ETsArray[i].capacidade << " | Carros: " << ETsArray[i].lotacao << " | Marca: " << ETsArray[i].marca << " | Total Fatura��o: " << ETsArray[i].faturacao << endl;
		for (int j = 0; j < ETsArray[i].lotacao; j++) {
			cout << "  Carro: ID:  " << ETsArray[i].Reparando[j].id << " | " << ETsArray[i].Reparando[j].marca << "-" << ETsArray[i].Reparando[j].modelo << " | Priorit�rio: " << ((ETsArray[i].Reparando[j].prioritario) ? "Sim" : "N�o") << " | Tempo de reparacao: " << ETsArray[i].Reparando[j].temporeparar << " | Dias na ET: " << ETsArray[i].Reparando[j].tempoet << endl;
		}
		cout << "--------------------------------------------------------------------------" << endl;
	}
}

void addCarToET(Data* data, LEspera& f) {
	string* aux = new string[data->ETs];
	int coutt = 0;
	for (int i = 0; i < data->ETs; i++) {
		if (data->ETsArray[i].lotacao < data->ETsArray[i].capacidade) {
			aux[coutt++] = data->Marcas[i];
		}
	}
	Car car;
	try {
		car = removeFirstPossibleCar(f, aux, data->ETs);
	}
	catch (Car car) {
		return;
	}
	//cout << "Car ID: " << car.id << endl;
	for (int j = 0; j < data->ETs; j++) {
		if (data->ETsArray[j].marca == car.marca) {
			car.idet = j;
			data->ETsArray[j].Reparando[data->ETsArray[j].lotacao++] = car;
			break;
		}	
	}

	delete[] aux;
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

void cloneCarArray(Car* Cars1, Car* FinalCars, int size) {
	for (int i = 0; i < size; i++) {
		FinalCars[i] = Cars1[i];
	}
}

void addReparados(ET* ETsArray, Car car, int x) {
	ETsArray[x].reparados++;
	ETsArray[x].faturacao += 100;
	Car* reparados = new Car[ETsArray[x].reparados+1];
	cloneCarArray(ETsArray[x].Reparados, reparados, ETsArray[x].reparados);
	car.reparado = true;
	reparados[ETsArray[x].reparados] = car;
	ETsArray[x].Reparados = reparados;
}

void repararCarros(int ETs, ET* ETsArray) {
	for (int i = 0; i < ETs; i++) {
		Car* reparando = new Car[ETsArray[i].capacidade];
		int aux = 0;
		int aux2 = ETsArray[i].lotacao;
		for (int j = 0; j < aux2; j++) {
			Car car = ETsArray[i].Reparando[j];
			if ((rand() % 100 <= 15) || car.temporeparar == car.tempoet) {
				addReparados(ETsArray, car, i);
				ETsArray[i].lotacao--;
			}
			else {
				car.tempoet++;
				reparando[aux++] = car;
			}
		}
		delete[] ETsArray[i].Reparando;
		ETsArray[i].Reparando = reparando;
	}
}
