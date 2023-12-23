#ifndef newCardDefence_publicDefine_h
#define newCardDefence_publicDefine_h

#include "cocos2d.h"
#include "VisibleRect.h"
#include "PublicSourceDefine.h"
#include "CsvUtil.h"

using namespace cocos2d;

class VictimEntityBase;
class MonsterBase;
class BarrierBase;
class BulletBase;
class Tower;

using MonsterVec = Vector<MonsterBase*>;
using BarrierVec = Vector<BarrierBase*>;
using BulletVec = Vector<BulletBase*>;
using TowerVec = Vector<Tower*>;

#define CREATE_INSTANCE_FUNC(__CLASS__) \
private:\
    static __CLASS__ *gInstance;\
public:\
static __CLASS__* getInstance()\
{\
    if(!gInstance)\
    {\
        gInstance = new __CLASS__();\
        if(gInstance && gInstance->Init())\
        {\
            gInstance->autorelease();\
            gInstance->retain();\
        }\
        else\
        {\
            CC_SAFE_DELETE(gInstance);\
        }\
    }\
    return gInstance;\
}

#define DESTROY_INSTANCE_FUNC()\
static void destroyInstance()\
{\
    CC_SAFE_RELEASE_NULL(gInstance);\
}

#define NOTIFY cocos2d::NotificationCenter::getInstance()

enum CsvPublicProperty
{
    NAME = 1,
    MODELNAME,
    VALUE,
    ANIMATION_COUNT,
    GRADE
};

enum CsvTowerProperty
{
    RANGE = 6,
    SPACE,
    BULLET_ID,
    UP_COST,
    TOWER_BASE,
    IS_ROTATE,
    CREATE_COST
};

enum CsvVictimProperty
{
    en_Hp = 6,
    en_Speed,
    en_Atk,
};

enum CsvBulletProperty
{
    en_AtkState = 6,
    en_Duration = 9,
    en_BulletType,
    en_DeadActCount
};

/**
 Atk State
 */
enum AtkState
{
    en_Normal = 1,
    en_Slow = en_Normal << 1,
    en_Stop = en_Normal << 2,
    en_Poison = en_Normal << 3,
};

class AtkProperty
{
public:
    int _enAtkState = 0;
    int Duration = 0;
    int Atk = 0;
    int ButtltType = 0;
};

//SceneType
enum SceneType
{
    en_WelcomeScene,
    en_GameSettingScene,
    en_GameHelpScene,
    en_PageSelectScene,
    en_LevelSelectScene,
    en_GameScene

};

//TowerType
enum TowerType
{
    STAR_TOWER,
    PIN_TOWER,
    ROCKET_TOWER
};
enum BarrierType
{
    BALLON,
    CLOUD,
    STONE,
    TREE
};

//MonsterType
enum MonsterType
{
    en_Land_Pink = 1,
    en_Land_Star,
    en_Land_Nima,
    en_Fly_Yellow,
    en_Fly_Blue,
    en_Fat_Green,
    en_Land_Boss_Pink,
    en_Land_Boss_Star,
    en_Land_Boss_Nima,
    en_Fly_Boss_Yellow,
    en_Fly_Boss_Blue,
    en_Fat_Boss_Green,
    en_Big_Oldboss,
    en_Fat_Oldboss,
    en_Fly_Oldboss,
    en_Land_Oldboss,
    en_Boss_Big,
};

//BulletType
enum BulletType
{
    en_NormalBullet = 1,
    en_NoDisspper,
    en_GunBullet,
    en_StarBullet
};

enum GameEndType
{
    en_GameWin,
    en_GameLose
};



#endif

