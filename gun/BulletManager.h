#pragma once
#include "PublicDefine.h"

class Entity;
class BulletManager : public Ref//֧�����ü������ڴ����
{
public:
    CREATE_INSTANCE_FUNC(BulletManager);//����BulletManager��ʵ��
    DESTROY_INSTANCE_FUNC();//����BulletManager��ʵ��

    virtual BulletVec& GetBulletVec();//��ȡ�ӵ�����

    virtual void SetFuncAddBulletLayer(const std::function<void(Entity*)>& FuncAddBulletLayer);//����һ���ص���������������ӵ���ͼ����,��֪ͨ����ͼ��

    virtual void CheckBulletIsDead();//����ӵ��Ƿ��Ѿ�����

    virtual void ClearManager();//���������

protected:

    friend class BulletBase;

    virtual void AddBullet(BulletBase* Bullet);//����ӵ�����������

    virtual bool Init();//��ʼ��

private:

    BulletVec* pBulletVec = nullptr;

    std::function<void(Entity*)> funcAddBulletLayer;//�ص���������������ӵ���ͼ����

private:

    BulletManager();

    virtual ~BulletManager();

    BulletManager(const BulletManager&) = delete;

    BulletManager& operator=(const BulletManager&) = delete;

};