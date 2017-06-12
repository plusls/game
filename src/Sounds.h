//
// Created by plusl on 2017/6/13.
//

#ifndef GAME_SOUNDS_H
#define GAME_SOUNDS_H

#include <SFML/Audio.hpp>
#include <list>


class Sound : public sf::Sound
{
public:
    static bool isRemoveSound(Sound* sound);

};

class MosterDeathSound : public Sound
{
public:
    MosterDeathSound();

};

class MosterDeathSoundBuffer : public sf::SoundBuffer
{
public:
    MosterDeathSoundBuffer();
};

extern std::list<Sound*> soundList;


//sound.setBuffer();
//sf::SoundBuffer buffer;
//buffer.loadFromFile()
#endif //GAME_SOUNDS_H
