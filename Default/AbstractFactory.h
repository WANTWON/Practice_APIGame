#pragma once
#include "Obj.h"
#include "Bullet.h"
#include "Player.h"
#include "FlagBlock.h"

template <typename T>
class CAbstractFactory
{
private:
	CAbstractFactory() {}
	~CAbstractFactory() {}

public:
	static CObj*  Create() {
		CObj* pInstance = new T;
		pInstance->Initialize();

		return pInstance;
	}

	static CObj* Create(float _fX, float _fY, DIRECTION eDir = DIR_END, OBJ_LIST eID = OBJ_END)
	{
		CObj* pInstance = new T;
		pInstance->Initialize();
		pInstance->Set_Pos(_fX, _fY);

		CBullet* pBullet = dynamic_cast<CBullet*>(pInstance);
		if (pBullet)
		{
			pBullet->Set_StartPos(_fX, _fY);
			if (eID != OBJ_END)
				pBullet->Set_ID(eID);
		}
			

		if (eDir != DIR_END)
			pInstance->Set_Dir(eDir);

		return pInstance;
	}

	static CObj* Create_with_Target(float _fX, float _fY,CObj* pTarget, OBJ_LIST eID = OBJ_END)
	{
		CObj* pInstance = new T;
		pInstance->Initialize();
		pInstance->Set_Pos(_fX, _fY);
		pInstance->Set_Target(pTarget);

		if (eID != OBJ_END)
			pInstance->Set_ID(eID);

		return pInstance;
	}

	static CObj* Create(float _fX, float _fY, float _angle)
	{
		CObj* pInstance = new T;
		pInstance->Initialize();
		pInstance->Set_Pos(_fX, _fY);
		pInstance->Set_Angle(_angle);

		return pInstance;
	}
	static CObj* Create(float _left, float _top, float _right, float _bottom, DIRECTION eDir = DIR_END)
	{
		CObj* pInstance = new T;
		pInstance->Initialize();
		pInstance->Set_Rect(_left, _top, _right, _bottom);
		if (eDir != DIR_END)
			pInstance->Set_Dir(eDir);

		return pInstance;
	}

	// 아이템 팩토리
	static CObj* Create(float _fX, float _fY, ITEM_TYPE _type)
	{
		CObj* pInstance = new T;
		static_cast<CItem*>(pInstance)->Set_Type(_type);
		pInstance->Initialize();
		pInstance->Set_Pos(_fX, _fY);

		return pInstance;
	}

	static CObj* Create(float _fX, float _fY, BLOCK_LIST _Block)
	{
		CObj* pInstance = new T;
		pInstance->Initialize();
		pInstance->Set_Pos(_fX, _fY);
		static_cast<CBlock*>(pInstance)->Set_Type(_Block);

		return pInstance;
	}




	//실험용

	static CObj*  Create(float _fX, float _fY, int _Life)
	{
		CObj* pInstance = new T;
		pInstance->Initialize();
		pInstance->Set_Pos(_fX, _fY);
		dynamic_cast<CPlayer*>(pInstance)->Set_Life(_Life);
		return pInstance;
	}
	static CObj*  Create(int _Life)
	{
		CObj* pInstance = new T;
		pInstance->Initialize();
		dynamic_cast<CPlayer*>(pInstance)->Set_Life(_Life);
		return pInstance;
	}
	static CObj* Create(float _fX, float _fY,bool _Number)
	{
		CObj* pInstance = new T;
		pInstance->Initialize();
		pInstance->Set_Pos(_fX, _fY);
		dynamic_cast<CFlagBlock*>(pInstance)->Set_Number(_Number);
		return pInstance;
	}

	static CObj*  Create(SAVEOBJ Temp) {
		CObj* pInstance = new T;

		pInstance->Initialize();
		pInstance->Set_ID(Temp.m_eID);
		pInstance->Set_Dead(Temp.m_bDead);
		pInstance->Set_Dir(Temp.m_eDir);
		pInstance->Set_Pos(Temp.m_tInfo.fX, Temp.m_tInfo.fY);
		pInstance->Set_Rect(Temp.m_tRect.left, Temp.m_tRect.top, Temp.m_tRect.right, Temp.m_tRect.bottom);
		pInstance->Set_Target(Temp.m_pTarget);

		return pInstance;
	}
};

