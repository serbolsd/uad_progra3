#include "../Include/figuras_geometricas.h"

#include "../stdafx.h"

#include <iostream>
using namespace std;

#include "../Include/Globals.h"
#include "../Include/CAppEmpty.h"
#include "../Include/CWideStringHelper.h"
#define PI 3.14159265358979323846
/* */
Cgeomretria ::Cgeomretria () :
	CApp(CGameWindow::DEFAULT_WINDOW_WIDTH, CGameWindow::DEFAULT_WINDOW_HEIGHT)
{
	m_geoVAOID = 0;
	m_shaderID = 0;

	m_currentDeltaTime = 0;
	m_objectRotation = 0;
	m_rotationSpeed = 90;

	m_objectPosition = CVector3::ZeroVector();

	cout << "Constructor: Cgeomretria ()" << endl;

	// Initialize class member variables here
	// ======================================
	//
	// ======================================
}

/* */
Cgeomretria ::Cgeomretria (int window_width, int window_height) :
	CApp(window_width, window_height)
{
	m_geoVAOID = 0;
	m_shaderID = 0;

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

/* */
Cgeomretria ::~Cgeomretria ()
{
	cout << "Destructor: ~Cgeomretria ()" << endl;

	// Free memory allocated in this class instance here
	// =================================================
	//
	// =================================================
	if (m_geoVAOID)
	{
		getOpenGLRenderer()->freeGraphicsMemoryForObject(&m_shaderID, &m_geoVAOID);
	}
}

/* */
void Cgeomretria ::initialize()
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
		&m_shaderID,
		resourceFilenameVS.c_str(),
		resourceFilenameFS.c_str());

	if (m_shaderID > 0)
	{
		//createPiramid();
		//createDona();
		//createEsfera();
		//createCubo();
		createTorus();
	}
}

/* */
void Cgeomretria ::run()
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

/* */
void Cgeomretria ::update(double deltaTime)
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
	degreesToRotate = m_rotationSpeed * (deltaTime / 1000.0);
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

/* 
void Cgeomretria ::render()
{
	CGameMenu *menu = getMenu();

	// If menu is active, render menu
	if (menu != NULL
		&& menu->isInitialized()
		&& menu->isActive())
	{
		//...
	}
	else // Otherwise, render app-specific stuff here...
	{
		// =================================
		//
		// =================================
	}
}*/

/* */
void Cgeomretria ::onMouseMove(float deltaX, float deltaY)
{
	// Update app-specific stuff when mouse moves here 
	// ===============================================
	//
	// ===============================================
}

/* */
void Cgeomretria ::executeMenuAction()
{
	if (getMenu() != NULL)
	{
		// Execute app-specific menu actions here
		// ======================================
		//
		// ======================================
	}
}

void Cgeomretria ::createPiramid()
{
	bool loaded = false;

	float h = 2.5f;
	float halfz = 1.0f;
	float halfx = 1.0f;
	float v1v3[3], v1v2[2],normal[3];

	m_numFacesToRender = 6;

	float vdata[15] = {
						 0.0  , h  , 0.0,//1
						-halfx, 0.0, halfz,//2
						 halfx, 0.0, halfz,//3
						-halfx, 0.0,-halfz,//4
						 halfx, 0.0,-halfz,//5
						};
	//son 18 por que cada triangulo tiene 3 vertices, y en una piramide hay 6 triangulos
	unsigned short vIndice[18]={
							0,2,4,
							0,4,3,
							0,3,1,
							1,4,2,
							1,3,4,
							0,1,2,
							};
	// la "n" es de normales
	float nData[18]={
					0.0,0.0,0.0,
					0.0,0.0,0.0,
					0.0,0.0,0.0,
					0.0,0.0,0.0,
					0.0,0.0,0.0,
					0.0,0.0,0.0
					};
	unsigned short nIndice[18]={
						0,0,0,
						1,1,1,
						2,2,2,
						3,3,3,
						4,4,4,
						5,5,5
				       };

	loaded = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
																  	&m_shaderID,
																  	&m_geoVAOID,
																  	vdata,  // vertices
																  	5,		// Nunmero de vertices del 0 al 5 por que son 6
																  	nData,	// Normales
																  	6,		// Numero de normales
																  	vdata,	// UV coords
																  	5,		// Num Uv coords
																  	vIndice,// Indices a vertices
																  	6,		// Num de tris
																  	nIndice,// Indices a normales
																  	6,		// Num de normales
																  	vIndice,// Indices a UV coords
																  	6		// Num de UV coords
																  );
}

