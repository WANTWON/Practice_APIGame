#pragma once
#include "Logo.h"
#include "MyMenu.h"
class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();
public:
	void Scene_Change(SCENEID eScene);
	void Update(void);
	void Late_Update(void);
	void Render(void);
	void Release(void);

public:
	static CSceneMgr* Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CSceneMgr;
		
		return m_pInstance;
	}
	static CSceneMgr* Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CSceneMgr*		m_pInstance;
	CScene*					m_pScene;


	SCENEID					m_ePreScene;				//먼저
	SCENEID					m_eCurScene;				//나중
};

