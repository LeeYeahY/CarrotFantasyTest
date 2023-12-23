#pragma once
#ifndef _OPT_LAYER_
#define _OPT_LAYER_
#include "cocos2d.h"

class TowerOpt;
using namespace cocos2d;

class OptLayer :public Layer
{
public:
	CREATE_FUNC(OptLayer);

protected:
	virtual bool Initiate();
	virtual void Listener();

protected:
	TowerOpt* TowerOptBtn;
	bool KeyOptBtn;
	Sprite* ForbiddenSp;

};

#endif _OPT_LAYER_
