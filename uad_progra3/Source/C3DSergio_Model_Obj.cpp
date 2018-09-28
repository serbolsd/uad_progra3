#include "../stdafx.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include "../Include/C3DModel.h"
#include "../Include/C3DSergio_Model_Obj.h"

/*
*/
C3DSergio_Model_Obj::C3DSergio_Model_Obj() :
	C3DModel(),
	m_currentVertex(0),
	m_currentNormal(0),
	m_currentUV(0),
	m_currentFace(0)
{
	cout << "Constructor: C3DSergio_Model_Obj()" << endl;
}

/*
*/
C3DSergio_Model_Obj::~C3DSergio_Model_Obj()
{
	cout << "Destructor: C3DSergio_Model_Obj()" << endl;
	resetobjs();
	m_objetos.clear();
}

/*
*/
void C3DSergio_Model_Obj::reset()
{
	C3DModel::resetobjs();
	C3DModel::reset();

	m_currentVertex = 0;
	m_currentNormal = 0;
	m_currentUV = 0;
	m_currentFace = 0;
}
void C3DSergio_Model_Obj::resetCurrents()
{
	m_currentVertex = 0;
	m_currentNormal = 0;
	m_currentUV = 0;
	m_currentFace = 0;
	m_obj.s_currentVertex = 0;
	m_obj.s_currentNormal = 0;
	m_obj.s_currentUV = 0;
	m_obj.s_currentFace = 0;
}
/*
*/
bool C3DSergio_Model_Obj::loadFromFile(const char * const filename)
{
	bool readFileOk = false;
	bool finishRead=false;
	int timeRead = 0;
	// Free any previous resources
	reset();
	// First pass is to count the number of vertices, normals, UVs, faces
	readFileOk = readObjFileMaya(filename, true, finishRead,timeRead);

	// Display count
	for (int i = 0; i < m_objetos.size(); i++)
	{
		cout << "Finished reading 3D model" << endl;
		cout << "Vertices: " << m_objetos[i].vVertices.size() / 3 << endl;
		cout << "Normals: " << m_objetos[i].vNormales.size()/3 << endl;
		cout << "UVCoords: " << m_objetos[i].vTexturas.size()/3 << endl;
		cout << "Faces: " << m_objetos[i].vFaces.size()/3 << endl;
	}

	if (readFileOk)
	{
		for (int i = 0; i < m_objetos.size(); i++)//sumo los numeros de todas las cosas
		{
			m_numVertices += m_objetos[i].vVertices.size()/3;
			m_numNormals += m_objetos[i].vNormales.size()/3;
			m_numUVCoords += m_objetos[i].vTexturas.size()/2;
			m_numFaces += (m_objetos[i].vFaces.size()/3)/3;
		}
		m_currentFace = m_numFaces;//calculo los current
		m_currentVertex = m_numVertices;
		m_currentNormal = m_numNormals;
		m_currentUV = m_numUVCoords;
		// Check for MAX number of faces
		if (m_numVertices >= 65535 || m_numNormals >= 65535 || m_numUVCoords >= 65535)
		{
			cout << "Error: object cannot have more than 65535 vertices" << endl;
			cout << "Object attempted to load has: " << m_numVertices << " vertices" << endl;
			return false;
		}

		// If model was read without normals or UVCoords, we'll set a default value for them
		// i.e.:
		//   0,0 for UV coords
		//   face normal for normal
		for (int i = 0; i < m_objetos.size(); i++)
		{
			if (m_objetos[i].vNormales.size() == 0)
			{
				m_objetos[i].s_modelHasNormals = false;
				m_objetos[i].vNormales.resize(m_objetos[i].vVertices.size());
			}
			else
			{
				m_objetos[i].s_modelHasNormals = true;
			}

			if (m_objetos[i].vTexturas.size() == 0)
			{
				m_objetos[i].vTexturas.resize(m_objetos[i].vVertices.size());
				m_objetos[i].s_modelHasUVs = false;
			}
			else
			{
				m_objetos[i].s_modelHasUVs = true;
			}
		}

		// Allocate memory for the arrays

		// C3DModel variables
		m_verticesRaw	 = new float[m_currentVertex*3];
		m_normalsRaw	 = new float[m_currentNormal*3];
		m_uvCoordsRaw	 = new float[m_currentUV*2];
		for (int i = 0; i < m_objetos.size(); i++)
		{
			m_objetos[i].s_vertexIndices = new unsigned short[(m_objetos[i].vFaces.size()/3)+3];//aqui acomo las caras para los indices dependiendo del objeto
			m_objetos[i].s_normalIndices = new unsigned short[(m_objetos[i].vFaces.size()/3)+3];
			m_objetos[i].s_UVindices	 = new unsigned short[(m_objetos[i].vFaces.size()/3)+3];

		}

		// Zero-out indices arrays
		for (int i = 0; i < m_objetos.size(); i++)
		{
			memset(m_objetos[i].s_vertexIndices, 0, sizeof(unsigned short) * ((m_objetos[i].vFaces.size() / 3)+3));//acomodo los indices en cero y agrego 3 para cuando haga el render
			memset(m_objetos[i].s_normalIndices, 0, sizeof(unsigned short) * ((m_objetos[i].vFaces.size() / 3)+3));
			memset(m_objetos[i].s_UVindices, 0, sizeof(unsigned short) * ((m_objetos[i].vFaces.size() / 3)+3));
		}
		memset(m_verticesRaw, 0, sizeof(float) * m_currentVertex * 3);
		memset(m_normalsRaw, 0, sizeof(float) * m_currentNormal * 3);
		memset(m_uvCoordsRaw, 0, sizeof(float) *m_currentUV * 2);
		
		int indexvertex = 0;
		int indexnormal = 0;
		int indexvUV = 0;
		//int indexvertex = 0;
		for (int i = 0; i <  m_currentVertex * 3; i++)//paso los todos los vertices
		{
			for (int j = 0; j <  m_objetos[indexvertex].vVertices.size(); j++)
			{
				m_verticesRaw[i] = (float)atof(m_objetos[indexvertex].vVertices[j].c_str());
				i++;
			}
			indexvertex++;
		}
		for (int i = 0; i < m_currentNormal * 3; i++)//paso los todas las normales
		{
			for (int j = 0; j < m_objetos[indexnormal].vNormales.size(); j++)
			{
				m_normalsRaw[i] = (float)atof(m_objetos[indexnormal].vNormales[j].c_str());
				i++;
			}
			indexnormal++;
		}
		for (int i = 0; i < m_currentUV * 2; i++)//paso los todas las texturas
		{
			for (int j = 0; j < m_objetos[indexvUV].vTexturas.size(); j++)
			{
				m_uvCoordsRaw[j] = (float)atof(m_objetos[indexvUV].vTexturas[j].c_str());
				i++;
			}
			m_currentUV++;
		}
		for (int i = 0; i < m_objetos.size(); i++)//separo los indices de vetices, normales y texturas
		{
			int index = 0;
			for (int j = 0; j < m_objetos[i].vFaces.size(); j++)
			{
				m_objetos[i].s_vertexIndices[index] = (float)atof(m_objetos[i].vFaces[j].c_str())-1;
				j++;
				m_objetos[i].s_UVindices[index] = (float)atof(m_objetos[i].vFaces[j].c_str())-1;
				j++;
				m_objetos[i].s_normalIndices[index] = (float)atof(m_objetos[i].vFaces[j].c_str())-1;
				index++;
			}
			readMtllibMaya(m_objetos[i].s_mtlLibFilename,m_objetos[i].s_materialName,m_objetos[i].s_materialFilename,i);


		}

		// Second pass is to read the data
		//readFileOk = readObjFileMaya(filename, false, finishRead, timeRead);
		
	}
	else
	{
		cout << "Error ocurred while reading 3D model." << endl;
	}

	if (readFileOk)
	{
		m_Initialized = true;

		if (!m_modelHasNormals)
		{
			computeFaceNormals();
		}
	}
	return readFileOk;
}

