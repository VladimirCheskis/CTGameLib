#include "SoundActions.h"

BaseSoundAction::BaseSoundAction(const GameSpritePtr& sprite,
                                 const string& soundId)
 : m_soundId(soundId)
{
    setSprite(sprite);
}


PlaySoundAction::PlaySoundAction(const GameSpritePtr& sprite,
                                 const string& soundId,
                                 const GameSound& sound)
  : BaseSoundAction(sprite, soundId), m_sound(sound)
{
}

PlaySoundAction::PlaySoundAction(const GameSpritePtr& sprite,
                                 const string& soundId,
                                 const string& soundFile, float volume)
  : BaseSoundAction(sprite, soundId), m_sound(soundFile)
{
    m_sound.volume = volume;
}

GameActionPtr PlaySoundAction::createCopy() const
{
    PlaySoundActionPtr result = make_shared<PlaySoundAction>(m_sprite.lock(), m_soundId, m_sound);
    return result;
}

void PlaySoundAction::tickImpl(GameScene& )
{
    if (auto sprite = m_sprite.lock())
        sprite->getSoundPlayer().play(m_soundId, m_sound);
}

///------------------------------------------------------------------------------
StopSoundsByIdAction::StopSoundsByIdAction(const GameSpritePtr& sprite, const string& soundId)
  :  BaseSoundAction(sprite, soundId)
{
}

GameActionPtr StopSoundsByIdAction::createCopy() const
{
    StopSoundsByIdActionPtr result = make_shared<StopSoundsByIdAction>(m_sprite.lock(), m_soundId);
    return result;
}

void StopSoundsByIdAction::tickImpl(GameScene& )
{
    if (auto sprite = m_sprite.lock())
        sprite->getSoundPlayer().stop(m_soundId);
}

///------------------------------------------------------------------------------
StopAllSoundsAction::StopAllSoundsAction(const GameSpritePtr& sprite)
{
    setSprite(sprite);
}

GameActionPtr StopAllSoundsAction::createCopy() const
{
    StopAllSoundsActionPtr result = make_shared<StopAllSoundsAction>(m_sprite.lock());
    return result;
}

void StopAllSoundsAction::tickImpl(GameScene& )
{
    if (auto sprite = m_sprite.lock())
        sprite->getSoundPlayer().stopAll();
}
