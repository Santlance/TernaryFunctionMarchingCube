#include "MarchingCube.h"
#include <fstream>

void MarchingCube::reconstruct() {
	 // 对于所有的函数进行统一操作
	for (int i = 0; i < functions.size(); i++) {
		ternaryFunction* func = functions[i];
		for (int cubeIndexZ = -cubeCountZ; cubeIndexZ < cubeCountZ; cubeIndexZ++) {
			for (int cubeIndexX = -cubeCountX; cubeIndexX < cubeCountX; cubeIndexX++) {
				for (int cubeIndexY = -cubeCountY; cubeIndexY < cubeCountY; cubeIndexY++) {
					// 记录当前立方体xyz坐标
					Vector basePos(cubeIndexX * cubeSizeX,cubeIndexY * cubeSizeX, cubeIndexZ * cubeSizeZ);
					// 计算立方体的8个顶点坐标，由于采用右手坐标系，顺序后表面左下v1，逆时针v2v3v4，前表面左下v5，逆时针v6v7v8
					// 是1987年论文的立方体前后面交换
					Vector verPos[8] =
					{
						basePos + Vector(0,0,0), // v1
						basePos + Vector(0,cubeSizeY,0),// v2
						basePos + Vector(0,cubeSizeY,cubeSizeZ), // v3
						basePos + Vector(0,0,cubeSizeZ), // v4
						basePos + Vector(cubeSizeX,0,0), // v5
						basePos + Vector(cubeSizeX,cubeSizeY,0), // v6
						basePos + Vector(cubeSizeX,cubeSizeY,cubeSizeZ), // v7
						basePos + Vector(cubeSizeX,0,cubeSizeZ) // v8
					};

					//计算是那种三角面片的情形
					int triCaseIndex = 0;
					for (int v = 0; v < 8; v++) {
						// 直接根据当前的func计算顶点
						double result = func->getResult(verPos[v]);
						if (result < 0) {
							triCaseIndex |= (1 << v);
						}
					}
					if (triCaseIndex == 0 || triCaseIndex == 255)continue;
					edge edges[12] = {
						edge(verPos[0] , verPos[1]),
						edge(verPos[1] , verPos[2]),
						edge(verPos[2] , verPos[3]),
						edge(verPos[3] , verPos[0]),
						edge(verPos[4] , verPos[5]),
						edge(verPos[5] , verPos[6]),
						edge(verPos[6] , verPos[7]),
						edge(verPos[7] , verPos[4]),
						edge(verPos[0] , verPos[4]),
						edge(verPos[1] , verPos[5]),
						edge(verPos[3] , verPos[7]),
						edge(verPos[2] , verPos[6]),
						// 如果有错就是在这里
					};

					for (int j = 0; j < 16; j += 3) {
						if (triangleCase[triCaseIndex][j] == -1)break;
						edge e1 = edges[triangleCase[triCaseIndex][j]];
						edge e2 = edges[triangleCase[triCaseIndex][j + 1]];
						edge e3 = edges[triangleCase[triCaseIndex][j + 2]];
						Vector p1 = linearInterpolation(e1.pts, e1.pte, func, 0);
						Vector p2 = linearInterpolation(e2.pts, e2.pte, func, 0);
						Vector p3 = linearInterpolation(e3.pts, e3.pte, func, 0);
						addVertex(p1);
						addVertex(p2);
						addVertex(p3);
						addEdge(id-1,id-2,id-3);
					}

				}
			}
		}
	}
}


// 线性插值
Vector MarchingCube::linearInterpolation(Vector p1, Vector p2, ternaryFunction* func, double T) {
	double I1 = func->getResult(p1);
	double I2 = func->getResult(p2);
	Vector p = p1 + (p2 - p1) * ((T-I1)/(I2 - I1));
	return p;
}

int MarchingCube::addVertex(Vector p) {
	vertexs.push_back(p);
	return id++;
}

void MarchingCube::addEdge(int id1, int id2, int id3) {
	std::tuple<int, int, int> t = std::make_tuple(id1,id2,id3);
	edges.push_back(t);
}

void MarchingCube::print(std::string filename) {
	std::ofstream output;
	output.open(filename);
	for (int it = 0; it < vertexs.size(); it++) {
		Vector p = vertexs[it];
		output << "v " << p.x << " " << p.y << " " << p.z << std::endl;
	}
	for (int i = 0; i < edges.size(); i++) {
		std::tuple<int, int, int> t = edges[i];
		output << "f " << std::get<0>(t) << " " << std::get<1>(t) << " " << std::get<2>(t) << std::endl;
	}
}

void MarchingCube::addFunction(ternaryFunction* func) {
	functions.push_back(func);
}


int MarchingCube::getId(Vector p) {
	return idtable[p];
}