#include"NumSprite.h"
#include<string>

Node* NumSprite::CreateNum(const std::string& Num, const std::string& Image)
{
    auto Size = Sprite::create(Image)->getContentSize();//获取图片的精灵尺寸
    auto NumSize = Num.size();//获取字符串大小

    auto NumNode = Node::create();//创建容纳数字精灵的结点
    NumNode->retain();//对该结点进行引用计数

    for (int i = 0; i < NumSize; ++i)//遍历字符串的每一位
    {
        auto IntNum = atoi(StringUtils::format("%c", Num.at(i)).c_str());//将字符串转换为整数
        auto PtrNum = Sprite::create(Image, Rect(Size.width / 12 * (IntNum + 2), 0, Size.width / 12, Size.height));//用该整数取用图片中的一部分并创建精灵
        auto Pos = Vec2(PtrNum->getContentSize().width * i, 0);//设置精灵的位置
        PtrNum->setPosition(Pos);
        NumNode->addChild(PtrNum);//添加数字精灵到数字结点中
    }
    return NumNode;//返回创建的数字结点
}
