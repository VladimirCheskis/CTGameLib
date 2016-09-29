#include "GameScene.h"
#include "FoldersAndPathes.h"

using namespace sf;

static auto* Title = "GameCpp";
//-----------------------------------------------------------------------------
GameScene::GameScene(unsigned int modeWidth, unsigned int modeHeight)
	: m_window(VideoMode(modeWidth, modeHeight), Title)
{
	loadMainFont(FontFile);
	setMainTextStyle(24);
}

bool GameScene::tick()
{
    bool needTick = refreshTime();
    if (!m_window.isOpen())
        return false;
    if (!processWindowEvent())
        return false;
    if (needTick)
    {
        m_spriteCollisionCalculator.tick();
        m_gameMessageStorage.tick();
        tickObjects();
        redrawWindow();
    }
    return true;
}

bool GameScene::refreshTime()
{
    if (m_isStart)
    {
        m_clock.restart();
    }
    m_time = m_clock.getElapsedTime().asSeconds();
    if (m_isStart)
    {
        m_prevTime = m_time;
        m_isStart = false;
        return true;
    }

    m_prevTime = m_time;
    return true;
}

void GameScene::addMouseDelegate(const IMouseEventDelegatePtr& delegate)
{
    m_mouseDelegates.addDelegate(delegate);
}

void GameScene::addKeyDelegate(const IKeyEventDelegatePtr& delegate)
{
    m_keyDelegates.addDelegate(delegate);
}

SpriteCollisionPtr GameScene::collision(const GameSpritePtr& a, const GameSpritePtr& b)
{
    return m_spriteCollisionCalculator.collision(a, b);
}


bool GameScene::processWindowEvent()
{
    Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            m_window.close();
            return false;
        }

        m_mouseDelegates.process(event, *this, m_objects);
        m_keyDelegates.process(event, *this);
    }
    return true;
}

void GameScene::tickObjects()
{
    for( size_t i = 0; i < m_objects.size();++i)
    {
        auto obj = m_objects[i].lock();
        if (obj)
        {
            obj->tick(*this);
        }
    }

    for( int i = m_objects.size()-1; i >=0; --i)
    {
        auto obj = m_objects[i].lock();
        if (obj && !obj->isEnded())
        {
            continue;
        }
        m_objects.erase(m_objects.begin() + i);
    }
}


void GameScene::redrawWindow()
{
    m_window.clear(Color(200,200,200));
    //window.draw(shape);

    for( auto& weak : m_objects)
    {
        auto obj = weak.lock();
        if (obj)
        {
            obj->draw(*this);
        }
    }

    m_window.draw(m_mainText);

    m_window.display();
}

void GameScene::addObject(const GameObjectPtr& obj)
{
    m_objects.push_back(obj);
}

void GameScene::loadMainFont(const std::string& fontFile)
{
    m_mainFont.loadFromFile(fontFile);
    m_mainText.setFont(m_mainFont);
}

void GameScene::setMainText(const std::string& text)
{
    m_mainText.setString(text);
}

void GameScene::setMainTextStyle(unsigned int size, const sf::Color color, unsigned int style)
{
    m_mainText.setCharacterSize(size);
    m_mainText.setStyle(style);
    m_mainText.setColor(color);
}
