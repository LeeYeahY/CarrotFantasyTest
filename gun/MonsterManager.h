#pragma once

#ifndef __Carrot__MonsterManager__
#define __Carrot__MonsterManager__

#include "PublicDefine.h"

class Entity;

class MonsterManager : public Ref
{
public:

    CREATE_INSTANCE_FUNC(MonsterManager);

    DESTROY_INSTANCE_FUNC();

    virtual MonsterVec& GetMonsterVec();// ��ȡ��������������

    virtual void SetFuncAddMonsterToLayer(const std::function<void(Entity*)>& FuncAddMonsterToLayer);// ������ӹ��ﵽͼ��Ļص�����

    virtual void ClearManager();// ���������״̬

    virtual void ClearAtkLockState();// ���������������״̬

protected:

    friend class MonsterBase;

    virtual void OpenCheckGameEnd(Ref* Sender);// ���������Ϸ�������¼�

    virtual void AddMonster(MonsterBase* Bullet); // �������������ӹ���

    virtual bool Init();// ��ʼ��

    virtual void RegisterDeadEvent();// ע����������¼�

    virtual void RemoveMonsterFromManager(Ref* Monster);// �ӹ��������Ƴ�����

private:

    MonsterVec* pMonsterVec = nullptr;// ��������

    std::function<void(Entity*)> funcAddMonsterToLayer;// ��ӹ��ﵽͼ��Ļص�����

    bool IsOpenCheckGameEnd = false;

private:

    MonsterManager();

    virtual ~MonsterManager();

    MonsterManager(const MonsterManager&) = delete;// ��ֹ�������캯��

    MonsterManager& operator=(const MonsterManager&) = delete;// ��ֹ��ֵ����������

};
#endif