#pragma once

#ifndef __CarrotFantasy__BulletBase__
#define __CarrotFantasy__BulletBase__

#include "Entity.h"
#include "DynamicPropertyInterFace.h"


class BulletBase :public Entity, public DynamicPropertyInterFace
{
public:
    std::set<int>& GetIdMap();//��ȡ�ӵ�ID�ļ��ϵ�����

    virtual void DoMove();//ִ���ӵ��ƶ�

    static BulletBase* Create(const int& Id, VictimEntityBase* VictimEntity);//�����ӵ�ʵ��
   
    virtual AtkProperty GetAtkProperty();//��ȡ�ӵ��Ĺ�������

    virtual void DeadMove(const std::string& DeadImageFile = ""); //�ӵ�����

    virtual void DoAction(const float& Dt); //ִ���ӵ�����

protected:

    virtual bool Init(const int& _Id, VictimEntityBase* VictimEntity);//��ʼ���ӵ�
   
    CC_SYNTHESIZE_PASS_BY_REF(int, myAtkState, MyAtkState);//����״̬

    CC_SYNTHESIZE_PASS_BY_REF(int, myBulletType, MyBulletType);//�ӵ�����

    CC_SYNTHESIZE_PASS_BY_REF(int, myDeadActCount, MyDeadActCount);//���������ļ���

    VictimEntityBase* pAtkTarget = nullptr;//����Ŀ���ָ��

    std::set<int>* IdMap = nullptr;//�ӵ�ID�ļ���ָ��
};
#endif