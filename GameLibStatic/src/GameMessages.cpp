#include "GameSprite.h"

bool MessageCompare::operator()(const GameMessage& a, const GameMessage& b)
{
    if (a.message < b.message)
        return true;
    if (a.message > b.message)
        return true;

    if (!a.toAllSprites && b.toAllSprites)
        return true;
    if (a.toAllSprites  && !b.toAllSprites)
        return false;


    auto fromA = a.from.lock().get();
    auto fromB = b.from.lock().get();
    if (fromA < fromB)
        return true;
    if (fromA > fromB)
        return false;

    auto toA = a.to.lock().get();
    auto toB = b.to.lock().get();
    return toA < toB;
}

//////////////////////////////////////////////////////////////////////////////////////////

void GameMessageStorage::tick()
{
    m_added.swap(m_received);
    m_added.clear();
}

void GameMessageStorage::addMessage(const GameMessage& msg)
{
    m_added.push_back(msg);
}

bool GameMessageStorage::empty() const
{
    return m_received.empty();
}

bool GameMessageStorage::hasMessages(const GameSpritePtr& to, const string& messageString) const
{
    for (auto& msg : m_received)
    {
        if (msg.message != messageString)
            continue;
        if (msg.to.lock() == to || msg.toAllSprites)
            return true;
    }
    return false;
}

vector<GameSpritePtr> GameMessageStorage::getMessages(const GameSpritePtr& to, const string& messageString) const
{
    vector<GameSpritePtr> result;
    for (auto& msg : m_received)
    {
        if (msg.message != messageString)
            continue;
        if (msg.to.lock() == to || msg.toAllSprites)
            result.push_back(msg.from.lock());
    }
    return result;
}
