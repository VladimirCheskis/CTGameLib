#pragma once

#include "GameObject.h"

class GameScene;

class IMouseEventDelegate
{
public:

    virtual ~IMouseEventDelegate () = default;

    using MouseButtonEvent = sf::Event::MouseButtonEvent;
    using MouseMoveEvent = sf::Event::MouseMoveEvent;

    virtual void onButtonDown(const MouseButtonEvent& event, GameScene& scene) = 0;
    virtual void onButtonUp(const MouseButtonEvent& event, GameScene& scene) = 0;
    virtual void onMove(const MouseMoveEvent& event, GameScene& scene) = 0;
};
DEFINE_STD(IMouseEventDelegate);

class MouseEventDelegateList
{
public:
    void addDelegate(const IMouseEventDelegatePtr& delegate);
    void process(const sf::Event event, GameScene& scene, GameObjectWeakVector& objects);
    const Point& getMousePosition() const
        { return m_mousePosition; }
private:
    void processLeftButtonDown(int x, int y, GameScene& scene, GameObjectWeakVector& objects);
    IMouseEventDelegateWeakVector m_delegates;
    Point m_mousePosition;
};

class IKeyEventDelegate
{
public:

    virtual ~IKeyEventDelegate () = default;

    using KeyEvent = sf::Event::KeyEvent;

    virtual void onKeyPressed(const KeyEvent& event, GameScene& scene) = 0;
};
DEFINE_STD(IKeyEventDelegate);

class KeyEventDelegateList
{
public:
    void addDelegate(const IKeyEventDelegatePtr& delegate);
    void process(const sf::Event event, GameScene& scene);
private:
    IKeyEventDelegateWeakVector m_delegates;
};
