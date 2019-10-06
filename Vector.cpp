#include "Vector.h"

double sqr(int x) {
	return x * x;
}

Vector operator*(const Matrix &a, const Vector &b) {
	return Vector(
		a.v[0][0] * b.x + a.v[0][1] * b.y + a.v[0][2] * b.z,
		a.v[1][0] * b.x + a.v[1][1] * b.y + a.v[1][2] * b.z,
		a.v[2][0] * b.x + a.v[2][1] * b.y + a.v[2][2] * b.z
	);
}

Vector min(const Vector &a, const Vector &b) {
	return Vector(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

Vector max(const Vector &a, const Vector &b) {
	return Vector(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}

double det(const Vector &a, const Vector &b, const Vector &c) {
	return a.x * (b.y * c.z - b.z * c.y)
		- b.x * (a.y * c.z - a.z * c.y)
		+ c.x * (a.y * b.z - a.z * b.y);
}