/*
*/
bool C3DSergio_Model_Obj::readObjFile(const char * filename, bool countOnly, bool &finishRead,int &timeRead)
{
	ifstream infile;
	string lineBuffer;
	bool readFileOk = true;
	bool AnotherObjet = false;
	int lineNumber = 0;
	int objectNumber = 0;
	int objectActual = 0;

	infile.open(filename);

	while (!infile.eof())
	{
		getline(infile, lineBuffer);
		lineNumber++;
		AnotherObjet = lineBuffer.find("# object");
		if (AnotherObjet)
		{
			resetCurrents();
			objectNumber++;
		}
		else if (AnotherObjet && objectNumber>0)
		{
			resetCurrents();
			m_objetos.push_back(m_obj);
			objectNumber++;
			objectActual++;
		}
		else
		{
			if (!(this->parseObjLine(lineBuffer, countOnly, lineNumber)))
			{
				readFileOk = false;
				break;
			}
		}
		// cout << lineBuffer << endl;
	}
	
	infile.close();

	return readFileOk;
}//no lo utilizo

bool C3DSergio_Model_Obj::readObjFileMaya(const char * filename, bool countOnly, bool &finishRead, int &timeRead)
{
	ifstream infile;
	string lineBuffer;
	bool readFileOk = true;
	bool AnotherObjectMaya = false;
	bool finishObjectMaya = false;
	bool finishObjectOBJ = false;
	bool isTwoFace = false;

	int anoetherObjetIndex = 0;
	int lineNumber = 0;
	int objectNumber = 0;
	int objectActual = 0;

	char *nextToken = NULL;
	char *token = NULL;
	char *twoToken = NULL;
	std::string tokenFace;
	std::vector<std::string> tokensVertices;
	std::vector<std::string> tokensNormales;
	std::vector<std::string> tokensTexturas;
	std::vector<std::string> numTokensTexturas;
	std::vector<std::string> tokensFaces;
	std::vector<std::string> tokensNumInFaces;

//	const char *delimiterToken = ' ';
	const char *delimiterFace = "/";

	infile.open(filename);

	while (!infile.eof())
	{
		getline(infile, lineBuffer);
		AnotherObjectMaya = lineBuffer.find("usemtl");
		anoetherObjetIndex= lineBuffer.find("usemtl");
		finishObjectOBJ = lineBuffer.find("# object");//asi se separan obj en archivos normales
		finishObjectMaya= lineBuffer.find("g default"),//asi se separan obj en archivos de maya
		token = strtok_s((char *)lineBuffer.c_str(), " \t", &nextToken);
		
		while (token!=NULL)
		{
			if (0==strcmp(token,"v"))//busca vertices
			{
				token = strtok_s(NULL, " \t", &nextToken);
				while (token!=NULL)
				{
					tokensVertices.push_back(std::string(token));//agrego los vertices a un vector en esta funcion
					token = strtok_s(NULL, " \t", &nextToken);
				}
			}
			else if (0==strcmp(token,"vn"))//busca normales
			{
				token = strtok_s(NULL, " \t", &nextToken);
				while (token != NULL)
				{
					tokensNormales.push_back(std::string(token));//agrego los normales a un vector en esta funcion
					token = strtok_s(NULL, " \t", &nextToken);
				}
			}
			else if (0 == strcmp(token, "vt"))//busca texturas
			{
				token = strtok_s(NULL, " \t", &nextToken);
				while (token != NULL)
				{
					numTokensTexturas.push_back(std::string(token));//las voy agregando a un vector de tokens especifico para contar las texturas
					token = strtok_s(NULL, " \t", &nextToken);
				}
				if (numTokensTexturas.size()<3)//si tiene solo 2 se agregan sin problema
				{
					tokensTexturas.push_back(numTokensTexturas[0]);
					tokensTexturas.push_back(numTokensTexturas[1]);
					//tokensTexturas.push_back("0.0");
				}
				else
				{
					tokensTexturas.push_back(numTokensTexturas[0]);// tiene 3 se agregan las primeras 2
					tokensTexturas.push_back(numTokensTexturas[1]);
					//tokensTexturas.push_back(numTokensTexturas[2]);
				}
				numTokensTexturas.clear();//limpio el vector de conteo para la siguiente vuelta
				
			}
			else if (0 == strcmp(token, "f"))//busca la faces
			{
				token = strtok_s(NULL, delimiterFace, &nextToken);
				while (token != NULL)
				{
					tokenFace = std::string(token);
					for (int i = 0; i < tokenFace.size(); i++)//reviso las caras
					{
						if (tokenFace[i]==' ')//separa las caras que estan por espacio, para que no se encimen partes de las faces
						{
							isTwoFace = true;
						}
					}
					if (isTwoFace)
					{
						twoToken = strtok((char *)tokenFace.c_str(), " \t");
						tokensNumInFaces.push_back(std::string(twoToken));
						twoToken = strtok(NULL, " \t");
						tokensNumInFaces.push_back(std::string(twoToken));
						isTwoFace = false;
					}
					else
					{
						tokensNumInFaces.push_back(std::string(token));
					}
					token = strtok_s(NULL, delimiterFace, &nextToken);
				}
				if (tokensNumInFaces.size()<=9)
				{
					for (int i = 0; i <tokensNumInFaces.size(); i++)
					{
						tokensFaces.push_back(tokensNumInFaces[i]);//sin son solo 9 elementos se cuenta como tri
					}
				}
				else//si son mas elementos se cuenta como quad y los acomodo de una forma poco ortodoxa, pero es como pude
				{

					tokensFaces.push_back(tokensNumInFaces[0]);
					tokensFaces.push_back(tokensNumInFaces[1]);
					tokensFaces.push_back(tokensNumInFaces[2]);
					tokensFaces.push_back(tokensNumInFaces[3]);
					tokensFaces.push_back(tokensNumInFaces[4]);
					tokensFaces.push_back(tokensNumInFaces[5]);
					tokensFaces.push_back(tokensNumInFaces[9]);
					tokensFaces.push_back(tokensNumInFaces[10]);
					tokensFaces.push_back(tokensNumInFaces[11]);
					tokensFaces.push_back(tokensNumInFaces[9]);
					tokensFaces.push_back(tokensNumInFaces[10]);
					tokensFaces.push_back(tokensNumInFaces[11]);
					tokensFaces.push_back(tokensNumInFaces[3]);
					tokensFaces.push_back(tokensNumInFaces[4]);
					tokensFaces.push_back(tokensNumInFaces[5]);
					tokensFaces.push_back(tokensNumInFaces[6]);
					tokensFaces.push_back(tokensNumInFaces[7]);
					tokensFaces.push_back(tokensNumInFaces[8]);
				}
				tokensNumInFaces.clear();//libero el vector para contar caras 
			}
			else if (0 == strcmp(token, "mtllib"))//guarda el nombre del archvio de materiales de maya
			{
				m_obj.s_mtlLibFilename= token = strtok_s(NULL, " \t", &nextToken);
			}
			else if (0 == strcmp(token, "usemtl"))//es para el material en el archivo de maya
			{
				m_obj.s_materialName = token = strtok_s(NULL, " \t", &nextToken);
			}
			else
				token = strtok_s(NULL, " \t", &nextToken);
		}

		if (!finishObjectMaya)
		{
			if (!finishObjectMaya && objectNumber<1)//el primer objeto con el que se encuentra es el mismo
			{
				objectNumber++;
			}
			else//si se encuentra otro guarda el actual y empiza el otro
			{
				objectNumber++;
				m_obj.vVertices = tokensVertices;
				m_obj.vNormales = tokensNormales;
				m_obj.vTexturas = tokensTexturas;
				m_obj.vFaces = tokensFaces;
				m_objetos.push_back(m_obj);
				tokensVertices.clear();
				tokensFaces.clear();
				tokensNormales.clear();
				tokensTexturas.clear();
			}
		}
		else if (!finishObjectOBJ)//para documentos obj normales, no funciona
		{
			if (!finishObjectOBJ && objectNumber<1)
			{
				objectNumber++;
			}
			else
			{
				objectNumber++;
				m_obj.vVertices = tokensVertices;
				m_obj.vNormales = tokensNormales;
				m_obj.vTexturas = tokensTexturas;
				m_obj.vFaces = tokensFaces;
				m_objetos.push_back(m_obj);
				tokensVertices.clear();
				tokensFaces.clear();
				tokensNormales.clear();
				tokensTexturas.clear();
			}
		}
	}
	m_obj.vVertices = tokensVertices;//al acabar guarda el objeto actual
	m_obj.vNormales = tokensNormales;
	m_obj.vTexturas = tokensTexturas;
	m_obj.vFaces = tokensFaces;
	m_objetos.push_back(m_obj);
	tokensVertices.clear();
	tokensFaces.clear();
	tokensNormales.clear();
	tokensTexturas.clear();

	infile.close();

	//delete nextToken, token, twoToken;
	return readFileOk;
}

