#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"


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

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	MoveToEx(hDC, (int)m_tInfo.fLPoint.fX + iScrollX, (int)m_tInfo.fLPoint.fY, nullptr);
	LineTo(hDC, (int)m_tInfo.fRPoint.fX + iScrollX, (int)m_tInfo.fRPoint.fY);
}

void CLine::Release(void)
{
}