void Cgeomretria::render()
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
		float color[3] = { 115.0f, 8.0f, 165.0f };
		unsigned int noTexture = 0;


		// convert total degrees rotated to radians;
		double totalDegreesRotatedRadians = m_objectRotation * 3.1459 / 180.0;

		// Get a matrix that has both the object rotation and translation
		MathHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix((float)totalDegreesRotatedRadians, m_objectPosition);
		if (m_geoVAOID > 0 && m_numFacesToRender)
		{
			getOpenGLRenderer()->renderObject(
				&m_shaderID,
				&m_geoVAOID,
				&noTexture,
				m_numFacesToRender,
				color,
				&modelMatrix,
				COpenGLRenderer::EPRIMITIVE_MODE::TRIANGLES,
				false
			);
		};
	}
}

void Cgeomretria::createDona()
{
	bool loaded = false;

	float h = 3.0f;
	float halfz = 0.5f;
	float halfx = 1.0f;
	float v1v3[3], v1v2[2], normal[3];

	m_numFacesToRender = 48;
	//son 24 vertices, 24 x 3 (los tris) =72
	float vdata[72] = {
		//X				,	Y	 ,	Z
		-halfx			, h		 , halfz,	//1
		 halfx			, h		 , halfz,	//2
		(-halfx-halfx/2), h/2	 , halfz,	//3
		 (halfx+halfx/2), h/2	 , halfz,	//4
		 -halfx			, 0.0	 , halfz,	//5
		 halfx			, 0.0	 , halfz,	//6

		-halfx			, (h-h/4), halfz,	//7
		 halfx			, (h-h/4), halfz,	//8
		(-halfx-halfx/4), h/2	 , halfz,	//9-----
		 (halfx+halfx/4), h/2    , halfz,	//10-----
		-halfx			, h/4	 , halfz,	//11
		 halfx			, h/4	 , halfz,	//12


		-halfx			, h		 ,-halfz,	//13
		 halfx			, h		 ,-halfz,	//14
		-halfx-(halfx/2), h / 2	 ,-halfz,	//15
		 halfx+(halfx/2), h / 2	 ,-halfz,	//16
		-halfx			, 0.0	 ,-halfz,	//17
		 halfx			, 0.0	 ,-halfz,	//18

		-halfx			, (h-h/4),-halfz,	//19
		 halfx			, (h-h/4),-halfz,	//20
		(-halfx-halfx/4), h / 2	 ,-halfz,	//21----
		 (halfx+halfx/4), h / 2  ,-halfz,	//22----
		-halfx			, h / 4	 ,-halfz,	//23
		 halfx			, h / 4	 ,-halfz	//24

	};
	//son 18 por que cada triangulo tiene 3 vertices, y en una piramide hay 6 triangulos
	unsigned short vIndice[144] = {
		//En frente
		0,6,7,//1
		0,7,1,

		1,7,9,//2
		1,9,3,

		3,9,11,//3
		3,11,5,

		5,11,10,//4
		5,10,4,

		4,10,8,//5
		4,8,2,

		2,8,6,//6
		2,6,0,

		//arriba
		0,1,13,//1
		0,13,12,

		1,3,15,//2
		1,15,13,

		3,5,17,//3
		3,17,15,

		5,4,16,//4
		5,16,17,

		4,2,14,//5
		4,14,16,

		2,0,12,//6
		2,12,14,

		//EN MEDIO
		18,19,7,//5
		18,7,6,//6

		19,9,7,//13
		19,21,9,//14----

		21,11,9,//33-------
		21,23,11,//34------

		23,10,11,//35
		23,22,10,//36

		22,8,10,//37
		22,20,8,//38----

		20,6,8,//39----
		20,18,6,//40---


		//ATRAS
		18,13,12,//7
		18,19,13,//8

		19,15,13,//15
		19,21,15,//16-----

		21,17,15,//41-----
		21,23,17,//42-----

		23,16,17,//43
		23,22,16,//44

		22,14,16,//45
		22,20,14,//46

		20,12,14,//47
		20,18,12,//48
	};
	// la "n" es de normales
	float nData[144] = {
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0
	};
	unsigned short nIndice[144] = {
		0,0,0,
		1,1,1,
		2,2,2,
		3,3,3,
		4,4,4,
		5,5,5,
		6,6,6,
		7,7,7,
		8,8,8,
		9,9,9,
		10,10,10,
		11,11,11,
		12,12,12,
		13,13,13,
		14,14,14,
		15,15,15,
		16,16,16,
		17,17,17,
		18,18,18,
		19,19,19,
		20,20,20,
		21,21,21,
		22,22,22,
		23,23,23,
		24,24,24,
		25,25,25,
		26,26,26,
		27,27,27,
		28,28,28,
		29,29,29,
		30,30,30,
		31,31,31,
		32,32,32,
		33,33,33,
		34,34,34,
		35,35,35,
		36,36,36,
		37,37,37,
		38,38,38,
		39,39,39,
		40,40,40,
		41,41,41,
		42,42,42,
		43,43,43,
		44,44,44,
		45,45,45,
		46,46,46,
		47,47,47
	};

	loaded = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
		&m_shaderID,
		&m_geoVAOID,
		vdata,  // vertices
		24,		// Nunmero de vertices del 0 al 5 por que son 6
		nData,	// Normales
		48,		// Numero de normales
		vdata,	// UV coords
		24,		// Num Uv coords
		vIndice,// Indices a vertices
		48,		// Num de tris
		nIndice,// Indices a normales
		48,		// Num de normales
		vIndice,// Indices a UV coords
		48		// Num de UV coords
	);
}

