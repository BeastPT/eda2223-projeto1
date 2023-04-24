#pragma once

#include "structs.h"
#include "LEspera.h"

using namespace std;

int calculateSizeofFile(string path);

string* getContentFromFiles(string path, int sizeofFile);

void saveCars(LEspera& f, Data* data, Filepaths* filepath);

void saveETs(Data* data, Filepaths* filepath);