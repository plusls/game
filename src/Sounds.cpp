//
// Created by plusl on 2017/6/13.
//

#include "Sounds.h"

//声音列表 用于回收内存
std::list<Sound*> soundList;

MosterDeathSoundBuffer mosterDeathSoundBuffer;

bool Sound::isRemoveSound(Sound* sound)
{
    Status ret = sound->getStatus();
    if (ret == Status ::Stopped)
    {
        delete sound;
    }
    return ret == Status ::Stopped;
}

MosterDeathSound::MosterDeathSound()
{
    setBuffer(mosterDeathSoundBuffer);
}

MosterDeathSoundBuffer::MosterDeathSoundBuffer()
{
    loadFromFile("../resources/sound/se_msl2.wav");
};