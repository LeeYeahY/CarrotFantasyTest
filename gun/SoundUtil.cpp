#include"SoundUtil.h"
#include "SimpleAudioEngine.h"//cocos�й�����Ƶ�Ŀ�

SoundUtil* SoundUtil::Instance;
void SoundUtil::PlayBackgroundSound(const std::string& BgSound)
{
    if (!IsBackgroundSound)//��������ֲ��Ǳ����������ò���
        return;

    if (BgSound == BACKGROUNDSOUND && IsSoundMainBackgroundMusic) 
        return;
    else
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BgSound.c_str(), true);//�������沥�ű�������
        if (BgSound == BACKGROUNDSOUND) //����������Ǳ�������
            IsSoundMainBackgroundMusic = true;//���ñ�����Ϊtrue
        else 
            IsSoundMainBackgroundMusic = false;//������Ϊfalse
    }

}

void SoundUtil::PlayEffect(const std::string& EffectSound)
{
    if (!IsEffectSound) 
        return;//���������ֲ�����Ч�򲻲��ţ�ֱ�ӷ���

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(EffectSound.c_str());
    //����������沥�ű�������
}

void SoundUtil::SetIsBackgroundSound(const bool& IsSound)
{
    IsBackgroundSound = IsSound;
    IsSoundMainBackgroundMusic = !IsSound;
    IsBackgroundSound ? PlayBackgroundSound(BACKGROUNDSOUND) : StopBackgroundSound();
}

void SoundUtil::StopBackgroundSound()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

SoundUtil::SoundUtil()
{
    setIsEffectSound(true);
}

SoundUtil::~SoundUtil()
{
    ;
}

