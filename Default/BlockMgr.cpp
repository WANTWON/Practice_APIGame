#include "stdafx.h"
#include "BlockMgr.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"

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
			iter->Update();
	}


	for (size_t i = 0; i < BLOCK_END; ++i)
	{
		for (auto& iter : m_Blocklist[i])
		{
			Col_Player(CCollisionMgr::Col_ReturnDir(m_listPlayer, iter));
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
			else
				Player->Set_PosY(fHeight);
		}
		else //좌우 충돌 
		{
			if (pTarget->Get_Info().fX > Player->Get_Info().fX)
				Player->Set_PosX(-fWidth);
			else
				Player->Set_PosX(fWidth);
		}
	}
}

void CBlockMgr::Col_Player(DIRECTION _eDir)
{
	switch (_eDir)
	{
	case DIR_UP:
		break;

	case DIR_DOWN:
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


