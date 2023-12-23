
#include"TowerManager.h"
#include"Tower.h"

TowerManager::~TowerManager()
{
    CC_SAFE_DELETE(Towers);//释放指向存储塔的vector的指针
}
bool TowerManager::Initiate()
{
    Towers = new TowerVec;//创建存储塔的vector
    RecordTowerDead();//调用记录塔的死亡的函数，即添加观察者
    return true;
}
TowerVec& TowerManager::GetTowerVec()
{
    return *Towers;//返回指向存储Tower的vector的指针
}
void TowerManager::AddNewTower(Tower* NewTower)
{
    if (Towers)//如果指向vector的指针不为空
        Towers->pushBack(NewTower);//则将新的防御塔添加到vector中
    AddTower(NewTower);//并调用添加塔层的函数对该塔进行添加
}
void TowerManager::SetFuncAddTowerLayer(const std::function<void(Entity*)>& MyAddTower)
{
    AddTower = MyAddTower;//根据传入的参数初始化添加塔层的函数指针
}
void TowerManager::RecordTowerDead()
{
    //添加观察者，观察者为当前对象，当接收到TowerDead的信息时，RemoveTower函数会被调用
    NOTIFY->addObserver(this, callfuncO_selector(TowerManager::RemoveTower), "TowerDead", nullptr);
}
void TowerManager::RemoveTower(Ref* Tower)
{
    if (!(Towers && Towers->size())) //如果Towers指向空或不指向空但没有元素
        return;//则直接返回
    Towers->eraseObject(static_cast<Tower*>(Tower));//否则在Towers中找到Tower并移除
}
void TowerManager::ClearManager()
{
    Towers->clear();//清空所有元素
}
int TowerManager::GetMoney() {
    return CheckMoney();//返回当前金币数
}
void TowerManager::SetFuncCheckMoney(const std::function<int()>& MyCheckMoney) {
    CheckMoney = MyCheckMoney;//根据传入的参数初始化检查金币的函数
}