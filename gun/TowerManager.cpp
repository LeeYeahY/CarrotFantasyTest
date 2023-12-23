
#include"TowerManager.h"
#include"Tower.h"

TowerManager::~TowerManager()
{
    CC_SAFE_DELETE(Towers);//�ͷ�ָ��洢����vector��ָ��
}
bool TowerManager::Initiate()
{
    Towers = new TowerVec;//�����洢����vector
    RecordTowerDead();//���ü�¼���������ĺ���������ӹ۲���
    return true;
}
TowerVec& TowerManager::GetTowerVec()
{
    return *Towers;//����ָ��洢Tower��vector��ָ��
}
void TowerManager::AddNewTower(Tower* NewTower)
{
    if (Towers)//���ָ��vector��ָ�벻Ϊ��
        Towers->pushBack(NewTower);//���µķ�������ӵ�vector��
    AddTower(NewTower);//�������������ĺ����Ը����������
}
void TowerManager::SetFuncAddTowerLayer(const std::function<void(Entity*)>& MyAddTower)
{
    AddTower = MyAddTower;//���ݴ���Ĳ�����ʼ���������ĺ���ָ��
}
void TowerManager::RecordTowerDead()
{
    //��ӹ۲��ߣ��۲���Ϊ��ǰ���󣬵����յ�TowerDead����Ϣʱ��RemoveTower�����ᱻ����
    NOTIFY->addObserver(this, callfuncO_selector(TowerManager::RemoveTower), "TowerDead", nullptr);
}
void TowerManager::RemoveTower(Ref* Tower)
{
    if (!(Towers && Towers->size())) //���Towersָ��ջ�ָ��յ�û��Ԫ��
        return;//��ֱ�ӷ���
    Towers->eraseObject(static_cast<Tower*>(Tower));//������Towers���ҵ�Tower���Ƴ�
}
void TowerManager::ClearManager()
{
    Towers->clear();//�������Ԫ��
}
int TowerManager::GetMoney() {
    return CheckMoney();//���ص�ǰ�����
}
void TowerManager::SetFuncCheckMoney(const std::function<int()>& MyCheckMoney) {
    CheckMoney = MyCheckMoney;//���ݴ���Ĳ�����ʼ������ҵĺ���
}