#ifndef _loadingSourceLayer_
#define _loadingSourceLayer_

#include "publicDefine.h"

class LoadingSourceLayer : public Layer
{
public:

    CREATE_FUNC(LoadingSourceLayer);

    virtual void setFuncShowMenuPanel(const std::function<void()>& rFuncShowMenuPanel);

protected:

    virtual void onEnter()override;

    virtual bool init();

    virtual void loadSource();

protected:

    std::function<void()> funShowMenuPanel;

    Label* pLoadingTitle = nullptr;
};

#endif 

