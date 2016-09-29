#include "GameAction.h"


void GameActionList::addAction(const GameActionPtr& action)
{
    m_actions.push_back(action);
}

bool GameActionList::isEnded() const
{
    for( auto& action : m_actions)
    {
        if (!action->isEnded())
            return false;
    }
    return true;
}

bool GameActionList::isBackground() const
{
    for( auto& action : m_actions)
    {
        if (!action->isEnded() && !action->isBackground())
            return false;
    }
    return true;

}

void GameActionList::tick(GameScene& scene)
{
    for( auto& action : m_actions)
    {
        action->tick(scene);
    }
}

bool GameActionList::needLeftButtonDown() const
{
    for (const auto& action : m_actions)
    {
        if (action->needLeftButtonDown())
            return true;
    }
    return false;
}

void GameActionList::onLeftButtonDown(const sf::Color& color)
{
    for (auto& action : m_actions)
    {
        action->onLeftButtonDown(color);
    }
}

GameActionPtr GameActionList::createCopy() const
{
    GameActionListPtr result = make_shared<GameActionList>();
    addCopiesTo(*result);
    return result;
}

void GameActionList::addCopiesTo(GameActionList& dst) const
{
    for (auto& action : m_actions)
    {
        auto copy = action->createCopy();
        if (copy)
            dst.addAction(copy);
    }
}
