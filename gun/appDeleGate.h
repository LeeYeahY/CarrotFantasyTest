#ifndef  _appDeleGate_
#define  _appDeleGate_

#include "cocos2d.h"

//����˽�м̳е�ԭ����Ҫ����һЩ��Director���õĽӿ�
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    //ʵ��Director��Scene�ĳ�ʼ��
    virtual bool applicationDidFinishLaunching();

    virtual void applicationDidEnterBackground();

    virtual void applicationWillEnterForeground();

protected:

    virtual void preLoadSource();

    virtual void unLoadSource();

};

#endif

