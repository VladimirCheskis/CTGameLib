#include "TextActions.h"
#include "GameScene.h"

MaintTextAction::MaintTextAction(const string& text)
  : m_text(text)
{

}

void MaintTextAction::tickImpl(GameScene& scene)
{
    scene.setMainText(m_text);
}

GameActionPtr MaintTextAction::createCopy() const
{
    return std::make_shared<MaintTextAction>(m_text);
}
