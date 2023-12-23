#pragma once
#ifndef _TOWER_OPT_
#define _TOWER_OPT_
#include "cocos2d.h"
#include <functional>
using namespace cocos2d;
class TowerBase;

class TowerOptButton :public Node
{
public:
	CREATE_FUNC(TowerOptButton);
	TowerOptButton();
	virtual ~TowerOptButton();
	virtual void HideTowerOpt();
	virtual void ShowTowerOpt();
	virtual void SetFuncCheckMoney(const std::function<int()>& MyCheckMoney);
	virtual void CreateTowerMenu();
	virtual void GradeTowerMenu(Tower* TouchTower);
	virtual void ShowMenu();
	virtual void HideMenu();

protected:
	virtual bool Initiate();
	virtual void CreateMenuAndItems();
	virtual void ChangeItem(float Delta);

protected:
	bool KeySpVisible;
	Sprite* KeySp;
	Menu* CreateMenu;
	Menu* GradeMenu;
	Sprite* TowerRangeSp;

	std::function<int()> CheckMoney;

	Vector<MenuItemSprite*>* CreateTowerItemSpVec = nullptr;
	Vector<MenuItemSprite*>* GradeTowerItemSpVec = nullptr;
};
#endif _TOWER_OPT_
