#pragma once
#include "Block.h"
#include "FlagBlock.h"

class CBlockMgr
{
private:
	CBlockMgr();
	~CBlockMgr();

public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

public:
	bool		CollisionBlock(RECT Player, float _fX, float * Change_fY); //X값은 값을 받기 위한 것. Y값은 좌표값 변경을 위해서
	bool		CollisionBlock_Ex(INFO Player, float * Change_fY);

	void		Add_Object(BLOCK_LIST _ID, CObj* pObj);
	int			Check_Rect(INFO Player, INFO pTarget, float* _pX, float* _pY);
	bool		Collision_with_Direction(CObj* _Sour);
	list<CObj*> Get_Flaglist(void) { return m_Blocklist[BLOCK_FLAG]; }
	void		Col_Player(CObj* _thisBlock, DIRECTION _eDir);
	void		Check_BreakBlock(CObj* _thisBlock);
	void		Create_RandItem(CObj* _thisBlock);

public:
	void	Save_File(void);
	void	Load_File(int _iStage);

public:
	static CBlockMgr* Get_Instance(void)
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CBlockMgr;

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

private:
	static CBlockMgr* m_pInstance;
	list<CObj*>		m_Blocklist[BLOCK_END];
	list<CObj*>		m_listPlayer;

};

