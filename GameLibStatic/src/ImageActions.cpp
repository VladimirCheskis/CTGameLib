#include "ImageActions.h"
#include "GameScene.h"

SpriteActionAnimate::SpriteActionAnimate(const GameSpritePtr& sprite,
                                         const IGameAnimatedImagePtr& images,
                                         EAnimationType animationType)
 : m_images(images), m_frameNumberAnimator(images->imageCount(), animationType)
{
    setSprite(sprite);
}

SpriteActionAnimate::SpriteActionAnimate(const GameSpritePtr& sprite,
                                         const std::string& animationName,
                                         EAnimationType animationType)
  : m_frameNumberAnimator(0, animationType)
{
    setSprite(sprite);
    m_images = sprite->animationsSet().get(animationName);
    if (m_images)
    {
        m_frameNumberAnimator.setFrameCount(m_images->imageCount());
    }
}


bool SpriteActionAnimate::isEnded() const
{
    return m_frameNumberAnimator.isEnded();
}

bool SpriteActionAnimate::isBackground() const
{
    return false;
}

void SpriteActionAnimate::tick(GameScene& scene)
{
    auto sprite = m_sprite.lock();
    if (m_frameNumberAnimator.isEnded() || !sprite)
        return;

    m_frameNumberAnimator.tick(scene.time());

    if (m_frameNumberAnimator.isFrameChanged() &&
        !m_frameNumberAnimator.isEnded())
    {
        auto frame = m_frameNumberAnimator.getFrame();
        auto image = m_images->getImage(frame);
        //std::cout << ">" << frame << std::endl;
        sprite->setImage(image);
    }
}

GameActionPtr SpriteActionAnimate::createCopy() const
{
    SpriteActionAnimatePtr result = std::make_shared<SpriteActionAnimate>(m_sprite.lock(), m_images,
                                                                          m_frameNumberAnimator.animationType());
    return result;
}
///////////////////////////////////////////////////////////////////////////////////
SpriteActionSetImage::SpriteActionSetImage(const GameSpritePtr& sprite,
                                           const IGameAnimatedImagePtr& images,
                                           size_t imageIndex)
{
    setSprite(sprite);
    m_image = images->getImage(imageIndex);
}

SpriteActionSetImage::SpriteActionSetImage(const GameSpritePtr& sprite,
                                           const GameImage& image)
{
    setSprite(sprite);
    m_image = image;
}

void SpriteActionSetImage::tick(GameScene& scene)
{
    auto sprite = m_sprite.lock();
    if (!sprite || m_isSeted)
        return;
    m_isSeted = true;
    sprite->setImage(m_image);
}

GameActionPtr SpriteActionSetImage::createCopy() const
{
    auto result = std::make_shared<SpriteActionSetImage>(m_sprite.lock(), m_image);
    return result;
}

