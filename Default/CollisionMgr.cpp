#include "stdafx.h"
#include "CollisionMgr.h"
#include "Item.h"

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
				if (fWidth > fHeight)  //상하 충돌
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
				else //좌우 충돌 
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

	for (auto& item : Items )
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

void CCollisionMgr::Collision_Wall(list<CObj*> Sour, list<CObj*> Wall)
{
	for (auto& iter = Sour.begin(); iter != Sour.end(); )
	{
		int iter_count = 0;
		for (auto& Monster_iter = Wall.begin(); Monster_iter != Wall.end(); )
		{
			if ((Wall.size() != 0) && (IntersectRect(&rc, &((*iter)->Get_Rect()), &((*Monster_iter)->Get_Rect()))))
			{
				(*iter)->Set_Dead(true);
				(*Monster_iter)->Set_Dead(true);
			}
			Monster_iter++;
		}
		iter++;
	}
}

void CCollisionMgr::Collision_Wall_Player(list<CObj*> Sour, list<CObj*> Wall)
{
	for (auto& Player_iter = Sour.begin(); Player_iter != Sour.end(); Player_iter++)
	{
		for (auto& Wall_iter = Wall.begin(); Wall_iter != Wall.end(); Wall_iter++)
		{
			if ((Wall.size() != 0) && (IntersectRect(&rc, &((*Player_iter)->Get_Rect()), &((*Wall_iter)->Get_Rect()))))
			{
				float fWidth = float(rc.right - rc.left);
				float fHeight = float(rc.bottom - rc.top);

				if ((*Wall_iter)->Get_Dir() == DIR_RIGHT)
					(*Player_iter)->Set_Pos((*Player_iter)->Get_Info().fX - fWidth, (*Player_iter)->Get_Info().fY);
				if ((*Wall_iter)->Get_Dir() == DIR_LEFT)
					(*Player_iter)->Set_Pos((*Player_iter)->Get_Info().fX + fWidth, (*Player_iter)->Get_Info().fY);
				if ((*Wall_iter)->Get_Dir() == DIR_DOWN)
					(*Player_iter)->Set_Pos((*Player_iter)->Get_Info().fX, (*Player_iter)->Get_Info().fY - fHeight);
				if ((*Wall_iter)->Get_Dir() == DIR_UP)
					(*Player_iter)->Set_Pos((*Player_iter)->Get_Info().fX, (*Player_iter)->Get_Info().fY + fHeight);
			}
		}
	}
}

bool CCollisionMgr::ChecK_Sphere(CObj* Sour, CObj* Dest)
{
	float fRadius = (Sour->Get_Info().fCX + Dest->Get_Info().fCX) * 0.5f; //두 원의 반지름을 더한 값

																		  //절대값을 씌워주는 함수
	float fWidth = fabs(Sour->Get_Info().fX - Dest->Get_Info().fX);
	float fHeight = fabs(Sour->Get_Info().fY - Dest->Get_Info().fY);

	float fDistance = sqrtf((fWidth* fWidth) + (fHeight*fHeight));

	if (fRadius >= fDistance)
		return true;
	else
		return false;
}