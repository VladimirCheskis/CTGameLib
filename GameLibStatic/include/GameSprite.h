#ifndef GAMESPRITE_H
#define GAMESPRITE_H

#include "GameObject.h"
#include "GameAction.h"
#include "GameAnimators.h"
#include "GameImage.h"
#include "GameSound.h"
#include "GameMessages.h"

class GameSprite : public GameObject
{
    public:
        GameSprite() = default;
        GameSprite(const string& imageFileName, int x, int y);

        virtual void tick(GameScene&) override;
        virtual void draw(GameScene& scene) override;
        virtual bool needLeftButtonDown() const;
        virtual bool onLeftButtonDown(int x, int y, GameScene& scene) override;

        void setImage(const GameImage& image);
        void setPlace(int x, int y);
        void setOrigin(int x, int y);
        void getPlace(float &x, float &y);

        void rotate(float degrees);
        void turnBack();
        void scale(float scaleCoeff);
        void setScale(float newScale);

        bool checkPoint(float x, float y) const;
        bool hasCollision(const GameSprite& sprite) const;

        void addAction(const GameActionPtr& action);

        sf::FloatRect getGlobalBounds() const
            { return m_sprite.getGlobalBounds();}

        SoundPlayer& getSoundPlayer()
            { return m_soundPlayer;}

        GameAnimationsSet& animationsSet()
            { return m_animationsSet;}
    protected:

    private:
        sf::Sprite m_sprite;
        GameImage  m_image;
        sf::Texture m_texture;
        SoundPlayer m_soundPlayer;
        GameAnimationsSet m_animationsSet;
        GameActionList m_actions;
};

class SpriteAction : public GameAction
{
public:
    void setSprite(const GameSpritePtr& sprite) {m_sprite = sprite;}

protected:
    GameSpriteWeakPtr m_sprite;
};
DEFINE_STD(SpriteAction);

class SpriteInstantAction : public SpriteAction
{
public:
      bool isEnded() const override { return m_wasTick;}
      bool isBackground() const override { return m_wasTick;}
      void tick(GameScene& scene) override
      {
          if (!m_wasTick)
            tickImpl(scene);
          m_wasTick = true;
      }
protected:
    virtual void tickImpl(GameScene& scene) = 0;
private:
    bool m_wasTick = false;
};
DEFINE_STD(SpriteInstantAction);

#endif // GAMESPRITE_H
