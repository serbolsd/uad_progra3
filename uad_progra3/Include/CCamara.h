#pragma once
#include "CVector3.h"
class CCamara
{
public:
	CCamara();
	~CCamara();
	CVector3 m_posicion;
private:
	CVector3 m_pos;				//get
	CVector3 m_lookAt;			//get
	CVector3 m_right;			//get
	float m_nearPlane = 0.001f;	//get
	float m_farPlane = 1000.0f;	//get
public:
	bool m_2D;
	void moveCamera(CVector3 delta);
	void panCamera(CVector3 delta);

	CVector3 getPos() { return m_pos; }
	CVector3 getLookAt() { return m_lookAt; }
	CVector3 getRight() { return m_right; }
	float getNearPlane() { return m_nearPlane; }
	float getFarPlane() { return m_farPlane; }

	CVector3 superiorIzquierdo={-0.1,1.0,0.0};
	CVector3 superiorDerecho = {-1.0,0.1,0.0};

};

