#include "stdafx.h"
#include "CollisionMgr.h"
#include "Item.h"
#include "Monster.h"
#include "Player.h"
#include "Define.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

RECT rc = {};

int CCollisionMgr::Collision_Rect(list<CObj*> Sour, list<CObj*> Dest)
{
	int iScore = 0;
	for (auto& iter = Sour.begin(); iter != Sour.end(); )
	{
		int iter_count = 0;
		for (auto& Monster_iter = Dest.begin(); Monster_iter != Dest.end(); )
		{
			if ((Dest.size() != 0) && (IntersectRect(&rc, &((*iter)->Get_Rect()), &((*Monster_iter)->Get_Rect()))))
			{
				(*iter)->Set_Dead(true);
				(*Monster_iter)->Set_Dead(true);
				iScore += rand() % 10 + 5;
			}
			Monster_iter++;
		}
		iter++;
	}
	return iScore;
}



void CCollisionMgr::Collision_Rect_Ex(list<CObj*> _Sour, list<CObj*> _Dest)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			float fWidth = 0.f;
			float fHeight = 0.f;

			if (Check_Rect(Dest, Sour, &fWidth, &fHeight))
			{
				if (fWidth > fHeight)  //»óÇÏ Ãæµ¹
				{
					if (Dest->Get_Info().fY > Sour->Get_Info().fY)
					{
						Sour->Set_PosY(-fHeight);
					}
					else
					{
						Sour->Set_PosY(fHeight);
					}

				}
				else //ÁÂ¿ì Ãæµ¹ 
				{
					if (Dest->Get_Info().fX > Sour->Get_Info().fX)
					{
						Sour->Set_PosX(-fWidth);
					}
					else
					{
						Sour->Set_PosX(fWidth);
					}
				}

			}

		}
	}
}


int CCollisionMgr::Check_Rect(CObj* Sour, CObj* Dest, float* _pX, float* _pY)
{
	float fWidth = abs(Sour->Get_Info().fX - Dest->Get_Info().fX);
	float fHeight = abs(Sour->Get_Info().fY - Dest->Get_Info().fY);

	float fRadiusX = (Sour->Get_Info().fCX + Dest->Get_Info().fCX)*0.5f;
	float fRadiusY = (Sour->Get_Info().fCY + Dest->Get_Info().fCY)*0.5f;

	if ((fWidth <= fRadiusX) && (fHeight <= fRadiusY))
	{
		*_pX = fRadiusX - fWidth;
		*_pY = fRadiusY - fHeight;
		return true;
	}
	else
		return false;
}


void CCollisionMgr::Step_on_Mushroom(list<CObj*> _Sour, list<CObj*> _Dest)
{

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			float fWidth = 0.f;
			float fHeight = 0.f;

			if (Check_Rect(Dest, Sour, &fWidth, &fHeight))
			{
				if (fWidth > fHeight)  //»óÇÏ Ãæµ¹
				{
					if (Dest->Get_Info().fY >= Sour->Get_Info().fY)
					{
						dynamic_cast<CMonster*>(Dest)->Be_Attacked();
						dynamic_cast<CPlayer*>(Sour)->Set_bJump(true);
					}
					else
					{
						Sour->Set_PosY(fHeight);
					}

				}
				else //ÁÂ¿ì Ãæµ¹ 
				{
					if (Dest->Get_Info().fX > Sour->Get_Info().fX)
					{
						Sour->Set_PosX(-fWidth);
					}
					else
					{
						Sour->Set_PosX(fWidth);
					}
				}

			}
		}
	}
}

