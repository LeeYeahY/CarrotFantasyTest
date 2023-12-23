#include"TowerFactory.h"
#include"TowerStar.h"
#include"TowerPin.h"
#include"TowerRocket.h"
Tower* TowerFactory::CreateTower(const TowerType& MyTowerType, Vec2 Position)
{
	Tower* MyTower = nullptr;
	int TowerId = 0;
	switch (MyTowerType)//���ݴ���Ĳ���ȷ����������
	{
		//��ʼ��TowerId��������
	case STAR_TOWER: 
		TowerId = 13;
		MyTower = TowerStar::create(); 
		break;
	case PIN_TOWER: 
		TowerId = 28; 
		MyTower = TowerPin::create(); 
		break;
	case ROCKET_TOWER:
		TowerId = 25;
		MyTower = TowerRocket::create(); 
		break;
	default:
		break;
	}
	//�����ڶ�Ӧ��λ��
	MyTower->setPosition(Position);
	return MyTower;//����ָ��÷�������ָ��
}