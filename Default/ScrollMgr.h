#pragma once
class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	static		CScrollMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CScrollMgr;

		return m_pInstance;
	}

	static		void			Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	float		Get_ScrollX(void) { return m_fScrollX; }
	void		Set_ScrollX(float _x) { m_fScrollX += _x; }
	void		Zero_Scroll(void) { m_fScrollX = 0; }

private:
	static		CScrollMgr*		m_pInstance;

	float		m_fScrollX;
	float		m_fScrollY;
};



