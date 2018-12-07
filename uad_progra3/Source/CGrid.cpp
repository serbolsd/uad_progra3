#include "../Include/CGrid.h"
#include "../stdafx.h"

#include <iostream>
using namespace std;

#include "../Include/Globals.h"
#include "../Include/CAppEmpty.h"
#include "../Include/CWideStringHelper.h"

CGrid::CGrid():
CApp(CGameWindow::DEFAULT_WINDOW_WIDTH, CGameWindow::DEFAULT_WINDOW_HEIGHT)
{

}
CGrid::CGrid(int window_width, int window_height) :
	CApp(window_width, window_height)
{

	m_currentDeltaTime = 0;
	m_objectRotation = 0;
	m_rotationSpeed = 0;
	m_rotationSpeed = 90;

	m_objectPosition = CVector3::ZeroVector();

	cout << "Constructor: Cgeomretria (int window_width, int window_height)" << endl;

	// Initialize class member variables here
	// ======================================
	//
	// ======================================
}

CGrid::~CGrid()
{
}

void CGrid::initialize()
{
	// Initialize app-specific stuff here
	// ==================================
	//
	// ==================================

	std::wstring wresourceFilenameVS;
	std::wstring wresourceFilenameFS;
	std::string resourceFilenameVS;
	std::string resourceFilenameFS;

	char *vertexShaderToLoad = VERTEX_SHADER_3D_OBJECT;
	char *fragmentShaderToLoad = FRAGMENT_SHADER_3D_OBJECT;

	if (!CWideStringHelper::GetResourceFullPath(vertexShaderToLoad, wresourceFilenameVS, resourceFilenameVS) ||
		!CWideStringHelper::GetResourceFullPath(fragmentShaderToLoad, wresourceFilenameFS, resourceFilenameFS))
	{
		cout << "ERROR: Unable to find one or more resources: " << endl;
		cout << "  " << vertexShaderToLoad << endl;
		cout << "  " << fragmentShaderToLoad << endl;

		m_initialized = false;
	}

	getOpenGLRenderer()->createShaderProgram(
		&m_celda.m_shaderID,
		resourceFilenameVS.c_str(),
		resourceFilenameFS.c_str());

	if (m_celda.m_shaderID > 0)
	{
		//createPiramid();
		//createDona();
		//createEsfera();
		//createCubo();
		//createTorus();
		//hexagon();
		//hexgrid();
		createSavePositions();
		m_celda.paintHexa();

		m_celda.loaded = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
		&m_celda.m_shaderID,
		&m_celda.m_geoVAOID,
			m_celda.vdata,			// Vertices
		14,				// Num Vertices
			m_celda.nData,			// normales
		24,				// num normales
			m_celda.vdata,			// UV coords
		14,				// num UV coords
			m_celda.vIndices,		// Indices a vertices
		24,				// num tri
			m_celda.nIndice,		// Indices a normales
		24,				// num indices a normales
			m_celda.vIndices,		// Indices a UV Coords
		24);				// num indices a UV coords
		if (!m_celda.loaded)
			m_celda.m_geoVAOID = 0;
	};
}

void CGrid::run()
{
	//initialize(); si se inicializa antes de crear la ventana clashea

	// Check if CGameWindow object AND Graphics API specific Window library have been initialized
	if (canRun())
	{
		// Create the Window 
		if (getGameWindow()->create(CAPP_PROGRA3_EMPTYAPP_WINDOW_TITLE))
		{
			// Set initial clear screen color
			getOpenGLRenderer()->setClearScreenColor(0.25f, 0.0f, 0.75f);
			getOpenGLRenderer()->setCameraDistance(15.0f);
			// Initialize window width/height in the renderer
			getOpenGLRenderer()->setWindowWidth(getGameWindow()->getWidth());
			getOpenGLRenderer()->setWindowHeight(getGameWindow()->getHeight());

			//se tiene que poner antes del main loop
			initialize();

			// Enter main loop
			cout << "Entering Main loop" << endl;
			getGameWindow()->mainLoop(this);
		}
	}
}

void CGrid::update(double deltaTime)
{
	// Do not update if delta time is < 0
	/*if (deltaTime <= 0.0f)
	{
	return;
	}*/
	//----------------------------------------------------------------------------------------------------------------------------------------------
	double degreesToRotate = 0.0;

	if (deltaTime <= 0.0f)
	{
		return;
	}

	// Save current delta time
	m_currentDeltaTime = deltaTime;

	// Calculate degrees to rotate
	// ----------------------------------------------------------------------------------------------------------------------------------------
	// degrees = rotation speed * delta time 
	// deltaTime is expressed in milliseconds, but our rotation speed is expressed in seconds (convert delta time from milliseconds to seconds)
	//degreesToRotate = m_rotationSpeed * (deltaTime / 1000.0);
	// accumulate rotation degrees
	m_objectRotation += degreesToRotate;

	// Reset rotation if needed
	while (m_objectRotation > 360.0)
	{
		m_objectRotation -= 360.0;
	}
	if (m_objectRotation < 0.0)
	{
		m_objectRotation = 0.0;
	}
	//----------------------------------------------------------------------------------------------------------------------------------------------

	// Update app-specific stuff here
	// ===============================
	//
	// ===============================
}

