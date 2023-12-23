#include "TowerStar.h"
#include "BulletStar.h"
#include "VictimEntityBase.h"

bool TowerStar::Initiate()
{
	
	bool Ret = false;
	do
	{
		CC_BREAK_IF(!Tower::Initiate(Id));//�����ʼ��ʧ�ܣ����˳�ѭ��������false
		unschedule(schedule_selector(TowerStar::Rotate));//ȡ����������ת�ĵ���ִ��

		Ret = true;//����true
	} while (0);
	return Ret;

}

void TowerStar::Attack(float Delta) {
	if (!Target || Target->getIsDead()) //���Ŀ��Ϊ�ջ��Ѿ���������ʲôҲ����ֱ�ӷ���
		return;
	auto AttackActionCF = CallFunc::create([=]() //����һ���ص������������Ϊһ��Lambdas���ʽ
		{ AttackMove(); });//�ñ��ʽ�е���ִ�й��������ĺ���

	auto CreateBulletCF = CallFunc::create([=]() {//�����ص�����
		if (!Target) //�������Ŀ��Ϊ�գ���ֱ�ӷ���
			return;
		BulletStar* Bullet = BulletStar::create(getBulletId(),Target);//����һ�����������ӵ�
		Bullet->setPosition(this->getPosition());//�����ӵ���λ��������λ����ͬ
		Bullet->DoMove();//�����ӵ��ƶ��ĺ���
		});

	this->runAction(Sequence::create(AttackActionCF, DelayTime::create(0.35), CreateBulletCF, NULL));
	//ִ�ж������У��ȹ�����Ȼ�����һ�����ʱ��Ȼ�����ӵ�
}