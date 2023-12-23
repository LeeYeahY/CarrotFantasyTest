#ifndef _scoreAndControlLayer_
#define _scoreAndControlLayer_

#include "publicDefine.h"
//�ò�����չʾ��Ǯ������ֹͣ��Ϸ�Լ���������ѡ��ؿ�
class ScoreAndControllerLayer : public Layer
{
public:

    CREATE_FUNC(ScoreAndControllerLayer);

    virtual void setPauseFlagIsClose();

    virtual void clickChooseItem();

protected:

    virtual bool init();

    virtual void createTopPanel();

    virtual void loadBg();

    CC_SYNTHESIZE(int, iMoney, CurMoney);

    virtual void registerNotifyEvent();

    virtual void unRegisterNotifyEvent();

    virtual void moneyChange(Ref* pData);

    virtual void monsterBatchChange(Ref* pData);

    virtual void setMonsterBatchCount(const int& rIMonsterBatchIndex);

    virtual void setMoneyNum(const int& rIMoneyNum);

    virtual void onExit()override;

private:

    Node* pMonsterBatchIndex = nullptr;

    Node* pMoneyLabel = nullptr;

    bool bIsOpenChooceMenu = false;

    bool bIsOpenSpeedUp = false;

    bool bIsPause = false;

    MenuItemSprite* pChooseItem = nullptr;

};

#endif /
