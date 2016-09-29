#pragma once

#include "GameAnimators.h"
#include "GameSprite.h"

class SpriteActionAnimate : public SpriteAction
{
public:
      SpriteActionAnimate(const GameSpritePtr& sprite,
                          const std::string& animationName,
                          EAnimationType animationType = EAnimationType::Die);
      SpriteActionAnimate(const GameSpritePtr& sprite,
                          const IGameAnimatedImagePtr& images,
                          EAnimationType animationType = EAnimationType::Die);

      bool isEnded() const override;
      bool isBackground() const override;
      void tick(GameScene& scene) override;
      GameActionPtr createCopy() const override;
private:
    IGameAnimatedImagePtr m_images;
    GameNumberAnimator    m_frameNumberAnimator;
};
DEFINE_STD(SpriteActionAnimate);

class SpriteActionSetImage : public SpriteAction
{
public:
      SpriteActionSetImage(const GameSpritePtr& sprite,
                           const IGameAnimatedImagePtr& images,
                           size_t imageIndex = 0);
      SpriteActionSetImage(const GameSpritePtr& sprite,
                           const GameImage& image);

      bool isEnded() const override {return m_isSeted;}
      bool isBackground() const override  {return m_isSeted;}
      void tick(GameScene& scene) override;
      GameActionPtr createCopy() const override;
private:
    GameImage m_image;
    bool      m_isSeted = false;
};
DEFINE_STD(SpriteActionAnimate);
