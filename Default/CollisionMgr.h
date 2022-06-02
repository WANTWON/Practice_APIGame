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
	static void Collision_Wall(list<CObj*> Sour, list<CObj*> Wall);
	static void Collision_Wall_Player(list<CObj*> Sour, list<CObj*> Wall);
	static void Collision_Rect_Ex(list<CObj*> Sour, list<CObj*> Dest);
	static int Check_Rect(CObj* Sour, CObj* Dest, float* _pX, float* _pY);


};

