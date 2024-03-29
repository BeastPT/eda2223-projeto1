#include <iostream>
#include <fstream>
#include <string>
#include "Files.h"
#include "structs.h"
#include "LEspera.h"
#include "ETs.h"
#include "Reparando.h"

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

void saveReparados(fstream& file, No* root, int et) {
	if (root == nullptr) {
		return;
	}
	file << root->car.id << " " << replaceSpaces(root->car.marca) << " " << root->car.modelo << " " << false << " " << root->car.prioritario << " " << true << " " << et + 1 << " " << root->car.temporeparar << " " << root->car.tempoet << endl;
	//cout << "car " << replaceSpaces(root->car.marca) << " " << root->car.modelo << " " << i << " " << reparados << endl;
	saveReparados(file, root->Left, et);
	saveReparados(file, root->Right, et);
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
		Car* carArr = carArray(data->ETsArray[i].Reparando, data->ETsArray[i].lotacao);
		for (int j = 0; j < data->ETsArray[i].lotacao; j++) {
			Car aux = carArr[j];
			file << aux.id << " " << replaceSpaces(aux.marca) << " " << aux.modelo << " " << false << " " << aux.prioritario << " " << false << " " << i + 1 << " " << aux.temporeparar << " " << aux.tempoet;
			if (j < data->ETsArray[i].lotacao - 1)
				file << endl;
		}
		// Reparados
		/*if (data->ETsArray[i].reparados != 0) {
			file << endl;
			for (int j = 0; j < data->ETsArray[i].reparados; j++) {
				Car aux = data->ETsArray[i].Reparados[j];
				file << aux.id << " " << replaceSpaces(aux.marca) << " " << aux.modelo << " " << false << " " << aux.prioritario << " " << true << " " << i + 1 << " " << aux.temporeparar << " " << aux.tempoet;
				if (j < data->ETsArray[i].reparados - 1)
					file << endl;
			}
		}*/
		if (data->ETsArray[i].reparados != 0) {
			file << endl;
			saveReparados(file, data->ETsArray[i].Reparados, i);
			/*if (data->ETsArray[i].Reparados == nullptr) {
				cout << "SAVE REPARADOS: Arvore vazia" << endl;
			}
			else {
				No* aux = data->ETsArray[i].Reparados;
				int auxx = 0;
				int auxxx = data->ETsArray[i].reparados;
				while (aux != nullptr) {
					auxx++;
					file << auxx << " " << auxxx << " " << aux->car.id << " " << replaceSpaces(aux->car.marca) << " " << aux->car.modelo << " " << false << " " << aux->car.prioritario << " " << true << " " << i + 1 << " " << aux->car.temporeparar << " " << aux->car.tempoet;
					if (auxx < auxxx - 1)
						file << endl;
					aux = aux->Left;
				}
				aux = data->ETsArray[i].Reparados;
				while (aux != nullptr) {
					auxx++;
					file << auxx << " " << auxxx << " " << aux->car.id << " " << replaceSpaces(aux->car.marca) << " " << aux->car.modelo << " " << false << " " << aux->car.prioritario << " " << true << " " << i + 1 << " " << aux->car.temporeparar << " " << aux->car.tempoet;
					if (auxx < auxxx - 1)
						file << endl;
					aux = aux->Right;
				}
			}*/
		}

		/*if (i < data->ETs - 1)
			file << endl;*/
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
		file << data->ETsArray[i].id << " " << data->ETsArray[i].mecanico << " " << replaceSpaces(data->ETsArray[i].marca) << " " << data->ETsArray[i].capacidade << " " << data->ETsArray[i].lotacao << " " << data->ETsArray[i].reparados << " " << 0;//data->ETsArray[i].faturacao;
		if (i != data->ETs - 1)
			file << endl;
	}


	file.close();
}

void loadCars(LEspera& f, Data* data, Filepaths* filepath) {
	data->Cars = calculateSizeofFile(filepath->pathCars);
	string* arrayFileContent = getContentFromFiles(filepath->pathCars, data->Cars+1);
	for (int i=0; i< data->Cars; i++){
		string s = arrayFileContent[i];
		if (s.compare("") == 0)
			continue;
		Car* car = new Car;
		size_t pos = 0;
		string token;
		int aux = 0;
		string* info = new string[9];
		while ((pos = s.find(" ")) != string::npos) {
			token = s.substr(0, pos);
			s.erase(0, pos + 1);
			info[aux++] = token;
		}
		car->id = stoi(info[0]);
		car->marca = replacePlus(info[1]);
		car->modelo = info[2];
		car->fila = (info[3].compare("1") == 0 ? true : false);
		car->prioritario = (info[4].compare("1") == 0 ? true : false);
		car->reparado = (info[5].compare("1") == 0 ? true : false);
		car->idet = stoi(info[6]);
		car->temporeparar = stoi(info[7]);
		car->tempoet = stoi(s);


		if (car->idet != 0 && !car->reparado) {
			data->ETsArray[car->idet - 1].Reparando = insertReparando(data->ETsArray[car->idet - 1].Reparando , *car);
			data->ETsArray[car->idet - 1].lotacao++;
		}
		else if (car->idet != 0 && car->reparado) {
			addReparados(data->ETsArray, *car, car->idet-1);
		}
		else {
			addToLEspera(f, car);
		}
	}
	delete[] arrayFileContent;
}

void loadETs(Data* data, Filepaths* filepath) {
	data->ETs = calculateSizeofFile(filepath->pathETs);
	data->ETsArray = new ET[data->ETs];
	data->Marcas = new string[data->ETs];
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
		et->reparados = 0; //stoi(info[5]);
		et->faturacao = 0; 
		et->Reparando = NULL;
		data->ETsArray[i] = *et;
		data->Marcas[i] = et->marca;
	}
	delete[] arrayFileContent;
}
