#ifndef _helpScene_
#define _helpScene_

#include "publicDefine.h"

class HelpScene : public Scene
{
public:

    CREATE_FUNC(HelpScene);

    virtual ~HelpScene();

protected:

    virtual bool init()override;

    virtual void onEnter()override;

private:

    Layer* pMenuPanelLayer = nullptr;

};

#endif