void CGrid::render()
{
	CGameMenu *menu = getMenu();
	if (menu != NULL && menu->isInitialized() && menu->isActive())
	{
		menu->render(getOpenGLRenderer());
	}
	else // Otherwise, render active object if loaded (or test cube if no object is loaded)
	{
		// White 
		// Colors are in the 0..1 range, if you want to use RGB, use (R/255, G/255, G/255)
		unsigned int noTexture = 0;
		
		//int filas = 10;
		//int columnas = 10;
		float totalTamañoX = incrementoX * columnas;
		float totalTamañoY = incrementoY * filas;
		float inicialX = (totalTamañoX / 2) - totalTamañoX;
		float inicialY = (totalTamañoY / 2) - totalTamañoY;
		int count = 0;
		float colorR = 7;
		float colorG = 102;
		float colorB = 204;
		//colorR=((float)rand() / RAND_MAX) * (255 - 0) + 0;
		//colorG=((float)rand() / RAND_MAX) * (255 - 0) + 0;
		//colorB=((float)rand() / RAND_MAX) * (255 - 0) + 0;
		float color[3];
		float color1[3] = { colorR + 100,colorG - 50,colorB - 100 };
		float color2[3] = { colorR,colorG,colorB };


		double totalDegreesRotatedRadians = m_objectRotation * 3.1459 / 180.0;
		for (float i = inicialY; i < totalTamañoY / 2 - 1; i += incrementoY)
		{
			for (float j = inicialX; j < totalTamañoX / 2 - 1; j += incrementoX)
			{

				if ((count % 2) != 0)
				{
					m_objectPosition.Y = i;
					m_objectPosition.X = j + incrementoX2;
					color[0] = color1[0];
					color[1] = color1[1];
					color[2] = color1[2];
				}
				else
				{
					m_objectPosition.Y = i;
					m_objectPosition.X = j;
					color[0] = color2[0];
					color[1] = color2[1];
					color[2] = color2[2];
				}
				MathHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix((float)totalDegreesRotatedRadians, m_objectPosition);
				if (m_celda.m_geoVAOID > 0 && m_celda.m_numFacesToRender)
				{
					getOpenGLRenderer()->renderObject(
						&m_celda.m_shaderID,
						&m_celda.m_geoVAOID,
						&noTexture,
						m_celda.m_numFacesToRender,
						color,
						&modelMatrix,
						COpenGLRenderer::EPRIMITIVE_MODE::TRIANGLES,
						false
					);
				}
			}
			count++;
		}

	}
}

void CGrid::paintGrid()
{
	int numcell=0;
	for (float i = inicialY; i < totalTamañoY / 2 - 1; i += incrementoY)
	{
		for (float j = inicialX; j < totalTamañoX / 2 - 1; j += incrementoX)
		{

			if ((count % 2) != 0)
			{
				m_objectPosition.Y = i;
				m_objectPosition.X = j + incrementoX2;
				color[0] = color1[0];
				color[1] = color1[1];
				color[2] = color1[2];
			}
			else
			{
				m_objectPosition.Y = i;
				m_objectPosition.X = j;
				color[0] = color2[0];
				color[1] = color2[1];
				color[2] = color2[2];
			}
			MathHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix((float)totalDegreesRotatedRadians, m_objectPosition);
			if (m_celda.m_geoVAOID > 0 && m_celda.m_numFacesToRender)
			{
				getOpenGLRenderer()->renderObject(
					&m_celda.m_shaderID,
					&m_celda.m_geoVAOID,
					&noTexture,
					m_celda.m_numFacesToRender,
					color,
					&modelMatrix,
					COpenGLRenderer::EPRIMITIVE_MODE::TRIANGLES,
					false
				);
			}
			m_cellPosition[numcell][0]= m_objectPosition.X;
			m_cellPosition[numcell][1]= m_objectPosition.Y;
			m_cellPosition[numcell][2]= 0.0;
			numcell++;
		}
		count++;
	}
}

void CGrid::createSavePositions()
{
	m_cellPosition = new float*[filas*columnas];
	for (int i = 0; i < filas*columnas; i++)
	{
		m_cellPosition[i] = new float[3];
	}
}

void CGrid::SavePositions(vector<CVector3> &vec)
{
	int linea = 0;
	for (float i = inicialY; i < (totalTamañoY/2)-1; i+=incrementoY)
	{
		for (float j = inicialX; j < (totalTamañoX / 2) - 1; j += incrementoX)
		{
			if (count%2 != 0)
			{
				m_vecForSavePosition.Y = i;
				m_vecForSavePosition.X = (j+incrementoX2);
			}
			else
			{
				m_vecForSavePosition.Y = i;
				m_vecForSavePosition.X = (j);

			}
			CVector3 forsave = m_vecForSavePosition;
			vec.push_back(forsave);
		}
		linea++;
	}
}