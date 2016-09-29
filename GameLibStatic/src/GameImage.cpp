#include "GameImage.h"

GameTexture::GameTexture(const char* filePath, bool firstPixelTransparent)
{
    m_image.loadFromFile(filePath);
    if (!firstPixelTransparent)
    {
        m_texture.loadFromImage(m_image);
        return;
    }

    auto sz = m_image.getSize();
    if (sz.x * sz.y > 0)
    {
        auto color = m_image.getPixel(0,0);
        m_image.createMaskFromColor(color);
        m_texture.loadFromImage(m_image);
    }
}


GameTexturePtr GameTextureStorage::get(const string& filePath, bool firstPixelTransparent)
{
    auto it = m_storedTextures.find(filePath);
    if (it != m_storedTextures.end())
    {
        auto texture = it->second.lock();
        if (texture)
            return texture;
    }
    auto texture = std::make_shared<GameTexture>(filePath.c_str(), firstPixelTransparent);
    m_storedTextures[filePath] = texture;
    return texture;
}

GameTexturePtr GameTextureStorage::hold(const string& filePath, bool firstPixelTransparent)
{
    auto it = m_holdedTextures.find(filePath);
    if (it != m_holdedTextures.end())
        return it->second;

    auto it1 = m_storedTextures.find(filePath);
    if (it1 != m_storedTextures.end())
    {
        auto texture = it1->second.lock();
        if (texture)
        {
            m_holdedTextures[filePath] = texture;
            return texture;
        }
    }
    auto texture = std::make_shared<GameTexture>(filePath.c_str(), firstPixelTransparent);
    m_storedTextures[filePath] = texture;
    m_holdedTextures[filePath] = texture;
    return texture;
}


GameTexturePtr getTexture(const string& filePath, bool firstPixelTransparent)
{
    static GameTextureStorage storage;
    return storage.get(filePath, firstPixelTransparent);
}

GameImage::GameImage(const string& filePath, bool firstPixelTransparent)
{
    texture = getTexture(filePath, firstPixelTransparent);
}

GameImage::GameImage(const string& filePath, const sf::IntRect& rect, bool firstPixelTransparent)
{
    texture = getTexture(filePath, firstPixelTransparent);
    rectangle = rect;
}

GameImage::GameImage(const GameTexturePtr _texture) : texture(_texture)
{

}
