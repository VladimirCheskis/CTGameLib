#include "GameAnimators.h"
#include "FileUtils.h"

GameAnimatedImageFromSheet::GameAnimatedImageFromSheet(const GameTexturePtr& texture,
                                                       sf::IntRect& firstImageRect,
                                                       size_t xCount, size_t yCount, size_t count)
 : m_texture(texture), m_firstImageRect(firstImageRect), m_imageCount(count)
{
   m_counts[0] = xCount;
   m_counts[1] = yCount;
}

GameAnimatedImageFromSheet::GameAnimatedImageFromSheet(const string& textureFile, bool firstPixelTransparent,
                                                       sf::IntRect& firstImageRect,
                                                       size_t xCount, size_t yCount, size_t count)
 : m_firstImageRect(firstImageRect), m_imageCount(count)
{
   //std::cout << "GameAnimatedImageFromSheet " << textureFile << std::endl;
   m_texture = getTexture(textureFile, firstPixelTransparent);
   m_counts[0] = xCount;
   m_counts[1] = yCount;
}

GameAnimatedImageFromSheet::GameAnimatedImageFromSheet(const string& textureFile, bool firstPixelTransparent,
                                                       size_t xCount, size_t yCount, size_t count)
  : m_imageCount(count)
{
   m_texture = getTexture(textureFile, firstPixelTransparent);
   m_counts[0] = xCount;
   m_counts[1] = yCount;

   m_firstImageRect.left = 0;
   m_firstImageRect.top = 0;

   auto size = m_texture ? m_texture->getTexture().getSize() : sf::Vector2u();
   m_firstImageRect.width = size.x / xCount;
   m_firstImageRect.height = size.y / yCount;
}



GameImage GameAnimatedImageFromSheet::getImage(size_t imageNumber)
{
 GameImage image(m_texture);
 image.rectangle.width = m_firstImageRect.width;
 image.rectangle.height = m_firstImageRect.height;

 size_t m_indexes[2];
 m_indexes[0] = imageNumber % m_counts[0];
 m_indexes[1] = imageNumber / m_counts[0];

 image.rectangle.left = m_firstImageRect.left + m_firstImageRect.width * m_indexes[0];
 image.rectangle.top  = m_firstImageRect.top + m_firstImageRect.height * m_indexes[1];

 return image;
}

size_t GameAnimatedImageFromSheet::imageCount()
{
    return m_imageCount;
}

///////////////////////////////////////////////////////////////////////////////////
GameAnimatedImageFromFiles::GameAnimatedImageFromFiles(const string& filePathStart,
                                                       const string& fileNameFormat,
                                                       size_t fileFirstIndex, size_t fileCount,
                                                       bool firstPixelTransparent)
: m_filePathStart(filePathStart), m_fileNameFormat(fileNameFormat),
  m_fileFirstIndex(fileFirstIndex),
  m_fileCount(fileCount), m_firstPixelTransparent(firstPixelTransparent)
{
   //std::cout << "GameAnimatedImageFromFiles " << filePathStart << std::endl;
}

GameImage GameAnimatedImageFromFiles::getImage(size_t imageNumber)
{
  char buff[1024];
  snprintf(buff, sizeof(buff), m_fileNameFormat.c_str(), m_filePathStart.c_str(), imageNumber - m_fileFirstIndex);
  GameImage image(buff, m_firstPixelTransparent);
  return image;
}

size_t GameAnimatedImageFromFiles::imageCount()
{
    return m_fileCount;
}

GameAnimatedImageFromFilesPtr createAnimatorFromFiles(const string& filePathStart,
                                                      bool firstPixelTransparent)
{
    FileIndexChecker checker(filePathStart);
    auto func = [&checker](const string& fileName) -> bool
    {
        checker.add(fileName);
        return true;
    };

    auto filter = filePathStart + "*";
    iterateFiles(filter, func);

    checker.build();

    return make_shared<GameAnimatedImageFromFiles>(filePathStart,
                                                   checker.fileFilter(), checker.fileFirstIndex(), checker.fileCount(), firstPixelTransparent);
}

///////////////////////////////////////////////////////////////////////////////////
GameNumberAnimator::GameNumberAnimator(size_t framesCout, EAnimationType animationType, float step)
 : m_step(step), m_framesCout(framesCout), m_animationType(animationType)
{
    m_isEnded = m_framesCout == 0;
    m_currentFrame = 0;
    m_isFrameChanged = true;
    m_isStarted = false;
}

void GameNumberAnimator::setFrameCount(size_t framesCout)
{
    m_framesCout = framesCout;
}

void GameNumberAnimator::restart(float currentTime)
{
    m_startTime = currentTime;
    m_isEnded = m_framesCout == 0;
    m_isStarted = true;
    m_currentFrame = 0;
    m_isFrameChanged = true;
}

void GameNumberAnimator::refreshFrameAndIsEnded(float currentTime)
{
    m_currentFrame = size_t((currentTime - m_startTime) / m_step);
    m_isEnded = false;

    if (m_currentFrame < m_framesCout)
        return;

    switch(m_animationType)
    {
    case EAnimationType::Loop:
        m_currentFrame = m_currentFrame % m_framesCout;
        break;
    case EAnimationType::Die:
        m_currentFrame = 0;
        m_isEnded = true;
        break;
    case EAnimationType::Stay:
        m_currentFrame = m_framesCout - 1;
        break;
    }
}

void GameNumberAnimator::tick(float currentTime)
{
    if (!m_isStarted)
    {
        restart(currentTime);
        return;
    }
    auto prevFrame = m_currentFrame;
    refreshFrameAndIsEnded(currentTime);
    m_isFrameChanged = prevFrame != m_currentFrame;
}

size_t GameNumberAnimator::getFrame() const
{
    return m_currentFrame;
}

bool GameNumberAnimator::isEnded() const
{
    return m_isEnded;
}

IGameAnimatedImagePtr GameAnimationsSet::get(const std::string& ainmationName) const
{
    auto it = m_animations.find(ainmationName);
    return it != m_animations.end() ? it->second : nullptr;
}

void GameAnimationsSet::setSheet(const std::string& ainmationName, const std::string& path,
                                 size_t xCount, size_t yCount, size_t count, bool firstPixelTransparent)
{
    auto realCount = count > 0 ? count : xCount * yCount;
    set(ainmationName, make_shared<GameAnimatedImageFromSheet>(path, firstPixelTransparent, xCount, yCount, realCount));
}

void GameAnimationsSet::set(const std::string& ainmationName, const IGameAnimatedImagePtr& animation)
{
    m_animations[ainmationName] = animation;
}

std::vector<std::string> GameAnimationsSet::getAnimationsNames()
{
    std::vector<std::string> result;
    for ( const auto& it : m_animations)
        result.push_back(it.first);
    return result;
}
