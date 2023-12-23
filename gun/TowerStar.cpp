#include "TowerStar.h"
#include "BulletStar.h"
#include "VictimEntityBase.h"

bool TowerStar::Initiate()
{
	
	bool Ret = false;
	do
	{
		CC_BREAK_IF(!Tower::Initiate(Id));//如果初始化失败，则退出循环，返回false
		unschedule(schedule_selector(TowerStar::Rotate));//取消星星塔旋转的调度执行

		Ret = true;//返回true
	} while (0);
	return Ret;

}

void TowerStar::Attack(float Delta) {
	if (!Target || Target->getIsDead()) //如果目标为空或已经死亡，则什么也不做直接返回
		return;
	auto AttackActionCF = CallFunc::create([=]() //创建一个回调函数，其参数为一个Lambdas表达式
		{ AttackMove(); });//该表达式中调用执行攻击动作的函数

	auto CreateBulletCF = CallFunc::create([=]() {//创建回调函数
		if (!Target) //如果攻击目标为空，则直接返回
			return;
		BulletStar* Bullet = BulletStar::create(getBulletId(),Target);//创建一个星星塔的子弹
		Bullet->setPosition(this->getPosition());//设置子弹的位置与塔的位置相同
		Bullet->DoMove();//调用子弹移动的函数
		});

	this->runAction(Sequence::create(AttackActionCF, DelayTime::create(0.35), CreateBulletCF, NULL));
	//执行动作序列，先攻击，然后进行一点点延时，然后发射子弹
}