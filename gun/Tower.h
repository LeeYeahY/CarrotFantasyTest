#ifndef _TOWER_BASE_
#define _TOWER_BASE_
#include "Entity.h"
#pragma once

class VictimEntityBase;//Ϊ�����ܺ����࣬�������ܺ�����

class Tower:public Entity 
{
protected:
	Sprite* MyTower;//ָ��������ָ��
	Sprite* Grade;//ָ��ȼ�����ָ��
	VictimEntityBase* Target;//����Ŀ��

	virtual bool Initiate(const int Id);
	virtual void InitTower();
	virtual void DeadMove(const std::string& DeadImageFile = "")override;//override��Ϊ������д�����е��麯��
	virtual void Attack(float Delta);//���й���
	virtual void AttackMove();//�����ӵ�ʱ�Ķ���
	virtual void Rotate(float Delta);//��תһ���ĽǶ�
	virtual void CheckTarget(float Delta);//��鹥��Ŀ��
	virtual void ChooseTarget();//ѡ�񹥻�Ŀ��
	virtual void MissTarget();
	virtual void CheckTargetIsOutOfRange();
		

	CC_SYNTHESIZE_PASS_BY_REF(int, BulletId, BulletId);//�����ӵ����ڽ���ŵı���
	CC_SYNTHESIZE_PASS_BY_REF(int, AttackRange, AttackRange);//����÷����������ٶȵı���
	CC_SYNTHESIZE_PASS_BY_REF(int, AttackSpace, AttackSpace);//����÷�����������Χ�ı���
	CC_SYNTHESIZE_PASS_BY_REF(std::string, UpCost, UpCost);//��������������ɱ��ı���
	CC_SYNTHESIZE_PASS_BY_REF(int, AttackUp, AttackUp);
	CC_SYNTHESIZE_PASS_BY_REF(bool, IsRotate, IsRotate);//��ʾ�������ܷ�����ת�ı���
	CC_SYNTHESIZE_PASS_BY_REF(int, CreateCost, CreateCost);//�������������ɱ��ı���
	CC_SYNTHESIZE_PASS_BY_REF(bool, HaveTarget, HaveTarget);//��ʶ�������Ƿ��й���Ŀ��ı���
public:
	static Tower* PlaceTower(const int Id);//���÷�����
	virtual void GradeUp();//����������
	virtual int GetUpCost();
	virtual void ShowGrade();//��ʾ�������ȼ��Ľӿں���
	virtual void HideGrade();//���ط������ȼ�
	virtual bool IsInAttackRange(const Vec2& Pos);//�ж�Ŀ�굱ǰ�Ƿ��ڹ�����Χ��
	virtual void SetTarget(VictimEntityBase* NewTarget);//���ù���Ŀ��
	virtual bool ChangeTarget();//�л�����Ŀ��
	virtual ~Tower();//��������
};

#endif