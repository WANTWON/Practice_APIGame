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
		{ 10.f, 400.f },
		{ 200.f, 500.f },
		{ 700.f, 500.f },
		{ 700.f, 100.f }
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

bool CLineMgr::CollisionLine(CObj*	_pObj, float* _fY)		//+
{
	if (m_Linelist.empty())
		return false;

	CLine* pTarget = nullptr;

	for (auto& iter : m_Linelist)
	{
		if (_pObj->Get_Info().fX >= iter->Get_Line().fLPoint.fX
			&& _pObj->Get_Info().fX < iter->Get_Line().fRPoint.fX
			&& _pObj->Get_Info().fY + (_pObj->Get_Info().fCY * 0.55f) >= iter->Get_Y(_pObj->Get_Info().fX)
			&& _pObj->Get_Info().fY - (_pObj->Get_Info().fCY * 0.5f) < iter->Get_Y(_pObj->Get_Info().fX))
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

	//-	*_fY = ((y2 - y1) / (x2 - x1))*(_fX - x1) + y1;
	*_fY = ((y2 - y1) / (x2 - x1))*(_pObj->Get_Info().fX - x1) + y1;

	return true;
}

CLine* CLineMgr::CollisionLine_Bullet(float _fX, float * _OutY)
{
	if (m_Linelist.empty())
		return false;

	CLine* pTarget = nullptr;

	for (auto& iter : m_Linelist)
	{
		// Bullet is in the middle of a line
		// (X Axis) 
		if (_fX >= iter->Get_Line().fLPoint.fX && _fX < iter->Get_Line().fRPoint.fX) 
			pTarget = iter;
	}

	if (!pTarget)
		return nullptr;

	float x1 = pTarget->Get_Line().fLPoint.fX;
	float y1 = pTarget->Get_Line().fLPoint.fY;

	float x2 = pTarget->Get_Line().fRPoint.fX;
	float y2 = pTarget->Get_Line().fRPoint.fY;

	*_OutY = ((y2 - y1) / (x2 - x1))*(_fX - x1) + y1;
	
	return pTarget;
}