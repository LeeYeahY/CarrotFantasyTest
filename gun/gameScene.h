#ifndef _gameScene_
#define _gameScene_

#include "sceneBase.h"

class EntityLayerBase;
class Carrot;

class GameScene :public SceneBase
{
public:

	CREATE_FUNC(GameScene);

	virtual ~GameScene();

	virtual Carrot* getCarrot();

	virtual void clickChooseItem();
protected:

	virtual bool init();

	virtual void createLayers();

	virtual void addLayers();

	virtual void onEnter()override;

	virtual void onExit()override;

	virtual void preLoadSource();

	virtual void unLoadSource();

	virtual void collisionUpDate(float dt);

	virtual void createBarriers();

	virtual void clearAllManager();

	virtual void registerGameEvent();

	virtual void showGameEndLayer(Ref* pData);

	virtual void startBuildMonster(Ref* pData);

private:

	std::vector<std::string>* _pSourceVec = nullptr;

	Layer* pTiledMapLayer = nullptr;

	EntityLayerBase* pBarriersLayerR = nullptr;

	EntityLayerBase* pBulletsLayer = nullptr;

	EntityLayerBase* pMonsterLayer = nullptr;

	EntityLayerBase* pTowersLayer = nullptr;

	Layer* pScoreAndControllerLayer = nullptr;

	Layer* pOptLayer = nullptr;

	Carrot* pCarrot = nullptr;

	int iSourceCount = 0;
};

#endif
