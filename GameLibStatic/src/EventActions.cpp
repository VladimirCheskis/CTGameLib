#include "EventActions.h"
#include "GameScene.h"

void IOnEventAction::addAction(const GameActionPtr& action)
{
    m_patterns.addAction(action);
}

bool IOnEventAction::isEnded() const
{
    if (m_actions.empty() && m_patterns.empty())
        return true;
    if (m_wereActionsStarted && !m_isRepeatable)
        return m_actions.isEnded();
    return !m_isRepeatable;
}

bool IOnEventAction::isBackground() const
{
    return false;
}

void IOnEventAction::tick(GameScene& scene)
{
    if (m_wereActionsStarted && !m_isRepeatable)
    {
        m_actions.tick(scene);
        return;
    }

    if (isTrigger(scene))
    {
        ++m_runCount;
        //std::cout << "IOnEventAction " << m_runCount << " \n";
        m_wereActionsStarted = true;
        m_patterns.addCopiesTo(m_actions);
    }
    m_actions.tick(scene);
}

void IOnEventAction::copyTo(IOnEventAction* dst) const
{
    dst->m_isRepeatable = m_isRepeatable;
    m_patterns.addCopiesTo(dst->m_patterns);
}

///////////////////////////////////////////////////////////////////////////////
WaitAction::WaitAction(float waitTime)
  : m_waitTime(waitTime)
{

}

bool WaitAction::isTrigger(GameScene& scene)
{
    if (!m_wasWaitingStarted)
    {
        m_waitingEndTime = scene.time() + m_waitTime;
        m_wasWaitingStarted = true;
        return false;
    }
    return scene.time() >= m_waitingEndTime;
}

GameActionPtr WaitAction::createCopy() const
{
    WaitActionPtr result = std::make_shared<WaitAction>(m_waitTime);
    copyTo(result.get());
    return result;
}

///////////////////////////////////////////////////////////////////////////////
OnSpriteMouseClickAction::OnSpriteMouseClickAction(const GameSpritePtr& sprite)
  : m_sprite(sprite)
{

}

void OnSpriteMouseClickAction::tick(GameScene& scene)
{
    IOnEventAction::tick(scene);
    m_mouseCliked = false;
}

bool OnSpriteMouseClickAction::isTrigger(GameScene& scene)
{
    return m_mouseCliked;
}

bool OnSpriteMouseClickAction::needLeftButtonDown() const
{
     return !m_mouseCliked;
}

void OnSpriteMouseClickAction::onLeftButtonDown(const sf::Color&)
{
    m_mouseCliked = true;
}

GameActionPtr OnSpriteMouseClickAction::createCopy() const
{
    OnSpriteMouseClickActionPtr result = std::make_shared<OnSpriteMouseClickAction>(m_sprite.lock());
    copyTo(result.get());
    return result;
}

OnSpriteCollsionAction::OnSpriteCollsionAction(const GameSpritePtr& sprite, const GameSpritePtr& other)
  : m_sprite(sprite), m_other(other)
{

}

bool OnSpriteCollsionAction::isTrigger(GameScene& scene)
{
    if (!m_collision)
    {
        m_collision = scene.collision(m_sprite.lock(), m_other.lock());
    }
    return m_collision->collisionDetected;
}

GameActionPtr OnSpriteCollsionAction::createCopy() const
{
    OnSpriteCollsionActionPtr result = std::make_shared<OnSpriteCollsionAction>(m_sprite.lock(), m_other.lock());
    copyTo(result.get());
    return result;
}

OnKeyPressedAction::OnKeyPressedAction(Key key)
  : m_key(key)
{

}

bool OnKeyPressedAction::isTrigger(GameScene& scene)
{
    bool isPressed = sf::Keyboard::isKeyPressed(m_key);
    bool result = isPressed && !m_wasPressedOnPrevTick;
    m_wasPressedOnPrevTick = isPressed;
/*
    if (result )//|| m_wasPressedOnPrevTick)
    {
        std::cout << "OnKeyPressedAction " << m_wasPressedOnPrevTick << " " << isPressed << " " << result << " \n";
    }
*/
    return result;
}

GameActionPtr OnKeyPressedAction::createCopy() const
{
    OnKeyPressedActionPtr result = make_shared<OnKeyPressedAction>(m_key);
    copyTo(result.get());
    return result;
}

