#include <iostream>
#include "MarchingCube.h"
#include "Vector.h"
using namespace std;


int main() {
	MarchingCube mc(Vector(0,0,0),100,100,100,0.05,0.05,0.05 );
	ternaryFunction* func = new ternaryFunction(1,1,1,0,0,0,0,0,0,-10);
	mc.addFunction(func);
	mc.reconstruct();
	mc.print("output.obj");
	return 0;
}