#pragma once
#include "Obj.h"


class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

	static int Collision_Rect(list<CObj*> Sour, list<CObj*> Dest);
	static int Collision_Sphere(list<CObj*> Sour, list<CObj*> Dest);
	static bool ChecK_Sphere(CObj* Sour, CObj* Dest);
	static void Collision_Rect_Ex(list<CObj*> Sour, list<CObj*> Dest);
	static int Check_Rect(CObj* Sour, CObj* Dest, float* _pX, float* _pY);
	static int Collision_Coin(CObj* Player, list<CObj*> Items);
	static int Step_on_Mushroom(list<CObj*> _Sour, list<CObj*> _Dest);
	
	static DIRECTION	Col_ReturnDir(list<CObj*> _Sour, list<CObj*> _Dest);
	static DIRECTION	Col_ReturnDir(list<CObj*> _Sour, CObj* _Dest);
	static void			 Collision_Item(CObj* Player, list<CObj*> Items);

	static int Collision_Bullet(CObj* _This, list<CObj*> _Bullet);
};