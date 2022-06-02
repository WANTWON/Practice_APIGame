#include "stdafx.h"
#include "Block.h"


CBlock::CBlock()
{
}


CBlock::~CBlock()
{
	Release();
}

void CBlock::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
}

int CBlock::Update(void)
{


	Update_Rect();
	return true;
}

void CBlock::Late_Update(void)
{
}

void CBlock::Release(void)
{

}

void CBlock::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}