DIRECTION CCollisionMgr::Col_ReturnDir(list<CObj*> _Sour, list<CObj*> _Dest)
{
	// _Sour = ºÎµúÈù
	// _Dest = ºÎµúÈû ´çÇÑ
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			float fWidth = 0.f;
			float fHeight = 0.f;

			if (Check_Rect(Dest, Sour, &fWidth, &fHeight))
			{
				float fX = Sour->Get_Info().fX - Dest->Get_Info().fX;
				float fY = Sour->Get_Info().fY - Dest->Get_Info().fY;

				float fR = sqrtf((fX * fX) + (fY * fY));

				float fAngle = (180 / PI) * acos(fX / fR);
				if (Sour->Get_Info().fY <= Dest->Get_Info().fY)
					fAngle = 360 + (-1.f * fAngle);

				if (fAngle > 315.f || fAngle <= 45.f)
				{
					return DIR_RIGHT;
				}
				else if (fAngle > 45.f && fAngle <= 135.f)
				{
					return DIR_DOWN;
				}
				else if (fAngle > 135.f && fAngle <= 225.f)
				{
					return DIR_LEFT;
				}
				else if (fAngle > 225.f && fAngle <= 315.f)
				{
					return DIR_UP;
				}
			}
		}
	}
}

DIRECTION CCollisionMgr::Col_ReturnDir(list<CObj*> _Sour, CObj* _Dest)
{
	// _Sour = ºÎµúÈù
	// _Dest = ºÎµúÈû ´çÇÑ
	for (auto& Sour : _Sour)
	{
		float fWidth = 0.f;
		float fHeight = 0.f;

		if (Check_Rect(_Dest, Sour, &fWidth, &fHeight))
		{
			float fX = Sour->Get_Info().fX - _Dest->Get_Info().fX;
			float fY = Sour->Get_Info().fY - _Dest->Get_Info().fY;

			float fR = sqrtf((fX * fX) + (fY * fY));

			float fAngle = (180 / PI) * acos(fX / fR);
			if (Sour->Get_Info().fY <= _Dest->Get_Info().fY)
				fAngle = 360 + (-1.f * fAngle);

			if (fAngle > 316.f || fAngle < 44.f)
			{
				return DIR_RIGHT;
			}
			else if (fAngle >= 45.f && fAngle <= 134.f)
			{
				return DIR_DOWN;
			}
			else if (fAngle > 136.f && fAngle < 224.f)
			{
				return DIR_LEFT;
			}
			else if (fAngle >= 225.f && fAngle < 315.f)
			{
				return DIR_UP;
			}
		}
	}
}

int CCollisionMgr::Collision_Sphere(list<CObj*> Sour, list<CObj*> Dest)
{
	int iScore = 0;

	for (auto& Sour_iter = Sour.begin(); Sour_iter != Sour.end(); )
	{
		int iter_count = 0;
		for (auto& Dest_iter = Dest.begin(); Dest_iter != Dest.end(); )
		{
			if ((Dest.size() != 0) && (ChecK_Sphere(*Sour_iter, *Dest_iter)))
			{
				(*Sour_iter)->Set_Dead(true);
				(*Dest_iter)->Set_Dead(true);
				iScore += rand() % 10 + 5;

			}
			Dest_iter++;
		}
		Sour_iter++;
	}
	return iScore;
}

int CCollisionMgr::Collision_Coin(CObj* Player, list<CObj*> Items)
{
	int iScore = 0;

	for (auto& item : Items)
	{
		if (IntersectRect(&rc, &Player->Get_Rect(), &item->Get_Rect()))
		{
			CItem* _Item = dynamic_cast<CItem*>(item);

			if (_Item->Get_Type() == ITEM_COIN)
			{
				iScore += 1;
				_Item->Set_Dead(true);
			}
		}
	}

	return iScore;
}

bool CCollisionMgr::ChecK_Sphere(CObj* Sour, CObj* Dest)
{
	float fRadius = (Sour->Get_Info().fCX + Dest->Get_Info().fCX) * 0.5f; //µÎ ¿øÀÇ ¹ÝÁö¸§À» ´õÇÑ °ª

																		  //Àý´ë°ªÀ» ¾º¿öÁÖ´Â ÇÔ¼ö
	float fWidth = fabs(Sour->Get_Info().fX - Dest->Get_Info().fX);
	float fHeight = fabs(Sour->Get_Info().fY - Dest->Get_Info().fY);

	float fDistance = sqrtf((fWidth* fWidth) + (fHeight*fHeight));

	if (fRadius >= fDistance)
		return true;
	else
		return false;
}