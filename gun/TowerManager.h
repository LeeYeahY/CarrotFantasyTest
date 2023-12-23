#pragma once
#ifndef _TOWER_MANAGER_
#define _TOWER_MANAGER_

#include "PublicDefine.h"
#include <functional>

class TowerManager:public Ref//��������������ü���
{
public:
	CREATE_INSTANCE_FUNC(TowerManager);//����TMʵ���ĺ���
	DESTROY_INSTANCE_FUNC();//�����ͷ�TMʵ���ĺ���
	virtual TowerVec& GetTowerVec();//��ȡָ��ǰ������Vector��ָ��
	virtual void SetFuncAddTowerLayer(const std::function<void(Entity*)>& AddTower);//��ʼ���������ĺ�����AddTowerΪ����ָ��
	virtual void ClearManager();//������Ĺ���Ա
	virtual void SetFuncCheckMoney(const std::function<int()>& CheckMoney);//���ü���������ĺ�����CheckMoneyΪ����ָ��
	virtual int GetMoney();//��ȡ��ǰ�������
protected:
	friend class Tower;
	virtual void AddNewTower(Tower* NewTower);//����·������ĺ���
	virtual void RecordTowerDead();//��¼���������ĺ���
	virtual bool Init();//��ʼ��
	virtual void RemoveTower(Ref*Tower);
private:
	TowerVec* Towers = nullptr;//ָ������vector��ָ�룬��ʼΪ��
	std::function<void(Entity*)> AddTower;//������ĺ���ָ��
	std::function<int()> CheckMoney;//����������ĺ���ָ��
	TowerManager* Instance;//��������ʵ��

	TowerManager();//���캯��
	virtual~TowerManager();//��������
};
#endif _TOWER_MANAGER_
