#pragma once

#ifndef _sceneBase_
#define _sceneBase_

#include "publicDefine.h"

class SceneBase : public Scene
{

protected:

    virtual void sourceManager(const std::vector<std::string>& rSourceNameVec, const bool& rBLoad);

};

#endif 
