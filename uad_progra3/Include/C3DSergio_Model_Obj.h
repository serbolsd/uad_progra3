#pragma once
#ifndef C3DMODEL_H_OBJ_SERGIO
#define C3DMODEL_H_OBJ_SERGIO

#include <string>
using namespace std;

#include "C3DModel.h"

class C3DSergio_Model_Obj : public C3DModel
{
private:
	int m_currentVertex, m_currentNormal, m_currentUV, m_currentFace;	// Aux counters used when loading an object from file

	bool readObjFile(const char * const filename, bool countOnly, bool &finishRead, int &timeRead);		// Read object from file 
	bool readObjFileMaya(const char * const filename, bool countOnly, bool &finishRead, int &timeRead);     // Read maya version
	bool parseObjLine(													// Parse line
		std::string line,								  
		bool countOnly, 
		int lineNumber); 
	bool readMtllib(													// Read mtllib
		std::string mtlLibFilename,
		std::string &materialName, 
		std::string &materialFilename);	 

	bool readMtllibMaya(													// Read mtllib
		std::string mtlLibFilename,
		std::string &materialName,
		std::string &materialFilename,
		int i);

	

protected:
	void reset();														// Cleanup any allocated memory
	void resetCurrents();
	bool loadFromFile(const char * const filename);

public:
	C3DSergio_Model_Obj();
	~C3DSergio_Model_Obj();
};

#endif // !C3DMODEL_H_OBJ_SERGIO