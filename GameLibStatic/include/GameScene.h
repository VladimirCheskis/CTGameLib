#pragma once

#include "GameObject.h"
#include "GameEventDelegate.h"
#include "SpriteCollisions.h"
#include "GameMessages.h"


class GameScene
{
public:
    GameScene(unsigned int modeWidth = 512, unsigned int modeHeight = 512);

    bool tick();

    void addObject(const GameObjectPtr& obj);

    sf::RenderWindow& getWindow() { return m_window; }
    float time() const {return m_time;}

    void addMouseDelegate(const IMouseEventDelegatePtr& delegate);
    void addKeyDelegate(const IKeyEventDelegatePtr& delegate);
    SpriteCollisionPtr collision(const GameSpritePtr& a, const GameSpritePtr& b);

    const sf::Text& mainText() const { return m_mainText; }
	const sf::Font& mainFont() const { return m_mainFont; }

	void setMainText(const std::string& );
	void loadMainFont(const std::string& fontFile);
	void setMainTextStyle(unsigned int size, const sf::Color color = sf::Color::Black, unsigned int style = sf::Text::Regular);

    const Point& getMousePosition() const
        { return m_mouseDelegates.getMousePosition(); }

    GameMessageStorage& getGameMessageStorage()
        { return m_gameMessageStorage; }

private:
    bool processWindowEvent();
    void redrawWindow();
    void tickObjects();
    bool refreshTime();

    sf::RenderWindow m_window;
    GameObjectWeakVector m_objects;

    MouseEventDelegateList m_mouseDelegates;
    KeyEventDelegateList m_keyDelegates;
    SpriteCollisionCalculator m_spriteCollisionCalculator;
    GameMessageStorage m_gameMessageStorage;

	sf::Font m_mainFont;
    sf::Text m_mainText;

    sf::Clock m_clock;
    float m_time = 0.f;
    float m_prevTime = 0.f;
    bool m_isStart = true;
};
DEFINE_STD(GameScene);
