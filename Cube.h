#ifndef CUBE_H
#define CUBE_H
#include "Vector.h"
#include <vector>

// һ��cube�ɰ˸��������
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

