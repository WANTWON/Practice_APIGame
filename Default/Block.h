#pragma once
#include "Obj.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"

class CBlock abstract :
	public CObj
{
public:
	CBlock();
	virtual ~CBlock();

public:
	virtual void Initialize(void)	PURE;
	virtual int  Update(void)		PURE;
	virtual void Late_Update(void)	PURE;
	virtual void Release(void)		PURE;
	virtual void Render(HDC hDC)	PURE;

public:
	bool	Get_IsItem(void) { return m_bItem; }
	const BLOCK_LIST Get_BlockType(void) const { return m_BlockType; }

	void	Set_Type(BLOCK_LIST _Block) { m_BlockType = _Block; }


protected:
	bool	m_bItem;
	BLOCK_LIST m_BlockType;


private:
	bool	m_bCreate;

};

