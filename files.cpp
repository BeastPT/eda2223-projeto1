#include <iostream>
#include <fstream>
#include <string>
#include "Files.h"
#include "structs.h"
#include "LEspera.h"

int calculateSizeofFile(string path) {

	fstream file;
	file.open(path, ios::in);

	string line = "";
	int cont = 0;

	if (file.is_open())
		while (getline(file, line))
			cont++;
	else
		cout << "Erro ao abrir o ficheiro " << path << ". Verificar novamente a localização" << endl;

	file.close();

	return cont;
}

string* getContentFromFiles(string path, int sizeofFile) {

	fstream file;
	file.open(path, ios::in);
	file.clear();
	file.seekg(0, ios::beg);

	int cont = 0;
	string* arrayFileContent = new string[sizeofFile];

	if (file.is_open())
		while (!file.eof())
			getline(file, arrayFileContent[cont++]);
	else
		cout << "Erro ao abrir o ficheiro " << path << ". Verificar novamente a localização." << endl;

	file.close();

	return arrayFileContent;

}

void saveCars(LEspera& f,Data* data , Filepaths* filepath) {
	fstream file;
	file.open(filepath->pathCars, ios::out);
	file.clear();
	file.seekp(0, ios::beg);
	// ID_CARRO MARCA-MODELO FILA PRIO REPARADO ID_ET(0 IF FILA TRUE) TEMPOREPARAR TEMPOET
	if (f.primeiro == NULL) {
		cout << "SAVE CARS: Lista de espera vazia" << endl;
	}
	else {
		LEspera::Item* aux = f.primeiro;
		while (aux != NULL) {
			file << aux->car->id << " " << aux->car->marca << "-" << aux->car->modelo << " " << true << " " << aux->car->prioritario << " " << false << " " << 0 << " " << aux->car->temporeparar << " " << aux->car->tempoet << endl;
			aux = aux->seguinte;
		}
	}
	for (int i = 0; i < data->ETs; i++) {
		// A reparar
		for (int j = 0; j < data->ETsArray[i].lotacao; j++) {
			Car aux = data->ETsArray[i].Reparando[j];
			file << aux.id << " " << aux.marca << "-" << aux.modelo << " " << false << " " << aux.prioritario << " " << false << " " << i << " " << aux.temporeparar << " " << aux.tempoet << endl;
		}
		// Reparados
		if (data->ETsArray[i].reparados != 0) {
			for (int j = 0; j < data->ETsArray[i].reparados; j++) {
				Car aux = data->ETsArray[i].Reparados[j];
				file << aux.id << " " << aux.marca << "-" << aux.modelo << " " << false << " " << aux.prioritario << " " << true << " " << i << " " << aux.temporeparar << " " << aux.tempoet << " " << endl;
			}
		}
	}

	file.close();
	return;
}

void saveETs(Data* data, Filepaths* filepath) {
	fstream file;
	file.open(filepath->pathETs, ios::out);
	file.clear();
	file.seekp(0, ios::beg);
	// ID_OFICINA MECANICO MARCA CAPACIDADE LOTACAO REPARADOS FATURACAO
	for (int i = 0; i < data->ETs; i++) {
		file << data->ETsArray[i].id << " " << data->ETsArray[i].mecanico << " " << data->ETsArray[i].marca << " " << data->ETsArray[i].capacidade << " " << data->ETsArray[i].lotacao << " " << data->ETsArray[i].reparados << " " << data->ETsArray[i].faturacao << endl;
	}

	file.close();
	return;
}