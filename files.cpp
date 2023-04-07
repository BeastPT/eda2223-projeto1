#include <iostream>
#include <fstream>
#include <string>
#include "Files.h"


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