/*
* NOTE: This code reads the .obj file format and can skip normal/UV coords information if the file doesn't have it,
*
* TO-DO...
* Also, this reads files with triangles, not quads. This is also a TO-DO...
*/
// no lo utilizo
bool C3DSergio_Model_Obj::parseObjLine(std::string line, bool countOnly, int lineNumber)
{
	bool parsed = false;
	bool unrecognizedLine = false;

	bool readingVertex = false;
	bool readingNormal = false;
	bool readingUV = false;
	bool readingFace = false;
	bool readingTexture = false;

	char *nextToken = NULL;
	char *token = NULL;

	const char *delimiterToken = " \t";
	const char *delimiterFace = "/";

	int currentToken = 0;
	int numTokens = 0;
	int numExpectedTokens = 4;

	std::vector<std::string> tokens;

	std::string materialName;
	std::string materialFilename;

	token = strtok_s((char *)line.c_str(), delimiterToken, &nextToken);

	// Line without space or tab separators (most likely a null string)
	if (token == NULL)
	{
		parsed = true;
	}

	// If there are any tokens left
	while (token != NULL)
	{
		// If first token
		if (currentToken == 0)
		{
			// Vertex
			if (0 == strcmp(token, "v"))
			{
				readingVertex = true;

				if (countOnly)
				{
					m_numVertices++;
				}
			}
			// Normal
			else if (0 == strcmp(token, "vn"))
			{
				readingNormal = true;

				if (countOnly)
				{
					m_numNormals++;
				}
			}
			// Vertex texture
			else if (0 == strcmp(token, "vt"))
			{
				readingUV = true;

				if (countOnly)
				{
					m_numUVCoords++;
				}
			}
			// Face
			else if (0 == strcmp(token, "f"))
			{
				readingFace = true;

				if (countOnly)
				{
					// Check if this line is a quad or a triangle
					std::string nextStrToken(nextToken);

					m_numFaces++;
				}
			}
			// Texture
			else if (0 == strcmp(token, "mtllib"))
			{
				readingTexture = true;
			}
			else
			{
				// Unrecognized line
				if (countOnly)
				{
					cout << "Ignoring line #" << lineNumber << ": " << line << endl;
				}
				unrecognizedLine = true;
			}

			// If this line has an unrecognized format
			// OR If we're in count only mode and we processed the first token, 
			// break to exit method and go to next line
			if (countOnly || unrecognizedLine)
			{
				return true;
			}
		}
		else
		{
			// Add token to vector
			tokens.push_back(std::string(token));
		}

		// Read next token
		token = strtok_s(NULL, delimiterToken, &nextToken);
		currentToken++;

		// No more tokens
		if (token == NULL)
		{
			//  If we're NOT in "count only" mode
			if (!countOnly)
			{
				// Verify we have the expected number of tokens
				if (currentToken != numExpectedTokens && !readingTexture)
				{
					cout << "Ignoring line, number of tokens doesn't match the expected." << endl;
					cout << line.c_str() << endl;
				}
				else
				{
					// Create the vertex|normal|UVcoord|face
					if (readingVertex || readingNormal || readingUV)
					{
						// Add the 3 effective tokens to the appropriate array
						float values[3];
						values[0] = (float)atof(tokens[0].c_str());
						values[1] = (float)atof(tokens[1].c_str());
						values[2] = (float)atof(tokens[2].c_str());
						parsed = true;

						if (readingVertex && m_verticesRaw != NULL &&
							(m_currentVertex < m_numVertices) && m_numVertices > 0)
						{
							m_verticesRaw[(m_currentVertex * 3)] = values[0];
							m_verticesRaw[(m_currentVertex * 3) + 1] = values[1];
							m_verticesRaw[(m_currentVertex * 3) + 2] = values[2];

							m_currentVertex++;
						}
						else if (readingNormal && m_normalsRaw != NULL &&
							(m_currentNormal < m_numNormals) && m_numNormals > 0)
						{
							m_normalsRaw[(m_currentNormal * 3)] = values[0];
							m_normalsRaw[(m_currentNormal * 3) + 1] = values[1];
							m_normalsRaw[(m_currentNormal * 3) + 2] = values[2];

							m_currentNormal++;
						}
						else if (readingUV && m_uvCoordsRaw != NULL &&
							(m_currentUV < m_numUVCoords) && m_numUVCoords > 0)
						{
							m_uvCoordsRaw[(m_currentUV * 2)] = values[0];
							m_uvCoordsRaw[(m_currentUV * 2) + 1] = values[1];

							m_currentUV++;
						}
						else
						{
							parsed = false;
						}
					}
					else if (
						readingFace
						&& m_vertexIndices != NULL
						&& m_normalIndices != NULL
						&& m_UVindices != NULL
						&& (m_currentFace < (m_numFaces * 3))
						&& m_numFaces > 0
						)
					{
						// Parse the current token to extract the vertex|normal|UV index
						parsed = true;
						nextToken = NULL;
						token = NULL;

						// Loop through all 3 groups of indices, i.e:    1/3/4    3/5/2    2/3/1
						//
						// token[0] = 1/3/4
						// token[1] = 3/5/2
						// token[2] = 2/3/1
						for (int i = 0; i < 3 && i < tokens.size(); i++)
						{
							currentToken = -1;

							// Get group of indices and split it into tokens with '/' as delimiter
							token = strtok_s((char *)tokens[i].c_str(), delimiterFace, &nextToken);

							while (nextToken != NULL && *nextToken != '\0')
							{
								currentToken++;

								if (token != NULL)
								{
									switch (currentToken)
									{
									case 0:
										// Indices in .obj format start at 1, but our arrays start from index 0
										m_vertexIndices[m_currentFace + i] = (unsigned short)(atoi(token)) - 1;
										break;
									case 1:
										// Indices in .obj format start at 1, but our arrays start from index 0
										m_UVindices[m_currentFace + i] = (unsigned short)(atoi(token)) - 1;
										break;
									case 2:
										// Indices in .obj format start at 1, but our arrays start from index 0
										m_normalIndices[m_currentFace + i] = (unsigned short)(atoi(token)) - 1;
										break;
									}
								}

								token = strtok_s(NULL, delimiterFace, &nextToken);

								// Last token
								if (token != NULL &&
									(nextToken == NULL || (nextToken != NULL && *nextToken == '\0'))
									)
								{
									currentToken++;

									switch (currentToken)
									{
									case 0:
										// Indices in .obj format start at 1, but our arrays start from index 0
										m_vertexIndices[m_currentFace + i] = (unsigned short)(atoi(token)) - 1;
										break;
									case 1:
										// Indices in .obj format start at 1, but our arrays start from index 0
										m_UVindices[m_currentFace + i] = (unsigned short)(atoi(token)) - 1;
										break;
									case 2:
										// Indices in .obj format start at 1, but our arrays start from index 0
										m_normalIndices[m_currentFace + i] = (unsigned short)(atoi(token)) - 1;
										break;
									}
								}
							} // while (nextToken != NULL)
						} // for

						m_currentFace += 3;
						token = NULL;
						nextToken = NULL;
					} // reading face
					else if (readingTexture)
					{
						if (readMtllib(tokens[0], materialName, materialFilename))
						{
							m_modelTextureFilename = new char[materialFilename.size() + 1];
							memset(m_modelTextureFilename, 0, materialFilename.size() + 1);
							memcpy(m_modelTextureFilename, materialFilename.c_str(), materialFilename.size());
							m_modelHasTextures = true;
							parsed = true;
						}
						else
						{
							parsed = false;
						}
					}

				} // reading
			} // !count only
		} // No more tokens
	}

	return parsed;
}//no lo utilizo

