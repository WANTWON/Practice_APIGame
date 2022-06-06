#pragma once
#include "Enum.h"

// x좌표, y좌표, 가로 길이, 세로 길이의 값을 받는 것

class CObj;
typedef struct tagInfo
{
	float fX;
	float fY;
	float fCX;	//가로길이
	float fCY;	//세로길이
}INFO;

typedef struct tagPoint
{
	float fX;
	float fY;

	tagPoint(void) { ZeroMemory(this, sizeof(tagPoint)); }
	tagPoint(float _fX, float _fY) { fX = _fX; fY = _fY; }

}LINEPOINT;

typedef struct tagLine
{
	LINEPOINT fRPoint;
	LINEPOINT fLPoint;

	tagLine(void) { ZeroMemory(this, sizeof(tagLine)); }
	//tagLine(LINEPOINT& LeftPoint, LINEPOINT& RightPoint) : fLPoint(LeftPoint), fRPoint(RightPoint) {}

	tagLine(LINEPOINT& LeftPoint, LINEPOINT& RightPoint)
	{
		fRPoint.fX = RightPoint.fX;
		fRPoint.fY = RightPoint.fY;

		fLPoint.fX = LeftPoint.fX;
		fLPoint.fY = LeftPoint.fY;
	}

}LINE;


typedef struct tagSave
{
	INFO  m_tInfo; //x좌표, y좌표 등을 담은 구조체
	RECT  m_tRect; //m_tInfo를 기반으로 Rect의 left,top,right,bottom을 구함
	DIRECTION m_eDir;

	float m_fSpeed;
	bool  m_bDead;

	float m_fAngle;
	CObj* m_pTarget;

	OBJ_LIST  m_eID;


}SAVEOBJ;