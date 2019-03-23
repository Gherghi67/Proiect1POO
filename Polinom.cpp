#include "Polinom.h"
#include <iostream>
#include <cmath>
using namespace std;
Polinom::Polinom() {
	this->degree = 0;
	this->coefficients = NULL;
}
Polinom::Polinom(int degree) {
	this->degree = degree;
	this->coefficients = new int[degree + 1];
	int i;
	for (i = 0; i <= degree; i++) {
		this->coefficients[i] = 0; // setam coeficientii initial cu 0
	}
}
Polinom::Polinom(const Polinom &polinom) {
	this->degree = polinom.degree;
	this->coefficients = new int[this->degree + 1];
	int i;
	for (i = 0; i <= this->degree; i++) {
		this->coefficients[i] = polinom.coefficients[i]; // copiem coeficientii 
	}
}
Polinom& Polinom::operator=(const Polinom &polinom) {
	if (&polinom == this) { // verificare self-assignment
		return *this;  
	}
	delete[] this->coefficients; // stergere continut vechi
	this->degree = polinom.degree;
	this->coefficients = new int[this->degree + 1];
	int i;
	for (i = 0; i <= this->degree; i++) {
		this->coefficients[i] = polinom.coefficients[i]; // copiem coeficientii
	}
	return *this;
}
Polinom::~Polinom() {
	delete[] this->coefficients; // stergem array-ul de coeficienti
	this->degree = 0;
}
istream& operator >> (istream &in, Polinom &polinom) {
	int i;
	for (i = 0; i <= polinom.degree; i++) {
		in >> polinom.coefficients[i];   // citim coeficientii polinomului pornind de la coeficientul termenului liber
	}
	return in;
}
ostream& operator<<(ostream &out, const Polinom &polinom) {
	int i;
	for (i = polinom.degree; i >= 0; i--) {
		out << polinom.coefficients[i] << "x^" << i << "+"; // afisam coeficientii polinomului pornind de la coeficientul termenului de 
	                                                        // grad maxim
	}
	out << "\n";
	return out;
}
int Polinom::CalculateValue(int x) const {
	int i;
	int s = 0;
	for (i = 0; i <= this->degree; i++) {
		s = s + this->coefficients[i] * pow(x, i);
	}
	return s;
}
Polinom Polinom::operator+(const Polinom &polinom) const {
	Polinom p;
	/*Avem doua cazuri: unul in care gradul polinomului this este mai mare decat gradului polinomului polinom si invers.*/
	if (this->degree > polinom.degree) {
		p.degree = this->degree;
		p.coefficients = new int[this->degree + 1];
		int i;
		for (i = this->degree; i >= polinom.degree + 1; i--) {
			p.coefficients[i] = this->coefficients[i];
		}
		for (i = polinom.degree; i >= 0; i--) {
			p.coefficients[i] = this->coefficients[i] + polinom.coefficients[i];
		}
		return p;
	}
	else {
		p.degree = polinom.degree;
		p.coefficients = new int[polinom.degree + 1];
		int i;
		for (i = polinom.degree; i >= this->degree + 1; i--) {
			p.coefficients[i] = polinom.coefficients[i];
		}
		for (i = this->degree; i >= 0; i--) {
			p.coefficients[i] = this->coefficients[i] + polinom.coefficients[i];
		}
		return p;
	}
}
Polinom Polinom::operator-(const Polinom &polinom) const {
	Polinom p;
	if (this->degree > polinom.degree) {
		p.degree = this->degree;
		p.coefficients = new int[p.degree + 1];
		int i;
		for (i = this->degree; i >= polinom.degree + 1; i--) {
			p.coefficients[i] = this->coefficients[i];
		}
		for (i = polinom.degree; i >= 0; i--) {
			p.coefficients[i] = this->coefficients[i] - polinom.coefficients[i];
		}
		return p;
	}
	else {
		p.degree = polinom.degree;
		p.coefficients = new int[p.degree + 1];
		int i;
		for (i = polinom.degree; i >= this->degree + 1; i--) {
			p.coefficients[i] = polinom.coefficients[i];
		}
		for (i = this->degree; i >= 0; i--) {
			p.coefficients[i] = this->coefficients[i] - polinom.coefficients[i];
		}
		return p;
	}
}
int& Polinom::operator[](int index) {
	return coefficients[index];
}
Polinom Polinom::operator*(const Polinom &polinom) const {
	Polinom p;
	p.degree = this->degree + polinom.degree;
	p.coefficients = new int[p.degree + 1];
	int i;
	for (i = 0; i <= p.degree; i++) {
		p.coefficients[i] = 0;
	}
	int j;
	for (i = 0; i <= this->degree; i++) {
		for (j = 0; j <= polinom.degree; j++) {
			p.coefficients[i + j] += this->coefficients[i] * polinom.coefficients[j]; // aplicam algoritmul de inmultire a doua polinoame
		}
	}
	return p;
}
Polinom operator*(int x, const Polinom &polinom) {
	Polinom p;
	int i;
	p.degree = polinom.degree;
	p.coefficients = new int[p.degree + 1];
	for (i = 0; i <= polinom.degree; i++) {
		p.coefficients[i] = polinom.coefficients[i] * x;
	}
	return p;
}
Polinom Polinom::operator/(const Polinom &polinom) const {
	Polinom q(this->degree - polinom.degree);
	Polinom r(*this);
	while (r.degree >= polinom.degree) {
		Polinom multiplier(r.degree - polinom.degree);
		multiplier.coefficients[multiplier.degree] = r.coefficients[r.degree] / polinom.coefficients[polinom.degree];
		r = r - (multiplier * polinom);
		q = q + multiplier;
	}
	return q;
}
void Polinom::AddElement(int i, int x) {
	int* v = this->coefficients;
	this->coefficients = new int[i + 1];
	this->coefficients[i] = x;  // adaugam coeficientul pentru gradul i
	int j;
	for (j = i - 1; j >= this->degree + 1; j--) {
		this->coefficients[j] = 0;  // setam coeficientii de al gradul i - 1 pana la gradul this->degree + 1 cu 0
	}
	for (j = this->degree; j >= 0; j--) {
		this->coefficients[j] = v[j];  // copiem coeficientii
	}
	this->degree = i;
	delete[] v;
}
void Polinom::RemoveElement(int i) {
	this->coefficients[i] = 0;
}
int Polinom::GetDegree() const {
	return this->degree;
}