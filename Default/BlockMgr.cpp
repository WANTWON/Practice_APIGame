#include "stdafx.h"
#include "BlockMgr.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "NormalBlock.h"
#include <typeinfo>
#include "AbstractFactory.h"
#include "Item.h"
#include "ItemBlock.h"
#include "FlagBlock.h"

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
	dynamic_cast<CBlock*>(m_Blocklist[_ID].back())->Set_Type(_ID);
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
			/*if (dynamic_cast<CFlagBlock*>(iter)->Get_Number())
			{
				continue;
			}*/
			if (Player.right >= iter->Get_Rect().left && Player.left < iter->Get_Rect().right
				&& Player.bottom < iter->Get_Rect().top + 3 && Player.bottom > iter->Get_Rect().top - 3 )
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

void CBlockMgr::Col_Player(CObj* _thisBlock, DIRECTION _eDir)
{
	switch (_eDir)
	{
	case DIR_UP:
 	//	static_cast<CPlayer*>(m_listPlayer.front())->Set_PosY(_thisBlock->Get_Info().fY - (_thisBlock->Get_Info().fCY * 0.5f));
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
	if ((true == static_cast<CBlock*>(_thisBlock)->Get_IsItem()) && (false == static_cast<CItemBlock*>(_thisBlock)->Get_Used()))
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

void CBlockMgr::Save_File(void)
{
	//	Block
	HANDLE hFile = CreateFile(L"../Data/SaveTemp/ObjBlock.dat",
		GENERIC_WRITE,
		NULL,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Save Block", L"Error", MB_OK);
		return;
	}
	DWORD dwByte = 0;
	DWORD dwTypeByte = 0;

	for (size_t i = 0; i < BLOCK_END ; ++i)
	{
		for (auto& iter : m_Blocklist[i])
		{
			WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
			WriteFile(hFile, &(static_cast<CBlock*>(iter)->Get_BlockType()), sizeof(int), &dwTypeByte, nullptr);
		}
	}
	CloseHandle(hFile);

#ifdef _DEBUG
	MessageBox(g_hWnd, L"Block Save 성공", L"성공", MB_OK);
#endif	//_DEBUG
}

void CBlockMgr::Load_File(int _iStage)
{
	HANDLE	hFile = nullptr;
	DWORD	dwByte = 0;
	DWORD	dwTypeByte = 0;
	INFO	tTemp{};
	int		iDest = 0;
	BLOCK_LIST typeTemp = BLOCK_END;

	switch (_iStage)
	{
	case 1:
		//	Block
		hFile = CreateFile(L"../Data/Save1/ObjBlock.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Block", L"Error", MB_OK);
			return;
		}
		dwByte = 0;
		dwTypeByte = 0;
		tTemp = {};
		iDest = 0;
		typeTemp = BLOCK_END;

		while (true)
		{
			ReadFile(hFile, &tTemp, sizeof(INFO), &dwByte, nullptr);
			ReadFile(hFile, &iDest, sizeof(int), &dwTypeByte, nullptr);
			if (0 == dwByte)
				break;
			if (0 == dwTypeByte)
				break;

			switch (iDest)
			{
			case BLOCK_NORMAL:
				m_Blocklist[BLOCK_NORMAL].push_back(CAbstractFactory<CNormalBlock>::Create(tTemp.fX, tTemp.fY));
				break;
			case BLOCK_COIN:
				m_Blocklist[BLOCK_COIN].push_back(CAbstractFactory<CCoinBlock>::Create(tTemp.fX, tTemp.fY));
				break;
			case BLOCK_ITEM:
				m_Blocklist[BLOCK_ITEM].push_back(CAbstractFactory<CItemBlock>::Create(tTemp.fX, tTemp.fY));
				break;
			case BLOCK_FLAG:
				m_Blocklist[BLOCK_FLAG].push_back(CAbstractFactory <CFlagBlock> ::Create(tTemp.fX, tTemp.fY));
				break;
			}
		}
		CloseHandle(hFile);

		return;

	case 2:
		//	Block
		hFile = CreateFile(L"../Data/Save2/ObjBlock.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Block", L"Error", MB_OK);
			return;
		}
		dwByte = 0;
		dwTypeByte = 0;
		tTemp = {};
		iDest = 0;
		typeTemp = BLOCK_END;

		while (true)
		{
			ReadFile(hFile, &tTemp, sizeof(INFO), &dwByte, nullptr);
			ReadFile(hFile, &iDest, sizeof(int), &dwTypeByte, nullptr);
			if (0 == dwByte)
				break;
			if (0 == dwTypeByte)
				break;

			switch (iDest)
			{
			case BLOCK_NORMAL:
				m_Blocklist[BLOCK_NORMAL].push_back(CAbstractFactory<CNormalBlock>::Create(tTemp.fX, tTemp.fY));
				break;

			case BLOCK_COIN:
				m_Blocklist[BLOCK_COIN].push_back(CAbstractFactory<CCoinBlock>::Create(tTemp.fX, tTemp.fY));
				break;

			case BLOCK_ITEM:
				m_Blocklist[BLOCK_ITEM].push_back(CAbstractFactory<CItemBlock>::Create(tTemp.fX, tTemp.fY));
				break;
			}
		}
		CloseHandle(hFile);

		return;

	case 3:
		//	Block
		hFile = CreateFile(L"../Data/Save3/ObjBlock.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Block", L"Error", MB_OK);
			return;
		}
		dwByte = 0;
		dwTypeByte = 0;
		tTemp = {};
		iDest = 0;
		typeTemp = BLOCK_END;

		while (true)
		{
			ReadFile(hFile, &tTemp, sizeof(INFO), &dwByte, nullptr);
			ReadFile(hFile, &iDest, sizeof(int), &dwTypeByte, nullptr);
			if (0 == dwByte)
				break;
			if (0 == dwTypeByte)
				break;

			switch (iDest)
			{
			case BLOCK_NORMAL:
				m_Blocklist[BLOCK_NORMAL].push_back(CAbstractFactory<CNormalBlock>::Create(tTemp.fX, tTemp.fY));
				break;

			case BLOCK_COIN:
				m_Blocklist[BLOCK_COIN].push_back(CAbstractFactory<CCoinBlock>::Create(tTemp.fX, tTemp.fY));
				break;

			case BLOCK_ITEM:
				m_Blocklist[BLOCK_ITEM].push_back(CAbstractFactory<CItemBlock>::Create(tTemp.fX, tTemp.fY));
				break;
			}
		}
		CloseHandle(hFile);

		return;

	case 4:
		//	Block
		hFile = CreateFile(L"../Data/Save4/ObjBlock.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Block", L"Error", MB_OK);
			return;
		}
		dwByte = 0;
		dwTypeByte = 0;
		tTemp = {};
		iDest = 0;
		typeTemp = BLOCK_END;

		while (true)
		{
			ReadFile(hFile, &tTemp, sizeof(INFO), &dwByte, nullptr);
			ReadFile(hFile, &iDest, sizeof(int), &dwTypeByte, nullptr);
			if (0 == dwByte)
				break;
			if (0 == dwTypeByte)
				break;

			switch (iDest)
			{
			case BLOCK_NORMAL:
				m_Blocklist[BLOCK_NORMAL].push_back(CAbstractFactory<CNormalBlock>::Create(tTemp.fX, tTemp.fY));
				break;

			case BLOCK_COIN:
				m_Blocklist[BLOCK_COIN].push_back(CAbstractFactory<CCoinBlock>::Create(tTemp.fX, tTemp.fY));
				break;

			case BLOCK_ITEM:
				m_Blocklist[BLOCK_ITEM].push_back(CAbstractFactory<CItemBlock>::Create(tTemp.fX, tTemp.fY));
				break;
			}
		}
		CloseHandle(hFile);

		return;
	}

	return;
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


