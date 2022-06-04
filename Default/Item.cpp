#include "stdafx.h"
#include "Item.h"


CItem::CItem() : m_Type(ITEM_END), m_bIsSpawned(false), m_fAnimSpeed(0.f), m_fAnimTime(0.f), m_fAnimAccel(9.8f), m_dwTime(GetTickCount())
{

}

CItem::~CItem()
{
	
}
