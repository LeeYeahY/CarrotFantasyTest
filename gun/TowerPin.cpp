#include "TowerPin.h"
#include "MonsterManager.h"
#include "MonsterBase.h"
#include "BarrierManager.h"
#include "TowerManager.h"
#include "BulletPin.h"

bool TowerPin::Initiate() {
	bool Ret = false;
	do
	{
		CC_BREAK_IF(!Tower::Initiate(Id));
		Ret = true;

	} while (0);
	return Ret;
}
void TowerPin::Attack(float Delta) {
	if (!Target || Target->getIsDead()) return;
	auto FireActionCF = CallFunc::create([=]() { AttackMove(); });

	auto CreateBulletCF = CallFunc::create([=]() {
		if (!Target) return;
		BulletPin* Bullet = BulletPin::create(BulletId,Target);
		Bullet->setPosition(this->getPosition());
		Bullet->setRotation(90 - 180 * (Target->getPosition() - this->getPosition()).getAngle() / M_PI);
		Bullet->DoMove();
		});

	this->runAction(Sequence::create(FireActionCF, DelayTime::create(0.35), CreateBulletCF, NULL));

}