#pragma once

#include "PointNumbers.h"

class CUIMgr
{
private:
	CUIMgr();
	~CUIMgr();

	static CUIMgr* m_pInstance;
	list<CPointNumbers*> m_pUIList;

public:
	void Release(void);

	// 프레임마다 실행되는 함수 
	void Update(void);
	void Late_Update(void);
	void Render(HDC hDC);

	void Add(CPointNumbers* pPointNumber);

	static CUIMgr* Get_Instance(void)
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CUIMgr;

		return m_pInstance;
	}

	static void Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
};

