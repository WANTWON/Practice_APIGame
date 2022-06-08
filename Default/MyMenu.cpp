#include "stdafx.h"
#include "MyMenu.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "ObjMgr.h"


CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Start.bmp", L"Start");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Edit.bmp", L"Edit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Exit.bmp", L"Exit");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Menu.bmp", L"Menu");

	// 여기서 부터 하면 됨

	CObj* pObj = CAbstractFactory<CMyButton>::Create(200.f, 400.f);
	pObj->Set_FrameKey(L"Start");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(400.f, 400.f);
	pObj->Set_FrameKey(L"Edit");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(600.f, 400.f);
	pObj->Set_FrameKey(L"Exit");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pObj);

}

void CMyMenu::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BUTTON);
}

int CMyMenu::Update()
{
	return 0;
}

void CMyMenu::Late_Update()
{
}

void CMyMenu::Render(HDC hDC)
{
}
