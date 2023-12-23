#include"TowerFactory.h"
#include"TowerStar.h"
#include"TowerPin.h"
#include"TowerRocket.h"
Tower* TowerFactory::CreateTower(const TowerType& MyTowerType, Vec2 Position)
{
	Tower* MyTower = nullptr;
	int TowerId = 0;
	switch (MyTowerType)//根据传入的参数确定塔的类型
	{
		//初始化TowerId并创建塔
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
	//放置在对应的位置
	MyTower->setPosition(Position);
	return MyTower;//返回指向该防御塔的指针
}