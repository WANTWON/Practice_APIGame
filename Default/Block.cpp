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
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
}
