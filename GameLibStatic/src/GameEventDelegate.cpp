#include "GameEventDelegate.h"

void MouseEventDelegateList::addDelegate(const IMouseEventDelegatePtr& delegate)
{
    m_delegates.push_back(delegate);
}

void MouseEventDelegateList::process(const sf::Event event, GameScene& scene, GameObjectWeakVector& objects)
{
    if(event.type != sf::Event::MouseButtonPressed
    && event.type != sf::Event::MouseButtonReleased
    && event.type != sf::Event::MouseMoved)
    {
        return;
    }

    if(event.type == sf::Event::MouseButtonPressed)
    {
        processLeftButtonDown(event.mouseButton.x, event.mouseButton.y, scene, objects);
    }
    else if(event.type == sf::Event::MouseMoved)
    {
        m_mousePosition.x = event.mouseMove.x;
        m_mousePosition.y = event.mouseMove.y;
    }

    for (auto& wd : m_delegates)
    {
        auto d = wd.lock();
        if (!d)
            continue;
        switch (event.type)
        {
        case sf::Event::MouseButtonPressed:
            d->onButtonDown(event.mouseButton, scene);
            break;
        case sf::Event::MouseButtonReleased:
            d->onButtonUp(event.mouseButton, scene);
            break;
        case sf::Event::MouseMoved:
            d->onMove(event.mouseMove, scene);
            break;
        default:
            break;
        }
    }

    removeDeleted(m_delegates);
}

//////////////////////////////////////////////////////////////////////////////////////
void MouseEventDelegateList::processLeftButtonDown(int x, int y, GameScene& scene, GameObjectWeakVector& objects)
{
    GameObjectVector checked;
    for (auto it = objects.rbegin(); it != objects.rend(); ++it)
    {
        if (auto obj = it->lock())
        {
            if (obj->onLeftButtonDown(x, y, scene))
            {
                checked.push_back(obj);
            }
        }
    }

    if (checked.empty())
        return;

    for (auto& obj : checked)
    {
        if  (obj->onLeftButtonDown(x, y, scene))
        {
            break;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////
void KeyEventDelegateList::addDelegate(const IKeyEventDelegatePtr& delegate)
{
    m_delegates.push_back(delegate);
}

void KeyEventDelegateList::process(const sf::Event event, GameScene& scene)
{
    if(event.type != sf::Event::KeyPressed)
    {
        return;
    }

    for (auto& wd : m_delegates)
    {
        if (auto d = wd.lock())
        {
            d->onKeyPressed(event.key, scene);
        }
    }
    removeDeleted(m_delegates);
}

