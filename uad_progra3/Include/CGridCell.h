#pragma once
#include "CGameObject.h"

class CGridCell
{
public:
	CGridCell();
	~CGridCell();

	CGameObject * m_pGO;
	bool loaded;
	unsigned int m_shaderID;
	unsigned int m_geoVAOID;

	bool m_initialized;

#define PI 3.14159265358979323846

	int m_numFacesToRender = 6;
	int size = 1;
	float width = sqrt(3) * size;
	float height = 2 * size;
	float centerWidth = width / 2;
	float centerHeight = height / 2;
	int numAristas = 6;
	int numVertices = 7;
	//int numFaces = (12 * 2) + 2;
	float anguloY = 360 / 6;
	float Z1 = 0.0f;
	float Z2 = -0.25;
	float *vdata = new float[numVertices * 3];
	int **Vertex = new int *[3];
	unsigned short nIndice[6 * 3];
	unsigned short vIndices[6 * 3];
	float nData[6 * 3];
	//float PI = 3.14159245358979323846;
	// ============================== SECTION
	void paintHexa();
private:

};

//	GRID.createHex;





