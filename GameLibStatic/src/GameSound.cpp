#include "GameSound.h"

GameSoundBuffer::GameSoundBuffer(const char* filePath)
{
    m_soundBuffer.loadFromFile(filePath);
}


GameSoundBufferPtr GameSoundBuffersStorage::get(const string& filePath)
{
    auto it = m_storedSounds.find(filePath);
    if (it != m_storedSounds.end())
    {
        auto sound = it->second.lock();
        if (sound)
            return sound;
    }
    auto sound = std::make_shared<GameSoundBuffer>(filePath.c_str());
    m_storedSounds[filePath] = sound;
    return sound;
}

GameSoundBufferPtr GameSoundBuffersStorage::hold(const string& filePath)
{
    auto it = m_holdedSounds.find(filePath);
    if (it != m_holdedSounds.end())
        return it->second;

    auto it1 = m_storedSounds.find(filePath);
    if (it1 != m_storedSounds.end())
    {
        auto sound = it1->second.lock();
        if (sound)
        {
            m_holdedSounds[filePath] = sound;
            return sound;
        }
    }
    auto sound = std::make_shared<GameSoundBuffer>(filePath.c_str());
    m_storedSounds[filePath] = sound;
    m_holdedSounds[filePath] = sound;
    return sound;
}

GameSoundBufferPtr getSoundBuffer(const string& filePath)
{
    static GameSoundBuffersStorage storage;
    return storage.get(filePath);
}

GameSound::GameSound(const string& filePath)
{
    sound = getSoundBuffer(filePath);
}


/////////////////////////////////////////////////////////////////////////////
void SoundPlayer::play(const std::string& soundId, const GameSound& soundParams)
{
    if (soundParams.sound == nullptr)
        return;
    Sound sound;
    sound.soundId = soundId;
    sound.sound = sf::Sound(soundParams.sound->getSoundBuffer());
    sound.sound.setVolume(soundParams.volume);
    m_sounds.push_back(sound);
    m_sounds.back().sound.play();
}

void SoundPlayer::stop(const std::string& soundId)
{
    for (auto& sound : m_sounds)
    {
        if (sound.soundId == soundId)
        {
            sound.sound.stop();
        }
    }
}

void SoundPlayer::stopAll()
{
    for (auto& sound : m_sounds)
    {
        sound.sound.stop();
    }
}

bool SoundPlayer::isEnded() const
{
    for (const auto& sound : m_sounds)
    {
        if (sound.sound.getStatus() != sf::SoundSource::Stopped)
            return false;
    }
    return true;
}
