#pragma once
#include "Obj.h"
#include "Bullet.h"
#include "Player.h"

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

	static CObj* Create(float _fX, float _fY, DIRECTION eDir = DIR_END)
	{
		CObj* pInstance = new T;
		pInstance->Initialize();
		pInstance->Set_Pos(_fX, _fY);

		CBullet* pBullet = dynamic_cast<CBullet*>(pInstance);
		if (pBullet)
			pBullet->Set_StartPos(_fX, _fY);

		if (eDir != DIR_END)
			pInstance->Set_Dir(eDir);

		return pInstance;
	}

	static CObj* Create_with_Target(float _fX, float _fY,CObj* pTarget)
	{
		CObj* pInstance = new T;
		pInstance->Initialize();
		pInstance->Set_Pos(_fX, _fY);
		pInstance->Set_Target(pTarget);

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
		pInstance->Initialize();
		pInstance->Set_Pos(_fX, _fY);
		static_cast<CItem*>(pInstance)->Set_Type(_type);
	
		return pInstance;
	}



	static CObj*  Create(int _Life) 
	{
		CObj* pInstance = new T;
		pInstance->Initialize();
		dynamic_cast<CPlayer*>(pInstance)->Set_Life(_Life);
		return pInstance;
	}
};

