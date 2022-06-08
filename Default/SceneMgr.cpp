#include "stdafx.h"
#include "SceneMgr.h"


CSceneMgr*		CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	:m_pScene(nullptr), m_eCurScene(SC_END), m_ePreScene(SC_END)
{
}
CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eScene)
{
	m_eCurScene = eScene;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SC_LOGO:
			m_pScene = new CLogo;
			break;
		case SC_MENU:
			m_pScene = new CMyMenu;
			break;
		case SC_EDIT:
			break;
		case SC_STAGE:
			break;
		}

		m_pScene->Initialize();

		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::Update(void)
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update(void)
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release(void)
{
	Safe_Delete<CScene*>(m_pScene);	
}
