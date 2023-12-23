#ifndef  _appDeleGate_
#define  _appDeleGate_

#include "cocos2d.h"

//采用私有继承的原因是要隐藏一些被Director调用的接口
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    //实现Director和Scene的初始化
    virtual bool applicationDidFinishLaunching();

    virtual void applicationDidEnterBackground();

    virtual void applicationWillEnterForeground();

protected:

    virtual void preLoadSource();

    virtual void unLoadSource();

};

#endif

