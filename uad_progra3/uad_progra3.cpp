// uad_progra3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
using namespace std;

#include "Include/CGameWindow.h"
#include "Include/CApp.h"
#include "Include/CAppParcial2.h"
#include "Include/figuras_geometricas.h"
#include "Include/CGridGame.h"
//#include "Include/CAppHexGrid.h"
#include "Include/CAppEmpty.h"

int main()
{
	CApp *app = NULL;                  // Pointer to BASE class CApp
	//WCHAR *esto=NULL;
	/*string aquello;
	char identificdor;
	int count = 0;
	LPWSTR getCommand;
	LPTCH getEnviro;
	getCommand = GetCommandLineW();
	esto=GetCommandLineW();
	cout << getCommand << endl;
	cout << *getCommand << endl;
	cout << &getCommand << endl;
	cout << &esto << endl;
	cout << *esto << endl;
	esto = getCommand;
	cout << aquello << endl;
	identificdor = esto[count];
	while (identificdor!='\0')
	{
		aquello += identificdor;
		count++;
		identificdor = esto[count];
	}
	cout << aquello << endl;
	aquello = *esto;
	cout << esto << endl;
	cout << aquello << endl;
	esto=GetEnvironmentStringsW();
	getEnviro = GetEnvironmentStringsW();
	cout << getEnviro << endl;
	cout << *getEnviro << endl;
	cout << &getEnviro << endl;
	cout << &esto << endl;
	cout << *esto << endl;*/
	//app = new CAppEmpty(800, 600);     // Using pointer to base class, create a new object of DERIVED class
	//app = new CAppParcial2(800, 600);
	//app = new Cgeomretria(800, 600);
	app = new CGridGame(800, 600);
	app->run();                        // Run the app
	delete app;                        // Delete pointer
	//delete esto;
	app = NULL;                        // Set pointer to NULL

	return 0;
}