void Cgeomretria::createEsfera()
{
	bool loaded = false;
	//cosas modificables
	int nLineasHorizontales = 5;
	int nLineasVerticales = 7;
	float radio = 1.0f;
	//calculos para caras, vertices, angulos y tries
	int nCarasVerticales = nLineasHorizontales+1;
	int nCarasHorizontales = nLineasVerticales - 1;
	int nVertices = (((nLineasHorizontales*(nLineasVerticales-1)) * 2) + 2);
	int nTries = (((nCarasVerticales - 2)*nCarasHorizontales)*2)*2 + (nCarasHorizontales * 4);

	float *vdata = new float[nVertices*3];
	float anguloY = 360/(nCarasVerticales*2);			//se calcula el angulo entre las caras de arria hacia abajo (las caras verticales)
	float anguloXZ = 360 / (nCarasHorizontales * 2);	//se calcula el angulo entre las caras horizontales

	//funciones para la creacion
	void esferaVertices(int **&vertices, float anguloY, float anguloXZ, float radio, float *&vdata);
	void esferaAcomodoTries(unsigned short *&vIndice, int **vertices, int nLineasHorizontales,int nLineasVerticales);
	//colo las caras a renderiar
	m_numFacesToRender = nTries;


	int **vertices = new int *[nLineasHorizontales+2];	//para llevar un registro del indice del vertice que se creo
	for (int i = 0; i < nLineasHorizontales + 2; i++)
	{
		vertices[i] = new int[((nLineasVerticales-1)*2)+1];
	}
	// para poder saber cuando se tienen que tomar los primeros vertices pongo un numero que de apoyo
	for (int i = 0; i < nLineasHorizontales + 2; i++)
	{
		for (int j = 0; j < ((nLineasVerticales - 1) * 2)+1;j++)
		{
			vertices[i][j] = -1;
		}

	}

	esferaVertices(vertices,anguloY,anguloXZ,radio,vdata);//se crea la pocioncion de los vertices y se registra su indice

	unsigned short *vIndice = new unsigned short[nTries*3];

	esferaAcomodoTries(vIndice,vertices,nLineasHorizontales,nLineasVerticales);//acomoda los tris utilizando los indices antes registrados

	float *nData = new float [nTries * 3];//coloco normales en 0
	for (int i = 0; i < nTries*3; i++)
	{
		nData[i] = 0.0;
	}

	int indice = 0;
	unsigned short *nIndice = new unsigned short[nTries * 3];//agrego los indices por tri
	for (int i = 0; i < nTries*3; i++)
	{
		nIndice[i] = indice;
		i++;
		nIndice[i] = indice;
		i++;
		nIndice[i] = indice;
		indice++;
	}


	loaded = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
		&m_shaderID,
		&m_geoVAOID,
		vdata,  // vertices
		nVertices,		// Nunmero de vertices de la figura
		nData,	// Normales
		nTries,		// Numero de normales
		vdata,	// UV coords
		nVertices,		// Num Uv coords
		vIndice,// Indices a vertices
		nTries,		// Num de tris
		nIndice,// Indices a normales
		nTries,		// Num de normales
		vIndice,// Indices a UV coords
		nTries		// Num de UV coords
	);
	delete[] vertices;
	delete vdata;
	delete nData;
	delete vIndice;
	delete nIndice;
}

