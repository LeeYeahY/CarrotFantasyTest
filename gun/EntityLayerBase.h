#pragma once
#include"cocos2d.h"
#ifndef _ENTITY_LAYER_BASE_
#define _ENTITY_LAYER_BASE_
class Entity;
class EntityLayerBase :public Layer
{
public:
    virtual void AddEntity(Entity* NewEntity);
};
#endif _ENTITY_LAYER_BASE_
