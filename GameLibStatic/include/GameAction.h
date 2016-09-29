#ifndef SCENEACTION_H
#define SCENEACTION_H

#include <Common.h>

class GameScene;
class GameAction;
class GameActionList;
DEFINE_STD(GameAction);
DEFINE_STD(GameActionList);
////////////////////////////////////////////////////////////////////////////////////////
//��������, ������������� �� ����� ������������ ������
class GameAction
{
public:
  virtual ~GameAction() = default;
  //�������� �����������, ����� �������
  virtual bool isEnded() const = 0;
  //�������� �� �����������, �� ����� ��������� ���������
  virtual bool isBackground() const = 0;

  //������� ��� ����� � ������ ����
  virtual void tick(GameScene& scene) = 0;

  virtual GameActionPtr createCopy() const = 0;

  virtual bool needLeftButtonDown() const {return false;}
  virtual void onLeftButtonDown(const sf::Color&) {}
};


class GameActionList : public GameAction
{
public:
    GameActionList() = default;
    void addAction(const GameActionPtr& action);
    bool empty() const { return m_actions.empty();}

    bool isEnded() const override;
    bool isBackground() const override;
    void tick(GameScene& scene) override;

    bool needLeftButtonDown() const;
    void onLeftButtonDown(const sf::Color&);

    GameActionPtr createCopy() const override;
    void addCopiesTo(GameActionList& dst) const;
private:
    GameActionVector m_actions;
};


#endif // SCENEACTION_H
