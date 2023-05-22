#include <iostream>

#include "LEspera.h"
#include "structs.h"
#include "ETs.h"
#include "management.h"
#include "Reparados.h"
#include <cctype>

using namespace std;

No* newNo(Car car) {
	No* no = new No;
	no->car = car;
	no->Left = NULL;
	no->Right = NULL;
	return no;
}

string toLowerCase(string str) {
	string result;
	for (char c : str) {
		result += tolower(c);
	}
	return result;
}

No* insert(No* root, Car car) {
	if (root == NULL) {
		return newNo(car);
	}
	else if (toLowerCase(car.marca) <= toLowerCase(root->car.marca)) {
		root->Left = insert(root->Left, car);
	}
	else if (car.marca > root->car.marca) {
		root->Right = insert(root->Right, car);
	}
	return root;
}

void printInOrder(No* root, int lvl) {
	if (root == NULL) {
		cout << endl;
		return;
	}
	printInOrder(root->Left, lvl + 1);
	for (int i = 1; i < lvl; i++)
	{
		cout << "\t";
	}
	cout << root->car.marca << endl;
	printInOrder(root->Right, lvl + 1);
}