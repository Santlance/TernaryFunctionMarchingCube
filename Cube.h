#ifndef CUBE_H
#define CUBE_H
#include "Vector.h"
#include <vector>

// 一个cube由八个顶点组成
class Cube
{
public:
	std::vector<Vector> vertexs;

	Cube() {
	
	}

	void addVertex(Vector v) {
		vertexs.push_back(v);
	}
};
#endif

