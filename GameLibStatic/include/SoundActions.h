#pragma once

#include "GameSprite.h"

class BaseSoundAction : public SpriteInstantAction
{
public:
      BaseSoundAction (const GameSpritePtr& sprite,
                      const string& soundId);
protected:
    string    m_soundId;
};

class PlaySoundAction : public BaseSoundAction
{
public:
      PlaySoundAction(const GameSpritePtr& sprite,
                      const string& soundId, const GameSound& sound);
      PlaySoundAction(const GameSpritePtr& sprite,
                      const string& soundId, const string& soundFile, float volume = 100);
      GameActionPtr createCopy() const override;
protected:
    virtual void tickImpl(GameScene& scene) override;
private:
    GameSound m_sound;
};
DEFINE_STD(PlaySoundAction);

class StopSoundsByIdAction : public BaseSoundAction
{
public:
      StopSoundsByIdAction(const GameSpritePtr& sprite, const string& soundId);
      GameActionPtr createCopy() const override;
protected:
    virtual void tickImpl(GameScene& scene) override;
};
DEFINE_STD(StopSoundsByIdAction);

class StopAllSoundsAction : public SpriteInstantAction
{
public:
      StopAllSoundsAction(const GameSpritePtr& sprite);
      GameActionPtr createCopy() const override;
protected:
    virtual void tickImpl(GameScene& scene) override;
};
DEFINE_STD(StopAllSoundsAction);
