#include "stdafx.h"
#include "BlockMgr.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "NormalBlock.h"
#include <typeinfo>
#include "AbstractFactory.h"
#include "Item.h"

//	아이템
#include "Coin.h"
#include "Mushroom.h"
#include "Star.h"
#include "Flower.h"
#include "CoinBlock.h"

CBlockMgr* CBlockMgr::m_pInstance = nullptr;

CBlockMgr::CBlockMgr()
{
}


CBlockMgr::~CBlockMgr()
{
}

void CBlockMgr::Initialize(void)
{
	m_listPlayer = CObjMgr::Get_Instance()->Get_listPlayer();

	for (size_t i = 0; i < BLOCK_END; ++i)
	{
		for (auto& iter : m_Blocklist[i])
			iter->Initialize();
	}
}

void CBlockMgr::Update(void)
{
	for (size_t i = 0; i < BLOCK_END; ++i)
	{
		for (auto& iter : m_Blocklist[i])
		{
			Col_Player(iter, CCollisionMgr::Col_ReturnDir(m_listPlayer, iter));
		}
	}

	int iEvent = 0;
	for (size_t i = 0; i < BLOCK_END; ++i)
	{
		for (auto& iter = m_Blocklist[i].begin(); iter != m_Blocklist[i].end(); )
		{
			iEvent = (*iter)->Update();

			if (iEvent == OBJ_DEAD)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_Blocklist[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CBlockMgr::Late_Update(void)
{
	for (size_t i = 0; i < BLOCK_END; ++i)
	{
		for (auto& iter : m_Blocklist[i])
			iter->Late_Update();
	}
}

void CBlockMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < BLOCK_END; ++i)
	{
		for (auto& iter : m_Blocklist[i])
			iter->Render(hDC);
	}
}

void CBlockMgr::Release(void)
{

	for (size_t i = 0; i < BLOCK_END; ++i)
	{
		for (auto& iter = m_Blocklist[i].begin(); iter != m_Blocklist[i].end(); )
		{
			Safe_Delete<CObj*>(*iter);
			iter = m_Blocklist[i].erase(iter);
		}
	}

	for (size_t i = 0; i < BLOCK_END; ++i)
		m_Blocklist[i].clear();

}

void CBlockMgr::Add_Object(BLOCK_LIST _ID, CObj* pObj)
{
	if (_ID == OBJ_END || nullptr == pObj)
		return;

	m_Blocklist[_ID].push_back(pObj);
}

bool CBlockMgr::CollisionBlock(RECT Player, float _fX, float * Change_fY)
{
	int iTemp = 0;
	for (size_t i = 0; i < BLOCK_END; ++i)
	{
		if (m_Blocklist[i].empty())
			++iTemp;

		if (BLOCK_END == iTemp)
		{
			return false;
		}
	}


	CObj* pTarget = nullptr;

	for (size_t i = 0; i < BLOCK_END; ++i)
	{
		for (auto& iter : m_Blocklist[i])
		{
		if ( Player.right >= iter->Get_Rect().left && Player.left < iter->Get_Rect().right
			&& Player.bottom < iter->Get_Rect().top+2 && Player.bottom > iter->Get_Rect().top-2)
			// 플레이어의 X값(중점)이 상자의 왼쪽과 오른쪽 사이에 있고, 플레이어의 Bottom이 상자의 Top보다 클 때
			// (이때, 플레이어랑 상자의 X값만 조건으로 하면 바로 Jump가 false처리 되어 순간이동 할 수 있어서, Y값도 조건으로 주고 2를 임의적으로 추가함)
			pTarget = iter;
		}
	}

	if (!pTarget)
		return false;

	// 직선의 방정식 
	// Y - y1 = ((y2 - y1) / (x2 - x1)) * (X - x1)
	// Y = ((y2 - y1) / (x2 - x1)) * (X - x1) + y1

	float x1 = pTarget->Get_Rect().left;
	float y1 = pTarget->Get_Rect().top;

	float x2 = pTarget->Get_Rect().right;
	float y2 = pTarget->Get_Rect().top;

	*Change_fY = ((y2 - y1) / (x2 - x1))*(_fX - x1) + y1;

	return true;

}



bool CBlockMgr::Collision_with_Direction(CObj* Player)
{
	int iTemp = 0;
	for (size_t i = 0; i < BLOCK_END; ++i)
	{
		if (m_Blocklist[i].empty())
			++iTemp;

		if (BLOCK_END == iTemp)
		{
			return false;
		}
	}

	CObj* pTarget = nullptr;

	for (size_t i = 0; i < BLOCK_END; ++i)
	{
		for (auto& iter : m_Blocklist[i])
		{
			if (Player->Get_Info().fX >= iter->Get_Rect().left && Player->Get_Info().fX < iter->Get_Rect().right)
				pTarget = iter;

		}
	}

	if (!pTarget)
		return false;

	float fWidth = 0.f;
	float fHeight = 0.f;

	if (Check_Rect(Player->Get_Info(), pTarget->Get_Info(), &fWidth, &fHeight))
	{
		if (fWidth > fHeight)  //상하 충돌
		{
			if (pTarget->Get_Info().fY >= Player->Get_Info().fY)
				Player->Set_PosY(-fHeight);
			//else
				//Player->Set_PosY(fHeight);
		}
		else //좌우 충돌 
		{/*
			if (pTarget->Get_Info().fX > Player->Get_Info().fX)
				Player->Set_PosX(-fWidth);
			else
				Player->Set_PosX(fWidth);*/
		}
	}
}

void CBlockMgr::Col_Player(CObj* _thisBlock, DIRECTION _eDir)
{
	switch (_eDir)
	{
	case DIR_UP:
		break;

	case DIR_DOWN:
		static_cast<CPlayer*>(m_listPlayer.front())->Set_GravityTime(3.4f);
		Check_BreakBlock(_thisBlock);
		break;

	case DIR_LEFT:
		m_listPlayer.front()->Set_PosX(-1.f * m_listPlayer.front()->Get_Speed());
		break;

	case DIR_RIGHT:
		m_listPlayer.front()->Set_PosX(m_listPlayer.front()->Get_Speed());
		break;

	default:
		break;
	}

}

void CBlockMgr::Check_BreakBlock(CObj * _thisBlock)
{
	if ((true == static_cast<CBlock*>(_thisBlock)->Get_IsItem()) && (false == static_cast<CCoinBlock*>(_thisBlock)->Get_Used()))
	{
 		Create_RandItem(_thisBlock);
		_thisBlock->Set_Dead(OBJ_DEAD);
	}

	if (1 <= static_cast<CPlayer*>(m_listPlayer.front())->Get_Level())
	{
		_thisBlock->Set_Dead(OBJ_DEAD);
	}
	else
		return;
}

void CBlockMgr::Create_RandItem(CObj* _thisBlock)
{
	ITEM_TYPE iItemNum = ITEM_TYPE(rand() % ITEM_END);

	switch (iItemNum)
	{
	case ITEM_COIN:
		CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CCoin>::Create(_thisBlock->Get_Info().fX, _thisBlock->Get_Info().fY - (_thisBlock->Get_Info().fCY * 0.5f), iItemNum));
		break;
	case ITEM_MUSHROOM:
		CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CMushroom>::Create(_thisBlock->Get_Info().fX, _thisBlock->Get_Info().fY - (_thisBlock->Get_Info().fCY * 0.5f), iItemNum));
		break;
	case ITEM_STAR:
		CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CStar>::Create(_thisBlock->Get_Info().fX, _thisBlock->Get_Info().fY - (_thisBlock->Get_Info().fCY * 0.5f), iItemNum));
		break;
	case ITEM_FLOWER:
		CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CFlower>::Create(_thisBlock->Get_Info().fX, _thisBlock->Get_Info().fY - (_thisBlock->Get_Info().fCY * 0.5f), iItemNum));
		break;
	default:
		break;
	}
}


int CBlockMgr::Check_Rect(INFO Player, INFO pTarget, float* _pX, float* _pY)
{



	float fWidth = abs(Player.fX - pTarget.fX);
	float fHeight = abs(Player.fY - pTarget.fY);

	float fRadiusX = (Player.fCX + pTarget.fCX*0.5f);
	float fRadiusY = (Player.fCY + pTarget.fCY*0.5f);

	if ((fWidth <= fRadiusX) && (fHeight <= fRadiusY))
	{
		*_pX = fRadiusX - fWidth;
		*_pY = fRadiusY - fHeight;
		return true;
	}
	else
		return false;
}


//	몬스터랑 블럭이랑 충돌
//	충돌 시 아이템


