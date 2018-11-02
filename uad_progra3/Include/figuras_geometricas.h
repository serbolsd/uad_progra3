#pragma once

#ifndef CAPPEMPTY_H
#define CAPPEMPTY_H

#include "Globals.h"
#include "CApp.h"

// --------------------------------------------------------------------------------------------------------------------------------------
// Class that inherits from Base class CApp
// Base class CApp has members for: CGameWindow, CGameMenu, and COpenGLRenderer, which we can access through the public/protected methods
// --------------------------------------------------------------------------------------------------------------------------------------
class Cgeomretria : public CApp
{
private:

	// ---------------------------------------------------
	// Private member variables specific to Cgeomretria  only
	// ---------------------------------------------------
	//
	// ---------------------------------------------------

protected:

	// Method to initialize the menu 
	// (not needed in Cgeomretria , so return false)
	bool initializeMenu() { return false; }

public:
	// Constructors and destructor
	Cgeomretria ();
	Cgeomretria (int window_width, int window_height);
	~Cgeomretria ();

	// --------------------------------------------------------------------------------------------------------------------------
	// Inherited methods from CApp
	// Initialize(), update(), run(), and render() are PURE VIRTUAL methods, so they need to be implemented in this DERIVED class
	// --------------------------------------------------------------------------------------------------------------------------

	// Method to initialize any objects for this class
	void initialize();

	// Method to update any objecs based on time elapsed since last frame
	void update(double deltaTime);

	// Method to run the app
	void run();

	// Method to render the app
	//void render();

	// -----------------------------------------------------------------------------------------------------------------------
	// Other inherited methods from CApp. These are optional to override.
	// Only provide an implementation in this DERIVD class if you need them to do something different than the base class CApp
	// -----------------------------------------------------------------------------------------------------------------------

	// Executes the action corresponding to the selected menu item
	void executeMenuAction();

	// Called when mouse moves within the window
	void onMouseMove(float deltaX, float deltaY);

	// -----------------------------------------
	// Public methods specific to Cgeomretria  only
	// -----------------------------------------
	//
	// -----------------------------------------

	void createPiramid();

	void createDona();

	void createEsfera();
	

	void createCubo();
	
	void createTorus();
	
	void hexagon();
	void hexgrid();

#define PI       3.14159265358979323846;

	void render();

	unsigned int m_shaderID;
	unsigned int m_geoVAOID;

	bool m_initialized;

	int m_numFacesToRender;

private:

	// ------------------------------------------
	// Private methods specific to Cgeomretria  only
	// ------------------------------------------
	//
	// ------------------------------------------

	// Pointer to an object of type C3DModel
	//C3DModel *m_p3DModel;

	// Current delta time (time of the current frame - time of the last frame)
	double m_currentDeltaTime;

	// Current object rotation, expressed in degrees
	double m_objectRotation;

	// Current object position
	CVector3 m_objectPosition;

	//  Object rotation speed (degrees per second)
	double m_rotationSpeed;
};

#endif // !CAPPEMPTY_H