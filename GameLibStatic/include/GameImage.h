#ifndef GAMEIMAGE_H
#define GAMEIMAGE_H

#include "Common.h"
#include "GameObject.h"

class GameTexture
{
public:
    GameTexture(const char* filePath, bool firstPixelTransparent);
    const sf::Texture& getTexture() const { return m_texture; }
    const sf::Image& getImage() const { return m_image; }
private:
    sf::Texture m_texture;
    sf::Image   m_image;
};
DEFINE_STD(GameTexture);

class GameTextureStorage
{
public:
    GameTextureStorage() = default;

    GameTexturePtr get(const string& filePath, bool firstPixelTransparent);
    GameTexturePtr hold(const string& filePath, bool firstPixelTransparent);
private:
    using HoldedTextures = map<string, GameTexturePtr> ;
    using StoredTextures = map<string, GameTextureWeakPtr> ;

    HoldedTextures m_holdedTextures;
    StoredTextures m_storedTextures;
};

GameTexturePtr getTexture(const string& filePath, bool firstPixelTransparent);

struct GameImage
{
    GameTexturePtr texture;
    sf::IntRect rectangle;

    GameImage() = default;
    GameImage(const string& filePath, bool firstPixelTransparent = false);
    GameImage(const string& filePath, const sf::IntRect& rect, bool firstPixelTransparent = false);
    GameImage(const GameTexturePtr _texture);
};
#endif // GAMESIMAGE_H
