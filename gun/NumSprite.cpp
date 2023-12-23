#include"NumSprite.h"
#include<string>

Node* NumSprite::CreateNum(const std::string& Num, const std::string& Image)
{
    auto Size = Sprite::create(Image)->getContentSize();//��ȡͼƬ�ľ���ߴ�
    auto NumSize = Num.size();//��ȡ�ַ�����С

    auto NumNode = Node::create();//�����������־���Ľ��
    NumNode->retain();//�Ըý��������ü���

    for (int i = 0; i < NumSize; ++i)//�����ַ�����ÿһλ
    {
        auto IntNum = atoi(StringUtils::format("%c", Num.at(i)).c_str());//���ַ���ת��Ϊ����
        auto PtrNum = Sprite::create(Image, Rect(Size.width / 12 * (IntNum + 2), 0, Size.width / 12, Size.height));//�ø�����ȡ��ͼƬ�е�һ���ֲ���������
        auto Pos = Vec2(PtrNum->getContentSize().width * i, 0);//���þ����λ��
        PtrNum->setPosition(Pos);
        NumNode->addChild(PtrNum);//������־��鵽���ֽ����
    }
    return NumNode;//���ش��������ֽ��
}
