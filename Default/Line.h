#pragma once

#include "Include.h"

class CLine
{
public:
	CLine();
	~CLine();
	CLine(LINEPOINT& RightPoint, LINEPOINT& LeftPoint);
	CLine::CLine(const LINE& tInfo)
		: m_tInfo(tInfo)
	{}

public:
	const LINE& Get_Line(void) { return m_tInfo; }
	void Render(HDC hDC);
	void Release(void);
	const float Get_Y(float _fX)
	{
		//	Get Line's Y by _fX

		//	Equation by Straight line
		//	Y - y1 = ((y2 - y1) / (x2 - x1)) * (X - x1)
		//	Y = ((y2 - y1) / (x2 - x1)) * (X - x1) + y1

		float x1 = m_tInfo.fLPoint.fX;
		float y1 = m_tInfo.fLPoint.fY;

		float x2 = m_tInfo.fRPoint.fX;
		float y2 = m_tInfo.fRPoint.fY;

		float _fY = ((y2 - y1) / (x2 - x1))*(_fX - x1) + y1;
		return _fY;
	}

private:
	LINE m_tInfo;
};

