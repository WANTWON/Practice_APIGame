#include "stdafx.h"
#include "Line.h"


CLine::CLine()
{
}


CLine::~CLine()
{
	Release();
}

CLine::CLine(LINEPOINT & LeftPoint, LINEPOINT & RightPoint)
	: m_tInfo(LeftPoint, RightPoint)
{
}

void CLine::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_tInfo.fLPoint.fX, (int)m_tInfo.fLPoint.fY, nullptr);
	LineTo(hDC, (int)m_tInfo.fRPoint.fX, (int)m_tInfo.fRPoint.fY);
}

void CLine::Release(void)
{
}
