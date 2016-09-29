#pragma once

#include "GameSprite.h"

class MaintTextAction : public SpriteInstantAction
{
public:
      MaintTextAction(const string& text);
protected:
    virtual GameActionPtr createCopy() const override;
    virtual void tickImpl(GameScene& scene) override;
private:
    string    m_text;
};
