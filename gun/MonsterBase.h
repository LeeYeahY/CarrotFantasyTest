#pragma once

#ifndef __Carrot__MonsterBase__
#define __Carrot__MonsterBase__
#include "VictimEntityBase.h"
#include "DynamicPropertyInterFace.h"

class MoveControllerBase;

class MonsterBase : public VictimEntityBase, public DynamicPropertyInterFace
{
    friend class MonsterFactory;

public:
    
    static MonsterBase* Create(const int& IId); //��������ָ��ID�Ĺ���ʵ��

    void SetMaxSpeed(const int& Speed);

protected:
    
    virtual void DeadMove(const std::string& SDeadImageFile = "")override;
  
    virtual void DoAction(const float& Dt);
    
    virtual bool Init(const int& IId);
    
    virtual void HurtMove();
    
    virtual void CreateAnimation();
    
    virtual void MonsterSound();
    
    CC_SYNTHESIZE_PASS_BY_REF(bool, myIsLeft, MyIsLeft);//���ﳯ��

    MoveControllerBase* pMoveController = nullptr;
};
#endif