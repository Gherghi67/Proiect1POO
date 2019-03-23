#pragma once
#include <iostream>
using namespace std;
class Polinom {
private:
	int degree; // gradul polinomului
	int* coefficients; // coeficientii polinomului care sunt retinuti intr-un array
public:
	Polinom();
	Polinom(int degree);
	Polinom(const Polinom &polinom);
	Polinom& operator= (const Polinom &polinom);
	~Polinom();
	friend istream& operator>>(istream &in, Polinom &polinom);
	friend ostream& operator<<(ostream &out, const Polinom &polinom);
	int CalculateValue(int x) const;
	Polinom operator+(const Polinom &polinom) const;
	Polinom operator-(const Polinom &polinom) const;
	int& operator[](int index);
	Polinom operator*(const Polinom &polinom) const;
	friend Polinom operator*(int x, const Polinom &polinom); // implementam functia de inmultire cu un scalar ca friend pentru comutativitate
	Polinom operator/(const Polinom &polinom) const;
	void AddElement(int i, int x);
	void RemoveElement(int i);
	int GetDegree() const;
};