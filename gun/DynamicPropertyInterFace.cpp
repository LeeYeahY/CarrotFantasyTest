#include "DynamicPropertyInterFace.h"

DynamicPropertyInterFace::~DynamicPropertyInterFace()
{
    CC_SAFE_RELEASE_NULL(pAnimation);
}

bool DynamicPropertyInterFace::Init(const int& Id, const std::string& SCsvFileName)
{
    bool Ret = false;
    do
    {
        auto CsvUtil = CsvUtil::GetInstance();//��ȡ CSV �ļ��е�����
        pAnimation = Animation::create();
        pAnimation->retain();//ȷ���ں���ʹ���в��ᱻ��ǰ�ͷ�
        myAtk = CsvUtil->GetInt(Id, en_Atk, SCsvFileName);//��ù�������
        mySpeed = CsvUtil->GetInt(Id, en_Speed,SCsvFileName);//����ٶ�
        Ret = true;
    } while (0);

    return Ret;
}

void DynamicPropertyInterFace::CreateDynamicEntityAnimation(const std::vector<std::string>& AnimationFiles)
{
    auto SpriteFrameCache = SpriteFrameCache::getInstance();//����ͻ��澫��֡
    for (auto& animationFile : AnimationFiles)//���� AnimationFiles �е�ÿһ�������ļ���
        pAnimation->addSpriteFrame(SpriteFrameCache->getSpriteFrameByName(animationFile));//�ӻ����л�ȡָ���ļ����ľ���֡����������ӵ��������� pAnimation ��
    pAnimation->setLoops(-1); //����������Ϊ����ѭ������
}
