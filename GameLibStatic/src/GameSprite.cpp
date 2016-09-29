#include "GameSprite.h"
#include "GameScene.h"
#include "SpriteCollisions.h"

//-----------------------------------------------------------------------------
GameSprite::GameSprite(const std::string& imageFileName, int x, int y)
{
    GameImage image(imageFileName);
    setImage(image);
    setPlace(x, y);
}

//-----------------------------------------------------------------------------
void GameSprite::setImage(const GameImage& image)
{
    m_image = image;
    if (!image.texture)
    {
        m_sprite.setTexture(sf::Texture());
        return;
    }

    bool useRect = image.rectangle.width > 0;
    m_sprite.setTexture(image.texture->getTexture(), !useRect);
    if (useRect)
        m_sprite.setTextureRect(image.rectangle);
}

//-----------------------------------------------------------------------------
void GameSprite::setOrigin(int x, int y)
{
    m_sprite.setOrigin(x, y);
}

//-----------------------------------------------------------------------------
void GameSprite::setPlace(int x, int y)
{
    m_sprite.setPosition(x, y);
}

//-----------------------------------------------------------------------------
void GameSprite::rotate(float degrees)
{
    m_sprite.rotate(degrees);
}

void GameSprite::turnBack()
{
    m_sprite.scale(-1, 1);
}

void GameSprite::scale(float scaleCoeff)
{
    m_sprite.scale(scaleCoeff, scaleCoeff);
}

void GameSprite::setScale(float newScale)
{
    float s[] = {newScale, newScale};
    auto& curScale = m_sprite.getScale();
    if (curScale.x < 0)
        s[0] *= -1;
    if (curScale.y < 0)
        s[1] *= -1;
    m_sprite.setScale(s[0], s[1]);
}

//-----------------------------------------------------------------------------
void GameSprite::getPlace(float &x, float &y)
{
    auto& v = m_sprite.getPosition();
    x = v.x;
    y = v.y;
}

bool GameSprite::checkPoint(float x, float y) const
{
    sf::Color color = sf::Color::Black;
    return spriteColor(m_sprite, m_image.texture->getImage(), x, y, color);
}


//-----------------------------------------------------------------------------
void GameSprite::draw(GameScene& scene)
{
 scene.getWindow().draw(m_sprite);
}

//-----------------------------------------------------------------------------
void GameSprite::tick(GameScene& scene)
{
    m_actions.tick(scene);
}

//-----------------------------------------------------------------------------
void GameSprite::addAction(const GameActionPtr& action)
{
    m_actions.addAction(action);
}

//-----------------------------------------------------------------------------
bool GameSprite::needLeftButtonDown() const
{
    return m_actions.needLeftButtonDown();
}

//-----------------------------------------------------------------------------
bool GameSprite::onLeftButtonDown(int x, int y, GameScene& scene)
{
    if (!m_image.texture)
        return false;
    sf::Color color = sf::Color::Black;
    if (!spriteColor(m_sprite, m_image.texture->getImage(), x, y, color))
        return false;
    m_actions.onLeftButtonDown(color);
    return true;
}
