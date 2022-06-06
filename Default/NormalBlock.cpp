#include "stdafx.h"
#include "NormalBlock.h"



CNormalBlock::CNormalBlock()
{
}


CNormalBlock::~CNormalBlock()
{
	Release();
}

void CNormalBlock::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_BlockType = BLOCK_NORMAL;
}

int CNormalBlock::Update(void)
{
	if (OBJ_DEAD == m_bDead)
		return OBJ_DEAD;


	Update_Rect();

	return OBJ_NOEVENT;
}

void CNormalBlock::Late_Update(void)
{
	CCollisionMgr::Collision_Bullet(this, CObjMgr::Get_Instance()->Get_Bullets());
}

void CNormalBlock::Release(void)
{
}

void CNormalBlock::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	TextOut(hDC, m_tInfo.fX, m_tInfo.fY, L"N", DT_CENTER);
}