void Cgeomretria::createCubo()
{
	m_numFacesToRender = 12;
	bool loaded = false;
	float h = 2.0f;
	float halfx = 1.0f;
	float halfz = 1.0f;
	float v1V3[3], v1V2[3], normal[3];

	// Vertices
	float vData[24] = {
		// Abajo
		halfx, 0.0, halfz, // Vertice 0, porque esta en el suelo y la altura es 0
		halfx, 0.0, -halfz, // Vertice 1
		-halfx, 0.0, halfz, // Vertice 2
		-halfx, 0.0, - halfz, // Vertice 3
							 // Arriba
							 halfx, h, halfz,		// Vertice 4
							 halfx, h, -halfz,		// Vertice 5
							 -halfx, h, halfz,		// Vertice 6
							 -halfx, h, -halfz		// Vertice 7



	};

	// Se definen los vertices 12 (Numtringulos) x 3 (num Vertices de un tringulo) = 36 indices
	unsigned short vIndices[36] = {
		// Cara base inferior
		1,2,3,
		1,0,2,

		// Cara 1
		0,6,2,
		0,4,6,

		// Cara 2
		1,4,0,
		1,5,4,

		// Cara 3
		3,5,1,
		3,7,5,

		// Cara 4
		2,7,3,
		2,6,7,

		// Cara Base Superior
		4,7,6,
		4,5,7
	};

	// Se definen las normales
	float nData[36] = {
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0,
		0.0,0.0,0.0
	};
	// Se difinen los indices (identificadores)
	unsigned short nIndices[36] = {
		0.0,0.0,0.0,	// Primer indice
		1.0,1.0,1.0,	// Segundo indice
		2.0,2.0,2.0,
		3.0,3.0,3.0,
		4.0,4.0,4.0,
		5.0,5.0,5.0,
		6.0,6.0,6.0,
		7.0,7.0,7.0,
		8.0,8.0,8.0,
		9.0,9.0,9.0,
		10.0,10.0,10.0,
		11.0,11.0,11.0
	};

	loaded = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
		&m_shaderID,
		&m_geoVAOID,
		vData,			// Vertices
		8,				// Num Vertices
		nData,			// normales
		12,				// num normales
		vData,			// UV coords
		8,				// num UV coords
		vIndices,		// Indices a vertices
		12,				// num tri
		nIndices,		// Indices a normales
		12,				// num indices a normales
		vIndices,		// Indices a UV Coords
		12);				// num indices a UV coords
	if (!loaded)
		m_geoVAOID = 0;
}


