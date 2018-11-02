#include "../Include/CGridGame.h"
#include "../stdafx.h"

#include <iostream>
using namespace std;

#include "../Include/Globals.h"
#include "../Include/CAppEmpty.h"
#include "../Include/CWideStringHelper.h"

CGridGame::CGridGame()
{
}

CGridGame::CGridGame(int window_width, int window_height) 
{
	m_grid = new CGrid(window_width,window_height);
}

CGridGame::~CGridGame()
{
	delete m_grid;
}

void CGridGame::initialize()
{
	m_grid->initialize();
}

void CGridGame::run()
{
	m_grid->run();
}

void CGridGame::update(double deltaTime)
{
	m_grid->update(deltaTime);
}

void CGridGame::render()
{
	m_grid->render();
}
void CGridGame::load3DObject()
{
}