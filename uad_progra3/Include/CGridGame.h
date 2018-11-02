#pragma once
#include "Globals.h"
#include "CApp.h"
#include "CGrid.h"

class CGridGame:public CApp, CGrid
{
public:
	CGridGame();
	CGridGame(int window_width, int window_height);
	~CGridGame();

	void initialize();

	void run();

	void update(double deltaTime);

	void render();
	
	bool initializeMenu() { return false; }

private:
//	CGrid m_pGrid;
	CGrid *m_grid=NULL;

	void inicialize();
	void load3DObject();

	bool m_initialized;

	std::vector<CGameObject *> m_pGameObjects;
	std::vector<C3DModel> m_pMeshe;

};

