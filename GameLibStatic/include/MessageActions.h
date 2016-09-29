#pragma once

#include "GameSprite.h"
#include "EventActions.h"

class SentMessageAction : public SpriteInstantAction
{
public:
    SentMessageAction(const GameMessage& msg);
    /// сообщение одному спрайту to
    SentMessageAction(const GameSpritePtr& from, const GameSpritePtr& to, const string& message);
    /// сообщение всем спрайтам
    SentMessageAction(const GameSpritePtr& from, const string& message);

    virtual GameActionPtr createCopy() const override;
protected:
    virtual void tickImpl(GameScene& scene) override;
private:
    GameMessage m_msg;
};
DEFINE_STD(SentMessageAction);

class OnMessageAction : public IOnEventAction
{
public:

    OnMessageAction(const GameSpritePtr& sprite, const string& message);
    virtual bool isTrigger(GameScene& scene) override;
    virtual GameActionPtr createCopy() const override;
private:
    GameSpriteWeakPtr m_sprite;
    string m_message;
};
DEFINE_STD(OnKeyPressedAction);
