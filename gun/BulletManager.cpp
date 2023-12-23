#ifndef __BulletManager__
#define __BulletManager__


#include "BulletManager.h"
#include "BulletBase.h"

BulletManager* BulletManager::gInstance;

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
    CC_SAFE_DELETE(pBulletVec);
}

bool BulletManager::Init()
{
    bool Ret = false;
    do
    {
        pBulletVec = new Vector<BulletBase*>();// ����һ�� Vector �������洢�ӵ������ָ��

        Ret = true;
    } while (0);

    return Ret;
}

Vector<BulletBase*>& BulletManager::GetBulletVec()
{
    return *pBulletVec;
}

void BulletManager::AddBullet(BulletBase* Bullet)
{
    if (pBulletVec) pBulletVec->pushBack(Bullet);
    funcAddBulletLayer(Bullet);
}

void BulletManager::SetFuncAddBulletLayer(const std::function<void(Entity*)>& FuncAddBulletLayer)
{
    funcAddBulletLayer = FuncAddBulletLayer;
}

void BulletManager::CheckBulletIsDead()
{
    for (auto iterBullet = pBulletVec->begin(); iterBullet != pBulletVec->end();)//ʹ�õ����������ӵ��б�
    {
        if ((*iterBullet)->getIsDead()) iterBullet = pBulletVec->erase(iterBullet);//����ӵ������������ӵ��б����Ƴ���ǰ�ӵ�����������һ����Ч�ĵ�����
        else ++iterBullet;
    }
}

void BulletManager::ClearManager()
{
    pBulletVec->clear();
}

#endif