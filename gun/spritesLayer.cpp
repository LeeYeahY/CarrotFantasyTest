#include "spritesLayer.h"

bool SpritesLayer::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF(!Layer::init());

        createStaticSprites();

        createDynamicSprites();

        createCarrot();

        bRet = true;
    } while (0);

    return bRet;
}

SpritesLayer::~SpritesLayer()
{
    CC_SAFE_RELEASE_NULL(pCarrotAll);
}

void SpritesLayer::createStaticSprites()
{
    auto pWelcomeBg = Sprite::createWithSpriteFrameName(WELCOMEBG);
    pWelcomeBg->setPosition(VisibleRect::center());
    addChild(pWelcomeBg);

    auto pMainBgCn = Sprite::createWithSpriteFrameName("mainbg_CN.png");
    pMainBgCn->setPosition(visibleSize.width / 2 - 20, visibleSize.height / 2);
    addChild(pMainBgCn, 6);

}

void SpritesLayer::createDynamicSprites()
{
    auto pCloud1 = Sprite::createWithSpriteFrameName("cloud1.png");
    pCloud1->setAnchorPoint(Vec2(0, 0.5f));
    pCloud1->setPosition(-pCloud1->getContentSize().width, 450);
    auto pCallBack1 = CallFunc::create([pCloud1]() {pCloud1->setPositionX(-pCloud1->getContentSize().width); });
    auto pMoveBy1 = MoveBy::create(20, Vec2(960 + pCloud1->getContentSize().width, 0));
    pCloud1->runAction(RepeatForever::create(Sequence::create(pCallBack1, pMoveBy1, NULL)));
    addChild(pCloud1);

    auto pCloud2 = Sprite::createWithSpriteFrameName("cloud2.png");
    pCloud2->setAnchorPoint(Vec2(0, 0.5f));
    pCloud2->setPosition(-pCloud2->getContentSize().width, 550);
    auto pCallBack2 = CallFunc::create([pCloud2]() {pCloud2->setPositionX(-pCloud2->getContentSize().width); });
    auto pMoveBy2 = MoveBy::create(35, Vec2(960 + pCloud2->getContentSize().width, 0));
    pCloud2->runAction(RepeatForever::create(Sequence::create(pCallBack2, pMoveBy2, NULL)));
    addChild(pCloud2);

    auto pBird = Sprite::createWithSpriteFrameName("bird.png");
    pBird->setPosition(Vec2(200, 460));
    auto pMoveBy = MoveBy::create(2, Vec2(0, 30));
    pBird->runAction(RepeatForever::create(Sequence::create(pMoveBy, pMoveBy->reverse(), NULL)));
    addChild(pBird);

}

void SpritesLayer::createCarrot()
{

    pCarrotAll = Node::create();
    pCarrotAll->retain();
    pCarrotAll->setName("carrot");
    auto pCarrot = Sprite::createWithSpriteFrameName("carrot.png");
    pCarrot->setAnchorPoint(Vec2(0.5, 0));
    pCarrotAll->addChild(pCarrot, 2);

    auto pLeaf1 = Sprite::createWithSpriteFrameName("leaf-1.png");
    pLeaf1->setPosition(Vec2(0, pCarrot->getContentSize().height));
    pLeaf1->setAnchorPoint(Vec2(1, 0.5));
    pCarrotAll->addChild(pLeaf1, 1);

    auto pLeaf3 = Sprite::createWithSpriteFrameName("leaf-3.png");
    pLeaf3->setAnchorPoint(Vec2(0.0f, 0.0f));
    pLeaf3->setPosition(Vec2(0, pCarrot->getContentSize().height - pLeaf3->getContentSize().height / 2));
    pLeaf3->setName("leaf3");
    pCarrotAll->addChild(pLeaf3, 1);

    auto pLeaf2 = Sprite::createWithSpriteFrameName("leaf-2.png");
    pLeaf2->setAnchorPoint(Vec2(0.5f, 0.0f));
    pLeaf2->setPosition(Vec2(0, pCarrot->getContentSize().height - pLeaf2->getContentSize().height / 3));
    pLeaf2->setName("leaf2");

    pCarrotAll->setContentSize(Size(pCarrot->getContentSize().width + 20, pCarrot->getContentSize().height + pLeaf2->getContentSize().height));
    pCarrotAll->addChild(pLeaf2, 1);
    pCarrotAll->setPosition(visibleSize.width / 2 - 20, visibleSize.height / 2 - 50);
    pCarrotAll->setScale(0);
    addChild(pCarrotAll);
    pCarrotAll->runAction(Sequence::create(ScaleTo::create(0.11, 1), NULL));

    schedule(schedule_selector(SpritesLayer::leafAction), 5);
}

void SpritesLayer::leafAction(float dt)
{
    auto pRotate = RotateBy::create(0.1f, 15);
    auto pDelay = DelayTime::create(2);
    pCarrotAll->getChildByName("leaf3")->runAction(Sequence::create(pDelay, pRotate, pRotate->reverse(), pRotate, pRotate->reverse(), pDelay, NULL));
    pCarrotAll->getChildByName("leaf2")->runAction(Sequence::create(pRotate, pRotate->reverse(), pRotate, pRotate->reverse(), pDelay, NULL));

}