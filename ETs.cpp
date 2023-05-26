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
			break;
		}
	}
	if (aux) {
		marca = data->Marca[rand() % data->sizeMarcas];
		return getUnusedMarca(data, marcas, prev);
	}
	else {
		return marca;
	}
}


void initializeETs(Data* data) {
	for (int i = 0; i < data->ETs; i++) {
		data->ETsArray[i].id = i + 1;
		cout << "Qual será o mecânico para a ET " << i + 1 << "? ";
		cin >> data->ETsArray[i].mecanico;
		string marca = getUnusedMarca(data, data->Marca, i);
		data->ETsArray[i].marca = marca;
		data->Marcas[i] = marca;
		data->ETsArray[i].capacidade = rand() % 6 + 3;
		data->ETsArray[i].Reparando = nullptr;
		data->ETsArray[i].Reparados = nullptr;
	}
}


void printETs(int ETs, ET* ETsArray) {
	for (int i = 0; i < ETs; i++) {
		cout << "ET: " << ETsArray[i].id << " | Mecânico: " << ETsArray[i].mecanico << " | Capacidade: " << ETsArray[i].capacidade << " | Carros: " << ETsArray[i].lotacao << " | Marca: " << ETsArray[i].marca << " | Total Faturação: " << ETsArray[i].faturacao << endl;
		printReparando(ETsArray[i].Reparando);
		cout << "--------------------------------------------------------------------------" << endl;
	}
}

void addCarToET(Data* data, LEspera& f) {
	string* aux = new string[data->ETs];
	int count = 0;
	for (int i = 0; i < data->ETs; i++) {
		if (data->ETsArray[i].lotacao < data->ETsArray[i].capacidade) {
			aux[count++] = data->ETsArray[i].marca;
		}
	}

	Car car;
	try {
		car = removeFirstPossibleCar(f, aux, data->ETs);
	}
	catch (Car& c) {
		delete[] aux;
		return;
	}

	for (int j = 0; j < data->ETs; j++) {
		if (data->ETsArray[j].marca == car.marca) {
			car.idet = j;
			data->ETsArray[j].lotacao++;

			Reparando* newNode = new Reparando;
			newNode->car = car;
			newNode->Next = data->ETsArray[j].Reparando;
			data->ETsArray[j].Reparando = newNode;

			break;
		}
	}
	delete[] aux;
}
int totalCars(int ETs, ET* ETsArray) {
	int TotalCars = 0;
	for (int i = 0; i < ETs; i++) {
		TotalCars += ETsArray[i].lotacao;
	}
	return TotalCars;
}

Car* ETsCarsArray(int ETs, int TotalCars, ET* ETsArray) {
	Car* auxx = new Car[TotalCars];
	int aux = 0;

	for (int i = 0; i < ETs; i++) {
		Car* carsEt = carArray(ETsArray[i].Reparando, ETsArray[i].lotacao);

		for (int j = 0; j < ETsArray[i].lotacao; j++) {
			if (aux < TotalCars) {
				auxx[aux++] = carsEt[j];
			}
			else {
				// Lidar com a situação em que o tamanho máximo do array é excedido
				// Aqui você pode gerar um erro, lançar uma exceção ou lidar com isso de outra forma
				break;
			}
		}

		delete[] carsEt; // Liberar a memória alocada pela função carArray
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
	car.reparado = true;
	ETsArray[x].Reparados = insert(ETsArray[x].Reparados, car);
}

void repararCarros(int ETs, ET* ETsArray) {
	for (int i = 0; i < ETs; i++) {
		if (ETsArray[i].lotacao == 0)
			continue;
		else {
			//No* head = nullptr; // Cabeça da lista ligada
			int aux = 0;
			int* ids = new int[ETsArray[i].lotacao];
			Reparando* auxx = ETsArray[i].Reparando;
			while (auxx != nullptr) {
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
		cout << "Não existe nenhuma ET com essa marca" << endl;
		return;
	}

	Car car;
	try {
		car = getCar(ETsArray[aux].Reparando, modelorm);
	}
	catch (Car car) {
		cout << "Essa ET não tem nenhum carro desse modelo" << endl;
		return;
	}

	addReparados(ETsArray, car, aux);
	ETsArray[aux].Reparando = removeReparando(ETsArray[aux].Reparando, car.id);
	ETsArray[aux].lotacao--;
}




void removerMecanico(int ETs, ET* ETsArray, LEspera& f, Data* data) {
	string nomeMecanico;
	int imec = 0;
	cout << "Diga o nome do mecânico para remover: ";
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
		cout << "Mecânico não encontrado.\n";
		return;
	}
	cout << "Mecânico saiu da oficina\n";

	cout << "Qual será o mecânico para a ET " << imec + 1 << "? ";
	cin >> ETsArray[imec].mecanico;
	string marca = getUnusedMarca(data, data->Marcas, ETs);
	ETsArray[imec].marca = marca;
	data->Marcas[imec] = marca;
	ETsArray[imec].capacidade = rand() % 6 + 3;
	ETsArray[imec].Reparando = NULL;
}



void AddET(Data* data) {
	ET* newET = new ET;

	// Preencher os dados do novo elemento
	newET->id = data->ETs + 1;

	cout << "Qual será o mecânico para a ET " << newET->id << ":" << endl;
	cin >> newET->mecanico;

	cout << "Qual a marca:" << endl;
	cin >> newET->marca;

	newET->capacidade = rand() % 6 + 3;

	// Adicionar o novo elemento ao final da lista ligada
	if (data->ETsArray == nullptr) {
		// A lista está vazia, o novo elemento será o primeiro
		data->ETsArray = newET;
	}
	else {
		// Procurar o último elemento da lista
		ET* current = data->ETsArray;
		while (current->Next != nullptr) {
			current = current->Next;
		}

		// Adicionar o novo elemento após o último
		current->Next = newET;
	}

	data->ETs++; // Incrementar o contador de ETs

	// Exemplo de exibição da nova ET adicionada
	cout << "ET adicionada com sucesso!" << endl;
	cout << "ID: " << newET->id << endl;
	cout << "Mecânico: " << newET->mecanico << endl;
	cout << "Marca: " << newET->marca << endl;
	cout << "Capacidade: " << newET->capacidade << endl;
}