/*
*/

//no lo utilizo
bool C3DSergio_Model_Obj::readMtllib(std::string mtlLibFilename, std::string &materialName, std::string &materialFilename)
{
	bool readTextureName = false;

	ifstream infile;
	string lineBuffer;
	char *nextToken = nullptr;
	char *token = nullptr;
	const char *delimiterToken = " \t";
	bool readingMaterialName = false;
	bool readingMaterialFilename = false;
	int numToken = 0;

	materialName.clear();
	materialFilename.clear();

	infile.open(mtlLibFilename);

	while (!infile.eof())
	{
		getline(infile, lineBuffer);

		readingMaterialName = false;
		readingMaterialFilename = false;
		numToken = 0;

		token = strtok_s((char *)lineBuffer.c_str(), delimiterToken, &nextToken);
		++numToken;

		// If there are any tokens left
		while (token != nullptr)
		{
			if (numToken == 1)
			{
				if (0 == strcmp(token, "newmtl"))
				{
					readingMaterialName = true;
				}
				else if (0 == strcmp(token, "map_Kd"))
				{
					readingMaterialFilename = true;
				}
			}
			else if (numToken == 2)
			{
				if (readingMaterialName)
				{
					materialName.append(token);
				}
				else if (readingMaterialFilename)
				{
					materialFilename.append(token);
					readTextureName = true;
					break;
				}
			}

			token = strtok_s(nullptr, delimiterToken, &nextToken);
			++numToken;
		}

		// For now, only read the first material
		if (readTextureName)
		{
			break;
		}
	}

	infile.close();

	return readTextureName;
}

