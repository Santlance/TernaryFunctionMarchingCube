#ifndef TERNARYFUNCTION_H
#define TERNARYFUNCTION_H
#include "Vector.h"
// assume this function has the form as ax^2 + by^2 + cz^2 + dxy + exz + fyz + hx + iy + jz + k = 0
class ternaryFunction
{
public:
	double coeffxx;
	double coeffyy;
	double coeffzz;
	double coeffxy;
	double coeffxz;
	double coeffyz;
	double coeffx;
	double coeffy;
	double coeffz;
	double coeffcon;

	ternaryFunction(double xx, double yy, double zz, double xy, double xz, double yz, double x, double y, double z,double c) {
		coeffxx = xx;
		coeffyy = yy;
		coeffzz = zz;
		coeffxy = xy;
		coeffxz = xz;
		coeffyz = yz;
		coeffx = x;
		coeffy = y;
		coeffz = z;
		coeffcon = c;
	}
	
	double getResult(Vector p) {
		double x = p.x;
		double y = p.y;
		double z = p.z;
		return coeffxx * x * x + coeffyy * y * y + coeffzz * z * z + coeffxy * x * y + coeffxz * x * z + coeffyz * y * z + coeffx * x + coeffy * y + coeffz * z + coeffcon;
	}
};

#endif

