#include "TowerRocket.h"
#include "MonsterBase.h"
#include "BarrierBase.h"
#include "MonsterManager.h"
#include "BarrierManager.h"
#include "SoundUtil.h"

bool TowerRocket::Initiate()
{
	bool Ret = false;
	do
	{
		CC_BREAK_IF(!Tower::Initiate(Id));

		Ret = true;
	} while (0);
	return Ret;
}

void TowerRocket::Attack(float Delta) {
	if (!Target || Target->getIsDead()) 
		return;
	auto FireActionCF = CallFunc::create([=]() { AttackMove(); });

	auto CreateBulletCF = CallFunc::create([=]() {
		if (!Target) 
			return;
		BulletRocket* Bullet = BulletRocket::create(BulletId, Target);
		Bullet->setPosition(this->getPosition());
		Bullet->setRotation(90 - 180 * (Target->getPosition() - this->getPosition()).getAngle() / M_PI);
		Bullet->DoMove();
		});

	this->runAction(Sequence::create(FireActionCF, DelayTime::create(0.35), CreateBulletCF, NULL));
}