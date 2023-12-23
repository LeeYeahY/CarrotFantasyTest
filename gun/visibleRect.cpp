#include "visibleRect.h"

USING_NS_CC;

Rect VisibleRect::sVisibleRect;

void VisibleRect::init()
{
    sVisibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
}

Rect VisibleRect::getVisibleRect()
{
    init();
    return sVisibleRect;
}

Vec2 VisibleRect::left()
{
    init();
    return Vec2(sVisibleRect.origin.x, sVisibleRect.origin.y + sVisibleRect.size.height / 2);
}

Vec2 VisibleRect::right()
{
    init();
    return Vec2(sVisibleRect.origin.x + sVisibleRect.size.width, sVisibleRect.origin.y + sVisibleRect.size.height / 2);
}

Vec2 VisibleRect::top()
{
    init();
    return Vec2(sVisibleRect.origin.x + sVisibleRect.size.width / 2, sVisibleRect.origin.y + sVisibleRect.size.height);
}

Vec2 VisibleRect::bottom()
{
    init();
    return Vec2(sVisibleRect.origin.x + sVisibleRect.size.width / 2, sVisibleRect.origin.y);
}

Vec2 VisibleRect::center()
{
    init();
    return Vec2(sVisibleRect.origin.x + sVisibleRect.size.width / 2, sVisibleRect.origin.y + sVisibleRect.size.height / 2);
}

Vec2 VisibleRect::leftTop()
{
    init();
    return Vec2(sVisibleRect.origin.x, sVisibleRect.origin.y + sVisibleRect.size.height);
}

Vec2 VisibleRect::rightTop()
{
    init();
    return Vec2(sVisibleRect.origin.x + sVisibleRect.size.width, sVisibleRect.origin.y + sVisibleRect.size.height);
}

Vec2 VisibleRect::leftBottom()
{
    init();
    return  sVisibleRect.origin;
}

Vec2 VisibleRect::rightBottom()
{
    init();
    return Vec2(sVisibleRect.origin.x + sVisibleRect.size.width, sVisibleRect.origin.y);
}