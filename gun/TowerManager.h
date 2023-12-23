#pragma once
#ifndef _TOWER_MANAGER_
#define _TOWER_MANAGER_

#include "PublicDefine.h"
#include <functional>

class TowerManager:public Ref//管理防御塔的引用计数
{
public:
	CREATE_INSTANCE_FUNC(TowerManager);//创建TM实例的函数
	DESTROY_INSTANCE_FUNC();//创建释放TM实例的函数
	virtual TowerVec& GetTowerVec();//获取指向当前防御塔Vector的指针
	virtual void SetFuncAddTowerLayer(const std::function<void(Entity*)>& AddTower);//初始化添加塔层的函数，AddTower为函数指针
	virtual void ClearManager();//清除塔的管理员
	virtual void SetFuncCheckMoney(const std::function<int()>& CheckMoney);//设置检查金币数量的函数，CheckMoney为函数指针
	virtual int GetMoney();//获取当前金币数量
protected:
	friend class Tower;
	virtual void AddNewTower(Tower* NewTower);//添加新防御塔的函数
	virtual void RecordTowerDead();//记录塔的死亡的函数
	virtual bool Init();//初始化
	virtual void RemoveTower(Ref*Tower);
private:
	TowerVec* Towers = nullptr;//指向塔的vector的指针，初始为空
	std::function<void(Entity*)> AddTower;//添加塔的函数指针
	std::function<int()> CheckMoney;//检查金币数量的函数指针
	TowerManager* Instance;//管理塔的实例

	TowerManager();//构造函数
	virtual~TowerManager();//析构函数
};
#endif _TOWER_MANAGER_
