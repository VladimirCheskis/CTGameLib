#include "MessageActions.h"
#include "GameScene.h"

SentMessageAction::SentMessageAction(const GameMessage& msg)
  : m_msg(msg)
{
}

SentMessageAction::SentMessageAction(const GameSpritePtr& from, const GameSpritePtr& to, const string& message)
{
    m_msg.from = from;
    m_msg.to = to;
    m_msg.message = message;
    m_msg.toAllSprites = false;
}

SentMessageAction::SentMessageAction(const GameSpritePtr& from, const string& message)
{
    m_msg.from = from;
    m_msg.message = message;
    m_msg.toAllSprites = true;
}

void SentMessageAction::tickImpl(GameScene& scene)
{
    scene.getGameMessageStorage().addMessage(m_msg);
}

GameActionPtr SentMessageAction::createCopy() const
{
    return make_shared<SentMessageAction>(m_msg);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

OnMessageAction::OnMessageAction(const GameSpritePtr& sprite, const string& message)
  : m_sprite(sprite), m_message(message)
{
}

bool OnMessageAction::isTrigger(GameScene& scene)
{
    return scene.getGameMessageStorage().hasMessages(m_sprite.lock(), m_message);
}

GameActionPtr OnMessageAction::createCopy() const
{
    return make_shared<OnMessageAction>(m_sprite.lock(), m_message);
}
