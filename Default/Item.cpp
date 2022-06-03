#include "stdafx.h"
#include "Item.h"


CItem::CItem()
{
}

CItem::~CItem()
{
	Release();
}

void CItem::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_fSpeed = 5.f;
}

void CItem::Release()
{
}

int CItem::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CItem::Late_Update()
{

}

void CItem::Render(HDC hDC)
{
	switch (m_Type)
	{
	case ITEM_COIN:
		Render_Coin(hDC);
		break;

	case ITEM_MUSHROOM:
		Render_Mushroom(hDC);
		break;

	case ITEM_STAR:
		Render_Star(hDC);
		break;

	case ITEM_FLOWER:
		Render_Flower(hDC);
		break;

	default:
		Render_Coin(hDC);
	}
}

void CItem::Render_Coin(HDC hdc)
{
	HBRUSH myBrush = nullptr;
	HBRUSH oldBrush = nullptr;

	myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
	oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	Ellipse(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);
	
}

void CItem::Render_Mushroom(HDC hdc)
{
}

void CItem::Render_Star(HDC hdc)
{
}

void CItem::Render_Flower(HDC hdc)
{
}
