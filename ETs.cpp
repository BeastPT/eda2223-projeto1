#include <iostream>

#include "structs.h"
#include "ETs.h"
#include "Reparados.h"
#include "Reparando.h"
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
		//data->ETsArray[i].Reparando = new Car[data->ETsArray[i].capacidade];
	}
}

void printETs(int ETs, ET* ETsArray) {
	for (int i = 0; i < ETs; i++) {
		cout << "ET: " << ETsArray[i].id << " | Mec�nico: " << ETsArray[i].mecanico << " | Capacidade: " << ETsArray[i].capacidade << " | Carros: " << ETsArray[i].lotacao << " | Marca: " << ETsArray[i].marca << " | Total Fatura��o: " << ETsArray[i].faturacao << endl;
		printReparando(ETsArray[i].Reparando);
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
	for (int j = 0; j < data->ETs; j++) {
		if (data->ETsArray[j].marca == car.marca) {
			car.idet = j;
			data->ETsArray[j].lotacao++;
			//data->ETsArray[j].Reparando[data->ETsArray[j].lotacao++] = car;
			data->ETsArray[j].Reparando = insertReparando(data->ETsArray[j].Reparando, car);
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
	int aux = 0;
	for (int i = 0; i < ETs; i++) {
		/*for (int j = 0; j < ETsArray[i].lotacao; j++) {
			auxx[aux++] = ETsArray[i].Reparando[j];
		}*/
		Car* carsEt = carArray(ETsArray[i].Reparando, ETsArray[i].lotacao);
		for (int j = 0; j < ETsArray[i].lotacao; j++) {
			auxx[aux++] = carsEt[j];
		}
	}
	return auxx;
}

//void cloneCarArray(Car* Cars1, Car* FinalCars, int size) {
//	for (int i = 0; i < size; i++) {
//		FinalCars[i] = Cars1[i];
//	}
//	delete Cars1;
//}

void addReparados(ET* ETsArray, Car car, int x) {
	ETsArray[x].reparados++;
	ETsArray[x].faturacao += 100;
	//Car* reparados = new Car[ETsArray[x].reparados + 1];
	//cloneCarArray(ETsArray[x].Reparados, reparados, ETsArray[x].reparados);
	car.reparado = true;
	ETsArray[x].Reparados = insert(ETsArray[x].Reparados, car);
	//reparados[ETsArray[x].reparados - 1] = car;
	//ETsArray[x].Reparados = reparados;
}

void repararCarros(int ETs, ET* ETsArray) {
	for (int i = 0; i < ETs; i++) {
		//Car* reparando = new Car[ETsArray[i].capacidade];
		if (ETsArray[i].lotacao == 0)
			continue;
		else {
			int aux = 0;
			int* ids = new int[ETsArray[i].lotacao];
			Reparando* auxx = ETsArray[i].Reparando;
			while (auxx->Next != NULL) {
				Car car = auxx->car;
				if ((rand() % 100 <= 15) || car.temporeparar <= car.tempoet) {
					addReparados(ETsArray, car, i);
					ids[aux++] = car.id;
					ETsArray[i].lotacao--;
				}
				else {
					car.tempoet++;
				}
				auxx = auxx->Next;
			}

			for (int j = 0; j < aux; j++) {
				ETsArray[i].Reparando = removeReparando(ETsArray[i].Reparando, ids[j]);
			}
			delete ids;
		} 
		if (ETsArray[i].reparados > 0) {
			cout << "Carros Reparados na ET " << ETsArray[i].id << ": " << ETsArray[i].reparados << endl;
			printInOrder(ETsArray[i].Reparados, 1);
		}
	}
}

void repararManual(int ETs, ET* ETsArray) {
	string marcarm, modelorm;
	cout << "Qual a marca do carro que quer reparar" << endl;
	cin >> marcarm;
	cout << "Qual o modelo do carro que quer reparar" << endl;
	cin >> modelorm;
	int aux = -1;
	for (int i = 0; i < ETs; i++) {
		if (ETsArray[i].marca == marcarm) {
			aux = i;
			break;
		}
	}
	if (aux == -1) {
		cout << "N�o existe nenhuma ET com essa marca" << endl;
		return;
	}
	/*for (int j = 0; j < ETsArray[aux].lotacao; j++) {
		if (ETsArray[aux].Reparando[j].modelo == modelorm) {
			aux2 = j;
			break;
		}
	}*/
	Car car;
	try {
		car = getCar(ETsArray[aux].Reparando, modelorm);
	}
	catch (Car car) {
		cout << "Essa ET n�o tem nenhum carro esse modelo" << endl;
		return;
	}
	addReparados(ETsArray, car, aux);
	ETsArray[aux].Reparando = removeReparando(ETsArray[aux].Reparando, car.id);
	ETsArray[aux].lotacao--;
}



void removerMecanico(int ETs, ET* ETsArray, LEspera& f,Data* data) {
	string nomeMecanico;
	//int idmec = 0;
	int imec = 0;
	cout << "Diga o nome do mecanico para remover: ";
	cin >> nomeMecanico;
	bool removed = false;
	for (int i = 0; i < ETs; i++) {
		if (ETsArray[i].mecanico == nomeMecanico) {
			// Move todos os carros para reparados
			Reparando* aux = ETsArray[i].Reparando;
			while (aux != NULL) {
				Car car = aux->car;
				addReparados(ETsArray, car, i);
				aux = aux->Next;
			}
			imec = i;
			ETsArray[i].lotacao = 0; 
			ETsArray[i].mecanico = ""; 
			removed = true;
			break;
		}
	}
	if (!removed) {
		cout << "Mecanico nao encontrado.\n";
		return;
	}
	cout << "Mecanico saiu da oficina\n";

	cout << "Qual ser� o mec�nico para a ET " << imec + 1 << "? ";
	cin >> ETsArray[imec].mecanico;
	string marca = getUnusedMarca(data, data->Marca, imec);
	ETsArray[imec].marca = marca;
	data->Marcas[imec] = marca;
	ETsArray[imec].capacidade = rand() % 6 + 3;
	ETsArray[imec].Reparando = NULL;
}

void AddET(Data* data) {
	int aux = data->ETs + 1;
	ET* auxx = new ET[aux];
	for (int i = 0; i < data->ETs; i++) {
		auxx[i] = data->ETsArray[i];
	}
	auxx[aux - 1].id = aux;
	cout << "Qual ser� o mecanico para a ET" << aux << ":" << endl;
	cin >> auxx[aux - 1].mecanico;
	cout << "Qual a marca :" << endl;
	cin >> auxx[aux - 1].marca;
	auxx[aux - 1].capacidade = rand() % 6 + 3;
	delete[] data->ETsArray;
	data->ETsArray = auxx;
	data->ETs = aux;
	//data->Marcas[aux] = marca;
}