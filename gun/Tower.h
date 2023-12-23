#ifndef _TOWER_BASE_
#define _TOWER_BASE_
#include "Entity.h"
#pragma once

class VictimEntityBase;//为定义受害者类，先声明受害者类

class Tower:public Entity 
{
protected:
	Sprite* MyTower;//指向塔面板的指针
	Sprite* Grade;//指向等级面板的指针
	VictimEntityBase* Target;//攻击目标

	virtual bool Initiate(const int Id);
	virtual void InitTower();
	virtual void DeadMove(const std::string& DeadImageFile = "")override;//override意为正在重写基类中的虚函数
	virtual void Attack(float Delta);//进行攻击
	virtual void AttackMove();//发射子弹时的动作
	virtual void Rotate(float Delta);//旋转一定的角度
	virtual void CheckTarget(float Delta);//检查攻击目标
	virtual void ChooseTarget();//选择攻击目标
	virtual void MissTarget();
	virtual void CheckTargetIsOutOfRange();
		

	CC_SYNTHESIZE_PASS_BY_REF(int, BulletId, BulletId);//保存子弹所在结点编号的变量
	CC_SYNTHESIZE_PASS_BY_REF(int, AttackRange, AttackRange);//保存该防御塔攻击速度的变量
	CC_SYNTHESIZE_PASS_BY_REF(int, AttackSpace, AttackSpace);//保存该防御塔攻击范围的变量
	CC_SYNTHESIZE_PASS_BY_REF(std::string, UpCost, UpCost);//保存防御塔升级成本的变量
	CC_SYNTHESIZE_PASS_BY_REF(int, AttackUp, AttackUp);
	CC_SYNTHESIZE_PASS_BY_REF(bool, IsRotate, IsRotate);//表示防御塔能否发生旋转的变量
	CC_SYNTHESIZE_PASS_BY_REF(int, CreateCost, CreateCost);//保存防御塔建造成本的变量
	CC_SYNTHESIZE_PASS_BY_REF(bool, HaveTarget, HaveTarget);//标识防御塔是否有攻击目标的变量
public:
	static Tower* PlaceTower(const int Id);//放置防御塔
	virtual void GradeUp();//防御塔升级
	virtual int GetUpCost();
	virtual void ShowGrade();//显示防御塔等级的接口函数
	virtual void HideGrade();//隐藏防御塔等级
	virtual bool IsInAttackRange(const Vec2& Pos);//判断目标当前是否在攻击范围内
	virtual void SetTarget(VictimEntityBase* NewTarget);//设置攻击目标
	virtual bool ChangeTarget();//切换攻击目标
	virtual ~Tower();//析构函数
};

#endif