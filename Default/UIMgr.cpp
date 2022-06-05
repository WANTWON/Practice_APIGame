#include "stdafx.h"
#include "UIMgr.h"
#include "Function.h"
#include "Define.h"

CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr()
{

}

CUIMgr::~CUIMgr()
{
	Release();
}

void CUIMgr::Release(void)
{
	for (auto& iter = m_pUIList.begin(); iter != m_pUIList.end(); )
	{
		Safe_Delete<CPointNumbers*>(*iter);
		iter = m_pUIList.erase(iter);
	}

	m_pUIList.clear();
}

void CUIMgr::Update(void)
{
	int iEvent = 0;
	for (auto& iter = m_pUIList.begin(); iter != m_pUIList.end(); )
	{
		iEvent = (*iter)->Update();

		if (iEvent == OBJ_DEAD)
		{
			Safe_Delete<CPointNumbers*>(*iter);
			iter = m_pUIList.erase(iter);
		}
		else
			++iter;
	}
}

void CUIMgr::Late_Update(void)
{
	for (auto& point : m_pUIList)
		point->Late_Update();
}

void CUIMgr::Render(HDC hDC)
{
	for (auto& point : m_pUIList)
		point->Render(hDC);
}

void CUIMgr::Add(CPointNumbers * pPointNumber)
{
	m_pUIList.push_back(pPointNumber);
}