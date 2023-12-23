#include"SoundUtil.h"
#include "SimpleAudioEngine.h"//cocos中管理音频的库

SoundUtil* SoundUtil::Instance;
void SoundUtil::PlayBackgroundSound(const std::string& BgSound)
{
    if (!IsBackgroundSound)//如果该音乐不是背景音乐则不用播放
        return;

    if (BgSound == BACKGROUNDSOUND && IsSoundMainBackgroundMusic) 
        return;
    else
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BgSound.c_str(), true);//调用引擎播放背景音乐
        if (BgSound == BACKGROUNDSOUND) //如果该音乐是背景音乐
            IsSoundMainBackgroundMusic = true;//将该变量置为true
        else 
            IsSoundMainBackgroundMusic = false;//否则置为false
    }

}

void SoundUtil::PlayEffect(const std::string& EffectSound)
{
    if (!IsEffectSound) 
        return;//如果这个音乐不是音效则不播放，直接返回

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(EffectSound.c_str());
    //否则调用引擎播放背景音乐
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

