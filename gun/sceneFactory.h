#ifndef _sceneFactory_
#define _sceneFactory_

#include "publicDefine.h"

class SceneFactory
{
public:

    static Scene* createScene(const SceneType& rEnSceneType);
};

#endif