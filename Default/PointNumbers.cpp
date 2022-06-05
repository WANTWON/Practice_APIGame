#include "stdafx.h"
#include "PointNumbers.h"
#include "Define.h"

CPointNumbers::CPointNumbers()
{

}

CPointNumbers::CPointNumbers(int iPoints, float fX, float fY) : m_iNumber(iPoints), m_fX(fX), m_fY(fY), m_fSpeed(0), m_bDead(false), m_dwTime(GetTickCount())
{
	m_fSpeed = 1.f;
}

CPointNumbers::~CPointNumbers()
{
	Release();
}

void CPointNumbers::Release()
{

}

int CPointNumbers::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_fY -= m_fSpeed;

	return OBJ_NOEVENT;
}

void CPointNumbers::Late_Update()
{
	if (GetTickCount() > m_dwTime + 500)
		m_bDead = true;
}

void CPointNumbers::Render(HDC hDC)
{
	if (m_iNumber != 0)
	{
		TCHAR sztPoints[32] = L"";
		swprintf_s(sztPoints, L"%d", m_iNumber);
		TextOut(hDC, m_fX, m_fY, sztPoints, lstrlen(sztPoints));
	}
}
