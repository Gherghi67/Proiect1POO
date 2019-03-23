#include "Polinom.h"
#include <iostream>
#include <fstream>
#include <process.h>
using namespace std;
int main() {
	Polinom a(3); // constructor cu parametru
	cin >> a; // citire polinom
	cout << a; // afisare polinom
	Polinom b(a); // constructor de copiere
	cout << b; // afisare b dupa ce a este copiat in b
	Polinom c; // constructor fara parametrii
	c = a; // operator de atribuire
	cout << c; // afisare c dupa ce a este copiat in c
	cout << a.CalculateValue(2) << "\n"; // calculare valoare polinom a in punctul 2
	Polinom d;
	d = a + b; // operator de adunare
	cout << d;
	a[2] = 100; // operator de indexare;
	cout << a;
	Polinom e;
	e = a * b; // operator de inmultire
	cout << e;
	e = 2 * e; // operator de inmultire cu un scalar
	cout << e;
	a.AddElement(10, 15); // adaugam coeficientul 15 pentru gradul 10;
	cout << a;
	a.RemoveElement(1); // eliminam elementul de grad 1
	cout << a;
	cout << a.GetDegree() << "\n"; // afisam gradul polinomului a
	system("pause");
	return 0;
}