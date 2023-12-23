#include "BulletFactory.h"
#include "BulletBase.h"
#include "VictimEntityBase.h"
#include "Tower.h"


BulletBase* BulletFactory::CreateBullet(const int& BulletId, Tower* Tower, VictimEntityBase* VictimEntity)
{
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Themes/Towers/TBottle-hd.plist", "Themes/Towers/TBottle-hd.png");
	cache->addSpriteFramesWithFile("Themes/Towers/TFan-hd.plist", "Themes/Towers/TFan-hd.png");
	cache->addSpriteFramesWithFile("Themes/Towers/TShit-hd.plist", "Themes/Towers/TShit-hd.png");

	auto pBullet = BulletBase::Create(BulletId, VictimEntity);//�����ӵ����ͼ��ز�ͬ�ľ���֡
	pBullet->setRotation(90 - 180 * (VictimEntity->getPosition() - Tower->getPosition()).getAngle() / M_PI);// �����ӵ�����ת�Ƕȣ�ʹ�䳯��Ŀ��ʵ��
	if (pBullet->getMyBulletType() == en_GunBullet) {//// �����ӵ����������ӵ��ĳ�ʼλ��
		pBullet->setPosition(Tower->getPosition() + Vec2(36 * sin(pBullet->getRotation() * M_PI / 180), 36 * cos(pBullet->getRotation() * M_PI / 180)));
	}
	else {
		pBullet->setPosition(Tower->getPosition());
	}

	pBullet->DoMove();// ִ���ӵ����ƶ���Ϊ
	return pBullet;
}