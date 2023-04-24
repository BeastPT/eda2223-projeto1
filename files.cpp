#include <iostream>
#include <fstream>
#include <string>
#include "Files.h"
#include "structs.h"
#include "LEspera.h"
#include "ETs.h"

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
	cout << "Ficheiro " << path << " carregado com sucesso." << endl;
	return arrayFileContent;

}

string replaceSpaces(string str) {
	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] == ' ') {
			str[i] = '+';
		}
	}
	return str;
}

string replacePlus(string str) {
	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] == '+') {
			str[i] = ' ';
		}
	}
	return str;
}

void saveCars(LEspera& f,Data* data , Filepaths* filepath) {
	fstream file;
	file.open(filepath->pathCars, ios::out);
	file.clear();
	file.seekp(0, ios::beg);
	// ID_CARRO MARCA MODELO FILA PRIO REPARADO ID_ET(0 IF FILA TRUE) TEMPOREPARAR TEMPOET
	if (f.primeiro == NULL) {
		cout << "SAVE CARS: Lista de espera vazia" << endl;
	}
	else {
		LEspera::Item* aux = f.primeiro;
		while (aux != NULL) {
			file << aux->car->id << " " << replaceSpaces(aux->car->marca) << " " << aux->car->modelo << " " << true << " " << aux->car->prioritario << " " << false << " " << 0 << " " << aux->car->temporeparar << " " << aux->car->tempoet << endl;
			aux = aux->seguinte;
		}
	}
	for (int i = 0; i < data->ETs; i++) {
		// A reparar
		for (int j = 0; j < data->ETsArray[i].lotacao; j++) {
			Car aux = data->ETsArray[i].Reparando[j];
			file << aux.id << " " << replaceSpaces(aux.marca) << " " << aux.modelo << " " << false << " " << aux.prioritario << " " << false << " " << i << " " << aux.temporeparar << " " << aux.tempoet << endl;
		}
		// Reparados
		if (data->ETsArray[i].reparados != 0) {
			for (int j = 0; j < data->ETsArray[i].reparados; j++) {
				Car aux = data->ETsArray[i].Reparados[j];
				file << aux.id << " " << replaceSpaces(aux.marca) << "-" << aux.modelo << " " << false << " " << aux.prioritario << " " << true << " " << i << " " << aux.temporeparar << " " << aux.tempoet << " " << endl;
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
		file << data->ETsArray[i].id << " " << data->ETsArray[i].mecanico << " " << replaceSpaces(data->ETsArray[i].marca) << " " << data->ETsArray[i].capacidade << " " << data->ETsArray[i].lotacao << " " << data->ETsArray[i].reparados << " " << data->ETsArray[i].faturacao;
		if (i != data->ETs - 1)
			file << endl;
	}


	file.close();
}

void loadCars(LEspera& f, Data* data, Filepaths* filepath) {
	data->Cars = calculateSizeofFile(filepath->pathCars);
	string* arrayFileContent = getContentFromFiles(filepath->pathCars, data->Cars);
	for (int i=0; i< data->Cars; i++){
		string s = arrayFileContent[i];
		Car car;
		size_t pos = 0;
		string token;
		int aux = 0;
		string* info = new string[9];
		while ((pos = s.find(" ")) != string::npos) {
			token = s.substr(0, pos + 1);
			s.erase(0, pos + 1);
			info[aux++] = token;
		}
		car.id = stoi(info[0]);
		car.marca = replacePlus(info[1]);
		car.modelo = info[2];
		car.fila = (info[3] == "1" ? true : false);
		car.prioritario = (info[4] == "1" ? true : false);
		car.reparado = (info[5] == "1" ? true : false);
		car.idet = stoi(info[6]);
		car.temporeparar = stoi(info[7]);
		car.tempoet = stoi(s);

		if (car.idet != 0 && !car.reparado) {
			data->ETsArray[car.idet - 1].Reparando[data->ETsArray[car.idet - 1].lotacao++] = car;
		}
		else if (car.idet != 0 && car.reparado) {
			addReparados(data->ETsArray, car, i);
		}
		else {
			addToLEspera(f, &car);
		}
	}
	//delete[] arrayFileContent;
}

void loadETs(Data* data, Filepaths* filepath) {
	data->ETs = calculateSizeofFile(filepath->pathETs);
	cout << data->ETs << endl;
	string* arrayFileContent = getContentFromFiles(filepath->pathETs, data->ETs);
	for (int i = 0; i < data->ETs; i++) {
		string s = arrayFileContent[i];
		ET* et = new ET;
		size_t pos = 0;
		string token;
		int aux = 0;
		string* info = new string[7];
		while ((pos = s.find(" ")) != string::npos) {
			token = s.substr(0, pos);
			s.erase(0, pos + 1);
			info[aux++] = token;
		}
		et->id = stoi(info[0]);
		et->mecanico = info[1];
		et->marca = replacePlus(info[2]);
		et->capacidade = stoi(info[3]);
		et->lotacao = 0; //stoi(info[4]);
		et->faturacao = 0; //stoi(info[5]);
		et->reparados = stoi(s);
		et->Reparando = new Car[et->capacidade];
		et->Reparados = new Car[et->reparados];
		cout << "end" << endl;
		data->ETsArray[i] = *et;
		data->Marcas[i] = et->marca;

	}
	//delete[] arrayFileContent;

}
