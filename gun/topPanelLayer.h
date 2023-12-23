#ifndef _topPanelLayer_
#define _topPanelLayer_

#include "publicDefine.h"


class TopPanelLayer :public Layer
{
public:

    CREATE_FUNC(TopPanelLayer);

    virtual ~TopPanelLayer();

protected:

    virtual bool init();

    virtual void createMenuPanel();

    virtual void createMultiplexLayer();

private:

    LayerMultiplex* pLayerMultiplex = nullptr;
};

#endif
