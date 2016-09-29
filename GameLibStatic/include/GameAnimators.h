#pragma once

#include "GameImage.h"

class IGameAnimatedImage
{
public:
    virtual ~IGameAnimatedImage() = default;

    virtual size_t imageCount() = 0;
    virtual GameImage getImage(size_t imageNumber) = 0;
};
DEFINE_STD(IGameAnimatedImage);

class GameAnimatedImageFromSheet : public IGameAnimatedImage
{
public:
    GameAnimatedImageFromSheet(const GameTexturePtr& texture,
                               sf::IntRect& firstImageRect,
                               size_t xCount, size_t yCount, size_t count);
    GameAnimatedImageFromSheet(const string& textureFile, bool firstPixelTransparent,
                               sf::IntRect& firstImageRect,
                               size_t xCount, size_t yCount, size_t count);
    GameAnimatedImageFromSheet(const string& textureFile, bool firstPixelTransparent,
                               size_t xCount, size_t yCount, size_t count);

    virtual size_t imageCount() override;
    virtual GameImage getImage(size_t imageNumber) override;

private:
    GameTexturePtr m_texture;
    sf::IntRect    m_firstImageRect;
    size_t m_counts[2];
    size_t  m_imageCount;
};
DEFINE_STD(GameAnimatedImageFromSheet);

enum class FrameIndexFormat
{
    Format1,
    Format01,
    Format001,
    Format0001,
    Format00001
};

class GameAnimatedImageFromFiles : public IGameAnimatedImage
{
public:
    GameAnimatedImageFromFiles(const string& filePathStart,
                               const string& fileNameFormat,
                               size_t fileFirstIndex, size_t fileCount,
                               bool firstPixelTransparent);

    virtual size_t imageCount() override;
    virtual GameImage getImage(size_t imageNumber) override;
private:
    string m_filePathStart;
    string m_fileNameFormat;
    size_t m_fileFirstIndex;
    size_t m_fileCount;
    bool m_firstPixelTransparent;
};
DEFINE_STD(GameAnimatedImageFromFiles);

GameAnimatedImageFromFilesPtr createAnimatorFromFiles(const string& filePathStart,
                                                      bool firstPixelTransparent);


enum class EAnimationType
{
    Loop,
    Die,
    Stay
};

const auto ANIMATION_STEP = 1.f / 30.f;

class GameNumberAnimator
{
public:
    GameNumberAnimator(size_t framesCout, EAnimationType animationType, float step = ANIMATION_STEP);
    virtual ~GameNumberAnimator() = default;
    void setFrameCount(size_t framesCout);
    void restart(float currentTime);
    void tick(float currentTime);
    size_t getFrame() const;
    bool   isFrameChanged() const {return m_isFrameChanged;}
    bool isEnded() const;

    EAnimationType animationType() const {return m_animationType;}
public:
    void refreshFrameAndIsEnded(float currentTime);
    float m_startTime;
    float m_step;
    size_t m_framesCout;

    bool m_isStarted;
    bool m_isEnded;
    size_t m_currentFrame;
    size_t m_isFrameChanged;
    EAnimationType m_animationType;
};

class GameAnimationsSet
{
public:
  IGameAnimatedImagePtr get(const std::string& ainmationName) const;
  void set(const std::string& ainmationName, const IGameAnimatedImagePtr& animation);

  void setSheet(const std::string& ainmationName, const std::string& path,
                size_t xCount, size_t yCount, size_t count = 0, bool firstPixelTransparent = true);
  std::vector<std::string> getAnimationsNames();
private:
  using Animations = std::map<std::string, IGameAnimatedImagePtr>;
  Animations m_animations;
};