void Cgeomretria::createTorus()
{
	bool loaded = false;
	//cosas modifivables
	int nLineasHorizontales = 6;//se cuentan solo las que se tienen engfrete, despues se hace un calculo para sacar las de atras
	int nLineasVerticales = 10;//en total las lineas verticales de la figura puesta como un tubo
	float Rinterno = 0.5f;//radio para el circulo interno de la figura
	float Rexterno = 1.0f;//radio del punto medio de donde se quiere centrar la figura hasta el borde interior de la figura
	float Rtotal = Rexterno + (2 * Rinterno);//radio del punto medio de donde se quiere centrar la figura hasta el borde exterior de la figura
	float Rsemi = Rexterno + Rinterno;//radio del punto medio de donde se quiere centrar la figura hasta el punto medio del circulo interno de la figura
	//calculos para caras, vertices, angulos y tries 
	int nCarasHorizontales = nLineasVerticales;
	int nCarasVerticales = (nLineasHorizontales - 1) * 2;
	int nVertices = nCarasHorizontales * nCarasVerticales;
	int nCarasTotoales = nCarasHorizontales*nCarasVerticales;
	int nTries = nCarasTotoales * 2;

	float anguloY = 360 / nCarasHorizontales;
	float anguloXZ = 360 / nCarasVerticales;

	//funciones para la creacion;
	void torusVertices(int **&vertices, float anguloY, float anguloXZ, float Rinterno,float Rsemi,float *&vdata);
	void torusAcomodoTries(unsigned short *&vIndice, int **vertices, int nCarasHorizontales, int nCarasVerticales);
	//colo el numero de caras a renderiar
	m_numFacesToRender = nTries;

	void desmadre(int **&vertices);

	int **vertices = new int *[nCarasHorizontales+1];//para el registro del indice de los vertices
	for (int i = 0; i < nCarasHorizontales+1; i++)
	{
		vertices[i] = new int[nCarasVerticales + 1];
	}
	//para tener un numero de referencia del limite de los vertices
	for (int i = 0; i < nCarasHorizontales+1; i++)
	{
		for (int j = 0; j < nCarasVerticales+1; j++)
		{
			vertices[i][j] = -1;
		}
	}

	float *vdata = new float[nVertices * 3];
	torusVertices(vertices,anguloY,anguloXZ,Rinterno,Rsemi,vdata);

	
	unsigned short *vIndice = new unsigned short[nTries*3];
	torusAcomodoTries(vIndice,vertices,nCarasHorizontales,nCarasVerticales);

	// la "n" es de normales
	float *nData = new float[nTries*3];
	for (int i = 0; i < nTries*3; i++)
	{
		nData[i] = 0.0;
	}
	
	int indice = 0;
	unsigned short *nIndice = new unsigned short[nTries*3];
	for (int i = 0; i < nTries*3; i++)
	{
		nIndice[i] = indice;
		i++;
		nIndice[i] = indice;
		i++;
		nIndice[i] = indice;
		indice++;
	}
	

	loaded = getOpenGLRenderer()->allocateGraphicsMemoryForObject(
		&m_shaderID,
		&m_geoVAOID,
		vdata,  // vertices
		nVertices,		// Nunmero de vertices 
		nData,	// Normales
		nTries,		// Numero de normales
		vdata,	// UV coords
		nVertices,		// Num Uv coords
		vIndice,// Indices a vertices
		nTries,		// Num de tris
		nIndice,// Indices a normales
		nTries,		// Num de normales
		vIndice,// Indices a UV coords
		nTries		// Num de UV coords
	);
	delete vdata;
	delete[] vertices;
	delete nData;
	delete vIndice;
	delete nIndice;
}


