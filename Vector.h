#ifndef VECTOR_H
#define VECTOR_H
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;
class Vector
{
public:
	double x, y, z;
	Vector() {
		x = y = z = 0;
	}
	Vector(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	double norm2() {
		return x * x + y * y + z * z;
	}

	Vector normalize() {
		double norm = sqrt(norm2());
		x /= norm; y /= norm; z /= norm;
		return *this;
	}

	double max() {
		return std::max(x, std::max(y, z));
	}
	double min() {
		return std::min(x, std::min(y, z));
	}
	void print() const {
		printf("%.5lf %.5lf %.5lf\n", x, y, z);
	}

	Vector operator+(const Vector &b) {
		return Vector(this->x + b.x, this->y + b.y, this->z + b.z);
	}
	Vector operator-(const Vector &b) {
		return Vector(this->x - b.x, this->y - b.y, this->z - b.z);
	}
	Vector operator*(const Vector &b) {
		return Vector(this->x * b.x, this->y * b.y, this->z * b.z);
	}
	Vector operator*(const double &b) {
		return Vector(this->x * b, this->y * b, this->z * b);
	}
	Vector operator/(const Vector &b) {
		return Vector(this->x / b.x, this->y / b.y, this->z / b.z);
	}
	Vector operator/(const double &b) {
		return Vector(this->x / b, this->y / b, this->z / b);
	}

	bool operator<(const Vector& b) const {
		return x < b.x;
	}

	Vector cross(const Vector &b) {
		return Vector(this->y * b.z - this->z * b.y, -this->x * b.z + this->z * b.x, this->x * b.y - this->y * b.x);
	}
	double dot(const Vector &b) {
		return this->x * b.x + this->y * b.y + this->z * b.z;
	}
	
};

class Matrix {
public:
	int n;
	double **v;//value
	Matrix(int n) {
		this->n = n;
		v = new double*[n];
		for (int i = 0; i < n; i++)
			v[i] = new double[n];
	}
	~Matrix() {
		for (int i = 0; i < n; i++) {
			delete[] v[i];
		}
		delete[] v;
	}
	//inverse
	Matrix inv();
	double& at(int i, int j) {
		return v[i - 1][j - 1];
	}

};

typedef Vector Color;
typedef Vector Point;


double sqr(int x);

Vector operator*(const Matrix &a, const Vector &b);

Vector min(const Vector &a, const Vector &b);

Vector max(const Vector &a, const Vector &b);

double det(const Vector &a, const Vector &b, const Vector &c);

#endif

