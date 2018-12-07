#pragma once
#include "CQuadTreeNode.h"
#include"CCamara.h"
 
class CQuadTree : public CQuadTreeNode
{
public:
	CQuadTree();
	CQuadTree(int window_width,int window_height);
	~CQuadTree();
	CQuadTreeNode *root;
	CCamara *cam;
	COpenGLRenderer*renderer;

	CVector3 m_positionOject;
	double m_currentDeltaTime;
	double m_objectRotation;
	double m_rotationSpeed;
	bool m_initialize;

	void render();
	void initialize();
	void run();
	void update(double deltatime);
	bool initializeMenu() { return false; }
	
private:

};