void esferaVertices(int **&vertices, float anguloY, float anguloXZ, float radio, float *&vdata)
{
	float avanceY = anguloY;
	float avanceXZ = anguloXZ;

	int nVertice = 0;
	float verticeX = 0, verticeY = 0, verticeZ = 0;

	int fila = 0;
	int columna = 0;
	int numero = 0;
	for (float i = 0; i < 181; i += avanceY)
	{
		for (float j = 0; j < 360; j += avanceXZ)
		{

			verticeX = radio * sin(j / (180 / PI))*sin(i / (180 / PI));
			vdata[nVertice] = verticeX;
			nVertice++;
			verticeY = radio * cos(i / (180 / PI));
			vdata[nVertice] = verticeY;
			nVertice++;
			verticeZ = radio * cos(j / (180 / PI))*sin(i / (180 / PI));
			vdata[nVertice] = verticeZ;
			nVertice++;
			vertices[fila][columna] = numero;
			numero++;
			if (i == 0 || i == 180)
			{
				break;
			}
			columna++;
			//vertice[0] = radio * cos((i + 1)*inct)*cos(j*incf - 0.5*pi);
			//vertice[1] = radio * sin((i + 1)*inct)*cos(j*incf - 0.5*pi);
		}
		fila++;
		columna = 0;
	}
}
void esferaAcomodoTries(unsigned short *&vIndice, int **vertices, int nLineasHorizontales, int nLineasVerticales)
{
	int contador = 0;
	for (int i = 0; i < nLineasHorizontales + 1; i++)
	{
		for (int j = 0; j < ((nLineasVerticales - 1) * 2); j++)
		{
			if (i == 0)
			{
				vIndice[contador] = unsigned short(vertices[i][0]);
				contador++;
				vIndice[contador] = unsigned short(vertices[i + 1][j]);
				contador++;
				if (vertices[i + 1][j + 1] == -1)
				{
					vIndice[contador] = unsigned short(vertices[i + 1][0]);
					contador++;
				}
				else
				{
					vIndice[contador] = unsigned short(vertices[i + 1][j + 1]);
					contador++;
				}
			}
			else if (i == nLineasHorizontales)
			{
				vIndice[contador] = unsigned short(vertices[i + 1][0]);
				contador++;
				if (vertices[i][j + 1] == -1)
				{
					vIndice[contador] = unsigned short(vertices[i][0]);
					contador++;
				}
				else
				{
					vIndice[contador] = unsigned short(vertices[i][j + 1]);
					contador++;
				}
				vIndice[contador] = unsigned short(vertices[i][j]);
				contador++;
			}
			else if (i == nLineasHorizontales + 1)
			{
				break;
			}
			else
			{
				vIndice[contador] = unsigned short(vertices[i + 1][j]);
				contador++;
				if (vertices[i][j + 1] == -1)
				{
					vIndice[contador] = unsigned short(vertices[i][0]);
					contador++;
				}
				else
				{
					vIndice[contador] = unsigned short(vertices[i][j + 1]);
					contador++;
				}
				vIndice[contador] = unsigned short(vertices[i][j]);
				contador++;

				vIndice[contador] = unsigned short(vertices[i + 1][j]);
				contador++;
				if (vertices[i + 1][j + 1] == -1)
				{
					vIndice[contador] = unsigned short(vertices[i + 1][0]);
					contador++;
				}
				else
				{
					vIndice[contador] = unsigned short(vertices[i + 1][j + 1]);
					contador++;
				}
				if (vertices[i][j + 1] == -1)
				{
					vIndice[contador] = unsigned short(vertices[i][0]);
					contador++;
				}
				else
				{
					vIndice[contador] = unsigned short(vertices[i][j + 1]);
					contador++;
				}
			}

		}

	}
}

