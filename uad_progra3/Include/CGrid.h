#pragma once
#include "CGridCell.h"
#include "Globals.h"
#include "CApp.h"

class CGrid: public CApp
{
public:
	CGrid();
	CGrid(int window_width, int window_height);
	~CGrid();

	void paintGrid();
	CGridCell m_celda;
	//void createShader();
	void initialize();
	void run();
	void update(double deltatime);
	void render();
	bool initializeMenu() { return false; }
	int filas = 100;
	int columnas = 100;
	float **m_cellPosition;
	void createSavePositions();
	float incrementoX = 1.76;
	float incrementoY = 1.7 - .13;
	float incrementoX2 = 1.76 / 2;

	void SavePositions(vector<CVector3> &vec);

private:
//	CGridCell * m_pGridCell;
	bool m_initialized;
	int m_size;
	int m_cellSize;


	// White 
	// Colors are in the 0..1 range, if you want to use RGB, use (R/255, G/255, G/255)
	unsigned int noTexture = 0;
	/*float incrementoX = 1.76;
	float incrementoY = 1.7 - .13;
	float incrementoX2 = 1.76 / 2;*/
	
	float totalTamañoX = incrementoX * columnas;
	float totalTamañoY = incrementoY * filas;
	float inicialX = (totalTamañoX / 2) - totalTamañoX;
	float inicialY = (totalTamañoY / 2) - totalTamañoY;
	int count = 0;
	float colorR = 7;
	float colorG = 102;
	float colorB = 204;
	// Current delta time (time of the current frame - time of the last frame)
	double m_currentDeltaTime;

	// Current object rotation, expressed in degrees
	double m_objectRotation;

	// Current object position
	CVector3 m_objectPosition;
	CVector3 m_vecForSavePosition;
	

	//  Object rotation speed (degrees per second)
	double m_rotationSpeed;
	float color[3];
	float color1[3] = { colorR + 100,colorG - 50,colorB - 100 };
	float color2[3] = { colorR,colorG,colorB };


	double totalDegreesRotatedRadians = m_objectRotation * 3.1459 / 180.0;
	

};

