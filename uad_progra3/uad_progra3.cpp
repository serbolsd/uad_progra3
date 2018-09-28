// uad_progra3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
using namespace std;

#include "Include/CGameWindow.h"
#include "Include/CApp.h"
#include "Include/CAppParcial2.h"
#include "Include/figuras_geometricas.h"
//#include "Include/CAppHexGrid.h"
#include "Include/CAppEmpty.h"

int main()
{
	CApp *app = NULL;                  // Pointer to BASE class CApp
	//app = new CAppEmpty(800, 600);     // Using pointer to base class, create a new object of DERIVED class
	app = new CAppParcial2(800, 600);
	//app = new Cgeomretria(800, 600);
	app->run();                        // Run the app
	delete app;                        // Delete pointer
	app = NULL;                        // Set pointer to NULL

	return 0;
}

