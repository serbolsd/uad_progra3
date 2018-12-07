#pragma once
#include "CVector3.h"
#include "CCamara.h"
#include "CGrid.h"
#include "Globals.h"
#include "CApp.h"

class CQuadTree;

class CQuadTreeNode: public CApp
{
public:
	CQuadTreeNode();
	CQuadTreeNode(int window_width, int window_height);
	~CQuadTreeNode();
	CVector3 m_bands[4];
	CVector3 m_aabb[4];

	CCamara camera;

	vector<CVector3> m_posiciones;

	vector<CVector3> m_nodo1;
	vector<CVector3> m_nodo2;
	vector<CVector3> m_nodo3;
	vector<CVector3> m_nodo4;

	CGrid m_grid;
	void calcularTamaño();
	void render();
	CQuadTree *tree;

	CVector3 m_positionOject;
	double m_currentDeltaTime;
	double m_objectRotation;
	double m_rotationSpeed;
	bool m_initialized;

	void render();
	void initialize();
	void run();

	void update(double deltatime);
	bool initializeMenu() { return false; }

	void revisarCam();

private:

};

