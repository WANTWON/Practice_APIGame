#include "stdafx.h"
#include "Block.h"
#include "LineMgr.h"

CBlock::CBlock() : m_bCreate(false)
{
}


CBlock::~CBlock()
{
}

void CBlock::Initialize(void)
{
	m_tInfo = { 125.f,125.f, 50.f, 50.f };
	

	
}

int CBlock::Update(void)
{
	Update_Rect();

	/*if (!m_bCreate)
	{
		LINEPOINT Left = { (float)m_tRect.left, (float)m_tRect.top };
		LINEPOINT Right = { (float)m_tRect.right, (float)m_tRect.top };
		CLineMgr::Get_Instance()->Add_Object(Left, Right);

		m_bCreate = true;
	}*/
	

	return OBJ_NOEVENT;
}

void CBlock::Late_Update(void)
{
}

void CBlock::Release(void)
{
}

void CBlock::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}