void torusVertices(int **&vertices, float anguloY, float anguloXZ, float Rinterno, float Rsemi, float *&vdata)
{
	int numero = 0;
	int fila = 0;
	int columna = 0;

	float verticeX = 0.0f;
	float verticeY = 0.0f;
	float verticeZ = 0.0f;
	float pi = PI;
	int nV = 0;
	for (int i = 0; i < 360; i += anguloY)
	{
		for (int j = 0; j < 360; j += anguloXZ)
		{
			//separado para probar paso por paso los resultados
			verticeX = (Rinterno*sin(j / (180 / pi)));
			verticeX += Rsemi;
			verticeX = verticeX * sin((i / (180 / pi)));
			vdata[nV] = verticeX;
			nV++;

			verticeY = (Rinterno*sin((j / (180 / pi))));
			verticeY += Rsemi;
			verticeY = verticeY * cos((i / (180 / pi)));
			vdata[nV] = verticeY;
			nV++;

			verticeZ = Rinterno * cos((j / (180 / pi)));
			vdata[nV] = verticeZ;
			nV++;

			vertices[fila][columna] = numero;//registro el indice
			numero++;
			columna++;
		}
		fila++;
		columna = 0;
	}

}
void torusAcomodoTries(unsigned short *&vIndice, int **vertices, int nCarasHorizontales, int nCarasVerticales)
{
	int contadorIndice = 0;
	for (int i = 0; i < nCarasHorizontales; i++)
	{
		for (int j = 0; j < nCarasVerticales; j++)
		{
			vIndice[contadorIndice] = unsigned short(vertices[i][j]);
			contadorIndice++;

			if (vertices[i + 1][j + 1] == -1)
			{
				if (i == nCarasHorizontales - 1)
				{
					if (vertices[0][j + 1] == -1)
					{
						vIndice[contadorIndice] = unsigned short(vertices[0][0]);
					}
					else
					{
						vIndice[contadorIndice] = unsigned short(vertices[0][j + 1]);
					}
					contadorIndice++;
				}
				else
				{
					vIndice[contadorIndice] = unsigned short(vertices[i + 1][0]);
					contadorIndice++;
				}
			}
			else
			{
				vIndice[contadorIndice] = unsigned short(vertices[i + 1][j + 1]);
				contadorIndice++;
			}

			if (vertices[i + 1][j] == -1)
			{
				if (i == nCarasHorizontales - 1)
				{
					vIndice[contadorIndice] = unsigned short(vertices[0][j]);
					contadorIndice++;
				}
				else
				{
					vIndice[contadorIndice] = unsigned short(vertices[i + 1][0]);
					contadorIndice++;
				}
			}
			else
			{
				vIndice[contadorIndice] = unsigned short(vertices[i + 1][j]);
				contadorIndice++;
			}


			vIndice[contadorIndice] = unsigned short(vertices[i][j]);
			contadorIndice++;

			if (vertices[i][j + 1] == -1)
			{
				if (i == nCarasHorizontales - 1)
				{
					vIndice[contadorIndice] = unsigned short(vertices[i][0]);
					contadorIndice++;
				}
				else
				{
					vIndice[contadorIndice] = unsigned short(vertices[i][0]);
					contadorIndice++;
				}
			}
			else
			{
				vIndice[contadorIndice] = unsigned short(vertices[i][j + 1]);
				contadorIndice++;
			}

			if (vertices[i + 1][j + 1] == -1)
			{
				if (i == nCarasHorizontales - 1)
				{
					if (vertices[0][j + 1] == -1)
					{
						vIndice[contadorIndice] = unsigned short(vertices[0][0]);
					}
					else
					{
						vIndice[contadorIndice] = unsigned short(vertices[0][j + 1]);
					}
					contadorIndice++;
				}
				else
				{
					vIndice[contadorIndice] = unsigned short(vertices[i + 1][0]);
					contadorIndice++;
				}
			}
			else
			{
				vIndice[contadorIndice] = unsigned short(vertices[i + 1][j + 1]);
				contadorIndice++;
			}


		}

	}
}