#pragma once
#include "C3DModel.h"
#include "CVector3.h"
#include <iostream>

using namespace std;

class CGameObject
{
public:
	CGameObject();
	~CGameObject();
	

private:
	C3DModel * M_Pmodel;
	float m_scale;
	int G;
	CVector3 m_pVertices[9];
	CVector3 m_center;
	int x, y, z;
};