bool C3DSergio_Model_Obj::readMtllibMaya(std::string mtlLibFilename, std::string &materialName, std::string &materialFilename,int i)
{
	bool readTextureName = false;

	ifstream infile;
	string lineBuffer;
	string material;
	string map = "map_Kd";
	char *nextToken = nullptr;
	char *token = nullptr;
	char *token2 = nullptr;
	const char *delimiterToken = " \t";
	bool findMateria = false;
	bool findMaterialFilename = false;
	int numToken = 0;
	//materialName.clear();//por que y alo traigo desde afuera evito que se limpie
	materialFilename.clear();

	infile.open(mtlLibFilename);

	while (!infile.eof())
	{
		getline(infile, lineBuffer);
		
		findMateria = lineBuffer.find("newmtl");//veo si es un nuevo material
		token = strtok_s((char *)lineBuffer.c_str(), delimiterToken, &nextToken);
		if (!findMateria)//si se encuentra 
		{
			token = strtok_s(NULL, delimiterToken, &nextToken);
			material = token;
			if (material==materialName)//si el material encontrado es igual al objeto actual 
			{
				//bool endMaterial = true; //lo plane usar para en caso de que acabara
				while (token!=NULL)
				{
					getline(infile, lineBuffer);
					token = strtok_s((char *)lineBuffer.c_str(), delimiterToken, &nextToken);
					token = strtok_s(NULL, delimiterToken, &nextToken);
					findMaterialFilename = lineBuffer.find(map);//busco el mapa de kd
					//endMaterial = lineBuffer.find("newmtl");
					if (!findMaterialFilename) //si lo encuentra las UV se hacen verdaderas y se rompe el ciclo 
					{
						materialFilename = string(token);
						m_objetos[i].s_modelHasUVs = true;
						break;
					}
					else//mientras no lo encuentre las UV seran falsas
					{
						m_objetos[i].s_modelHasUVs = false;
					}
				}
			}
			else
			{
				m_objetos[i].s_modelHasUVs = false;//si no es el material la UV son falsas
			}
		}
	}
	m_objetos[i].s_modelTextureFilename = new char[materialFilename.size() + 1];
	memset(m_objetos[i].s_modelTextureFilename, 0, materialFilename.size() + 1);
	memcpy(m_objetos[i].s_modelTextureFilename, materialFilename.c_str(), materialFilename.size());
	m_objetos[i].s_modelHasTextures = true;

	infile.close();

	return readTextureName;
}