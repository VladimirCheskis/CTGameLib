#include "GameScene.h"
#include "MoveActions.h"


SpriteActionMove::SpriteActionMove(const GameSpritePtr& sprite, float x, float y, float time)
: m_endPosition(x, y), m_duration(time)
{
    setSprite(sprite);
}

void SpriteActionMove::start(GameScene& , float curTime)
{
    m_isStarted = true;
    if (auto sprite = m_sprite.lock())
    {
        sprite->getPlace(m_startPosition.x, m_startPosition.y);
    }
    m_startTime = curTime;
    m_endTime   = curTime + m_duration;
}

void interpolate(const Point& p0, const Point& p1, float c, Point& p)
{
    p.x = p0.x * (1.f-c) + p1.x * (c);
    p.y = p0.y * (1.f-c) + p1.y * (c);
}

void SpriteActionMove::step(float curTime)
{
    if (m_endTime <= curTime + 1E-6f)
    {
        moveSprite(m_endPosition);
        m_isEnded = true;
        return;
    }
    float c = (curTime - m_startTime) / m_duration;
    Point point;
    interpolate(m_startPosition, m_endPosition, c, point);
    moveSprite(point);
}

void SpriteActionMove::moveSprite(const Point& point)
{
    if (auto sprite = m_sprite.lock())
    {
        sprite->setPlace(point.x, point.y);
    }
}


void SpriteActionMove::tick(GameScene& scene)
{
    if (m_isEnded)
        return;
    float curTime = scene.time();
    if (m_duration < 1E-5f )
    {
        start(scene, curTime);
        moveSprite(m_endPosition);
        m_isEnded = true;
        return;
    }
    m_isStarted ? step(curTime) : start(scene, curTime);
}

GameActionPtr SpriteActionMove::createCopy() const
{
    SpriteActionMovePtr result = std::make_shared<SpriteActionMove>(m_sprite.lock(),
                                                                    m_endPosition.x, m_endPosition.y,
                                                                    m_duration);
    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////
SpriteActionMoveToMouse::SpriteActionMoveToMouse(const GameSpritePtr& sprite, float time)
  : SpriteActionMove(sprite, 0, 0, time)
{
}

GameActionPtr SpriteActionMoveToMouse::createCopy() const
{
    return make_shared<SpriteActionMoveToMouse>(m_sprite.lock(), getDuration());
}

void SpriteActionMoveToMouse::start(GameScene& scene, float curTime)
{
    setEndPosition(scene.getMousePosition());
    SpriteActionMove::start(scene, curTime);
}

SpriteActionMoveByVector::SpriteActionMoveByVector(const GameSpritePtr& sprite, float dx, float dy, float time)
  : SpriteActionMove(sprite, 0, 0, time), m_delta(dx, dy)
{

}

SpriteActionMoveByVector::SpriteActionMoveByVector(const GameSpritePtr& sprite, const Vector& delta, float time)
  : SpriteActionMove(sprite, 0, 0, time), m_delta(delta)
{

}

GameActionPtr SpriteActionMoveByVector::createCopy() const
{
    return make_shared<SpriteActionMoveByVector>(m_sprite.lock(), m_delta, getDuration());
}

void SpriteActionMoveByVector::start(GameScene& scene, float curTime)
{
    if (auto sprite = m_sprite.lock())
    {
        float x, y;
        sprite->getPlace(x, y);
        setEndPosition(Point(x,y) + m_delta);
    }
    SpriteActionMove::start(scene, curTime);
}

SpriteActionMoveToSprite::SpriteActionMoveToSprite(const GameSpritePtr& sprite, const GameSpritePtr& targetSprite, float time)
  : SpriteActionMove(sprite, 0, 0, time), m_targetSprite(targetSprite)
{
}

GameActionPtr SpriteActionMoveToSprite::createCopy() const
{
    return make_shared<SpriteActionMoveToSprite>(m_sprite.lock(), m_targetSprite.lock(), getDuration());
}

void SpriteActionMoveToSprite::start(GameScene& scene, float curTime)
{
    if (auto targetSprite = m_targetSprite.lock())
    {
        float x, y;
        targetSprite->getPlace(x, y);
        setEndPosition({x,y});
    }
    SpriteActionMove::start(scene, curTime);
}
