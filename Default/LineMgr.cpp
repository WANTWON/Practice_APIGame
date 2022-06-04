#include "stdafx.h"
#include "LineMgr.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release();
}



void CLineMgr::Initialize(void)
{
	LINEPOINT tPoint[4] =
	{
		{ 100.f, 450.f },
		{ 300.f, 450.f },
		{ 500.f, 250.f },
		{ 700.f, 250.f }
	};

	m_Linelist.push_back(new CLine(tPoint[0], tPoint[1]));
	m_Linelist.push_back(new CLine(tPoint[1], tPoint[2]));
	m_Linelist.push_back(new CLine(tPoint[2], tPoint[3]));

}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_Linelist)
		iter->Render(hDC);
}

void CLineMgr::Release(void)
{
	for_each(m_Linelist.begin(), m_Linelist.end(), CDeleteObj());
	m_Linelist.clear();
}

bool CLineMgr::CollisionLine(float _fX, float *_fY)
{
	if (m_Linelist.empty())
		return false;

	CLine* pTarget = nullptr;

	for (auto& iter : m_Linelist)
	{
		if (_fX >= iter->Get_Line().fLPoint.fX
			&& _fX < iter->Get_Line().fRPoint.fX)
			pTarget = iter;
	}

	if (!pTarget)
		return false;

	// 직선의 방정식 
	// Y - y1 = ((y2 - y1) / (x2 - x1)) * (X - x1)
	// Y = ((y2 - y1) / (x2 - x1)) * (X - x1) + y1

	float x1 = pTarget->Get_Line().fLPoint.fX;
	float y1 = pTarget->Get_Line().fLPoint.fY;

	float x2 = pTarget->Get_Line().fRPoint.fX;
	float y2 = pTarget->Get_Line().fRPoint.fY;

	*_fY = ((y2 - y1) / (x2 - x1))*(_fX - x1) + y1;

	return true;
}

bool CLineMgr::CollisionLine_Bullet(float _fX, float _fY, float * _OutY, CLine* _OutLine)
{
	if (m_Linelist.empty())
		return false;

	CLine* pTarget = nullptr;

	for (auto& iter : m_Linelist)
	{
		// Bullet is in the middle of a line (X axis oriented) 
		if (_fX >= iter->Get_Line().fLPoint.fX && _fX < iter->Get_Line().fRPoint.fX) 
			pTarget = iter;
	}

	if (!pTarget)
		return false;

	float x1 = pTarget->Get_Line().fLPoint.fX;
	float y1 = pTarget->Get_Line().fLPoint.fY;

	float x2 = pTarget->Get_Line().fRPoint.fX;
	float y2 = pTarget->Get_Line().fRPoint.fY;

	*_OutY = ((y2 - y1) / (x2 - x1))*(_fX - x1) + y1;
	//*_OutLine = CLine(LINEPOINT(pTarget->Get_Line().fLPoint.fX), LINEPOINT());

	return true;
}
