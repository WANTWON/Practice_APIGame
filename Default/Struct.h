#pragma once


// x좌표, y좌표, 가로 길이, 세로 길이의 값을 받는 것

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
