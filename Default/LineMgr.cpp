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



void CLineMgr::Initialize(int _Number)
{
	if (1 == _Number)
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


		{ 10.f, 400.f },
		{ 200.f, 500.f },
		{ 700.f, 500.f },
		{ 700.f, 100.f }
	};
	else if (3 == _Number)
	{

		LINEPOINT tPoint[8] =
		{
			{ 0, 450.f },
			{ 200.f, 450.f },
			{250.f, 200.f},
			{450.f, 200.f},
			{450.f, 450.f},
			{WINCX, 450.f},
			{ 550.f, 440.f },
			{ 550.f, 100.f}
		};
		m_Linelist.push_back(new CLine(tPoint[0], tPoint[1]));
		m_Linelist.push_back(new CLine(tPoint[1], tPoint[2]));
		m_Linelist.push_back(new CLine(tPoint[2], tPoint[3]));
		m_Linelist.push_back(new CLine(tPoint[3], tPoint[4]));
		m_Linelist.push_back(new CLine(tPoint[4], tPoint[5]));
		m_Flagline.push_back(new CLine(tPoint[6] , tPoint[7]));
	}

}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_Linelist)
		iter->Render(hDC);
	

	//½ÇÇè¿ë
	for (auto& iter : m_Flagline)
		iter->Render(hDC);
}

void CLineMgr::Release(void)
{
	for_each(m_Linelist.begin(), m_Linelist.end(), CDeleteObj());
	m_Linelist.clear();

	//½ÇÇè¿ë
	for_each(m_Flagline.begin(), m_Flagline.end(), CDeleteObj());
	m_Flagline.clear();
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

	// Á÷¼±ÀÇ ¹æÁ¤½Ä 
	// Y - y1 = ((y2 - y1) / (x2 - x1)) * (X - x1)
	// Y = ((y2 - y1) / (x2 - x1)) * (X - x1) + y1

	float x1 = pTarget->Get_Line().fLPoint.fX;
	float y1 = pTarget->Get_Line().fLPoint.fY;

	float x2 = pTarget->Get_Line().fRPoint.fX;
	float y2 = pTarget->Get_Line().fRPoint.fY;

	*_fY = ((y2 - y1) / (x2 - x1))*(_fX - x1) + y1;

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



bool CLineMgr::CollisionFlag(RECT rc, float * _fY)
{
	if (m_Flagline.empty())
		return false;

	CLine* pTarget = nullptr;

	for (auto& iter : m_Flagline)
	{
		if (rc.right >= iter->Get_Line().fLPoint.fX
			&& rc.left < iter->Get_Line().fRPoint.fX)
		{
			pTarget = iter;
			return true;
		}
	}

	if (!pTarget)
		return false;

	// Á÷¼±ÀÇ ¹æÁ¤½Ä 
	// Y - y1 = ((y2 - y1) / (x2 - x1)) * (X - x1)
	// Y = ((y2 - y1) / (x2 - x1)) * (X - x1) + y1

	//float x1 = pTarget->Get_Line().fLPoint.fX;
	//float y1 = pTarget->Get_Line().fLPoint.fY;

	//float x2 = pTarget->Get_Line().fRPoint.fX;
	//float y2 = pTarget->Get_Line().fRPoint.fY;

	//*_fY = ((y2 - y1) / (x2 - x1))*(rc.right - x1) + y1;

	return true;
}

