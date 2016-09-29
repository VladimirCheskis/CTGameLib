#pragma once

#include "Common.h"

class GameSoundBuffer
{
public:
    GameSoundBuffer(const char* filePath);
    const sf::SoundBuffer& getSoundBuffer() const { return m_soundBuffer; }
private:
    sf::SoundBuffer m_soundBuffer;
};
DEFINE_STD(GameSoundBuffer);

class GameSoundBuffersStorage
{
public:
    GameSoundBuffersStorage() = default;

    GameSoundBufferPtr get(const string& filePath);
    GameSoundBufferPtr hold(const string& filePath);
private:
    using HoldedGameSoundBuffers = map<string, GameSoundBufferPtr> ;
    using StoredGameSoundBuffers = map<string, GameSoundBufferWeakPtr> ;

    HoldedGameSoundBuffers m_holdedSounds;
    StoredGameSoundBuffers m_storedSounds;
};

struct GameSound
{
    GameSoundBufferPtr sound;
    float volume = 100.f;
    GameSound(const string& filePath);
};


class SoundPlayer
{
public:
    SoundPlayer() = default;

    void play(const std::string& soundId, const GameSound& soundParams);
    void stop(const std::string& soundId);
    void stopAll();
    bool isEnded() const;
private:
    struct Sound
    {
        std::string soundId;
    	sf::Sound   sound;
    };
    using Sounds = std::vector<Sound>;
    Sounds m_sounds;
};

