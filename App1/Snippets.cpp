/// ���� ���� ������ ��� ����,
/// ����� �� �� ���������� �������, ��������� ���� �����, ��������� �������� ����������

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GameLib.h"

using namespace std;
using namespace sf;

/// ������� ���������� �������� � ��������
/// ���� ������� ����� ���������� ����
/// �������� - �����
void createSpritesAndActios(GameScene& gameScene)
{
    /// ---------------------------------------------------------
    /// �������� ��������

    /// ������ ������ ������ � ��������� ��� � �����. 100, 120 - ����������
    auto demon = createSpriteDemon(100, 120);
    gameScene.addObject(demon);

    /// ������ ������ ���������� � ��������� ��� � �����. 100, 120 - ����������
    auto wizard = createSpriteWizard(100, 120);
    gameScene.addObject(wizard);

    /// ������ ������ � ��������� ��� � �����. GameSprite(���� � ����� � ������������, x, y)
    auto sprite = make_shared<GameSprite>(DemonPNG + "Crouching__000.png", 100, 120);
    gameScene.addObject(sprite);

    /// ������ ��� ���� ������ � ��������� ��� � �����. GameSprite(���� � ����� � ������������, x, y)
    auto sprite1 = make_shared<GameSprite>(WizardPNG + "Walking__000.png", 300, 120);
    gameScene.addObject(sprite1);

    /// ������������ sprite1 ����� � ������ ������� (� sprite)
    sprite1->turnBack();


    /// ---------------------------------------------------------
    /// ������� �������� (��. MoveActions.h)
    /// ��������� �������� - ����� �������� � ��������
    /// ���� ������ 0 - ����� ���������

    /// ������ ������� ������ � ����� 300, 250 �� 2 �������
    auto moveToPoint = make_shared<SpriteActionMove>(sprite, 300, 250, 2);
    sprite->addAction(moveToPoint);

    /// ��������� ���������� ������ � ����� 300, 250
    auto jumpToPoint = make_shared<SpriteActionMove>(sprite, 300, 250, 0);
    sprite->addAction(jumpToPoint);

    /// ������� ������ � �����, ��� ������ ���� �� 3 �������
    auto moveToMouse = make_shared<SpriteActionMoveToMouse>(sprite, 3);
    sprite->addAction(moveToMouse);

    /// ������� ������ � �����, ��� ������ ������ ������ sprite1 �� 3 �������
    auto moveToSprite = make_shared<SpriteActionMoveToSprite>(sprite, sprite1, 3);
    sprite->addAction(moveToSprite);

    /// �������� ������ �� 10 �� � � �� -10 �� y �� 3 �������
    /// ���� ���������� ������� ���� (100,100), � ����� �������� ����� (110, 90).
    auto moveByVector = make_shared<SpriteActionMoveByVector>(sprite, 10, -10, 3);
    sprite->addAction(moveByVector);

    /// ---------------------------------------------------------
    /// ������� ����� ����������� � �������� (��. ImageActions.h)

    /// ������������� ����������� �� ����� imageFileName, ������ ������� ����� ���������� ���
    auto imageFileName = DemonPNG + "Crouching__000.png";
    auto setImageAction = make_shared<SpriteActionSetImage>(sprite, GameImage(imageFileName, true));
    sprite->addAction(setImageAction);

    /// ��������� �������� "Flame". ������ Die ��������� EAnimationType::Loop - ����������� � �����
    auto animationAction = make_shared<SpriteActionAnimate>(sprite, "Flame", EAnimationType::Die);
    sprite->addAction(animationAction);

    /// �������� Demon'�:  "Attack", "Crouch", "Die", "Hit", "Jump", "Run", "Walk", "Flame".
    /// �������� Wizard'�: "Attack", "Crouch", "Die", "Hit", "Jump", "Run", "Walk".

    /// ---------------------------------------------------------
    /// ������� ������ �� ������ (��. SoundActions.h)

    /// ������ ���� AAA.wav � ���������� 70. ��������� ��� �������������(Id) AAA
    auto playSoundAction = make_shared<PlaySoundAction>(sprite, "AAA", SoundsFolder + "AAA.wav", 70);
    sprite->addAction(playSoundAction);

    /// ��������� ����� ������� � ��������������� (Id) AAA
    auto stopAAAAction = make_shared<StopSoundsByIdAction>(sprite, "AAA");
    sprite->addAction(stopAAAAction);

    /// ��������� ��� ����� �������
    auto stopAllSoundsAction = make_shared<StopAllSoundsAction>(sprite);
    sprite->addAction(stopAllSoundsAction);

    /// ---------------------------------------------------------
    /// ����� (���� �������� ����, ����� ����� ������� ����������)

    /// ������� ����� �������� ���� "���� ����������!"
    auto textAction = make_shared<MaintTextAction>("���� ����������!");
    sprite->addAction(textAction);

    /// ��������� ������ �������� ���� �������� ����� �����
    gameScene.setMainText("�� ���������!");

    /// ��������� ����� ������ �������� ����. � ������� - ������ ������ �� ����.
	gameScene.loadMainFont(FontFile);

    /// ��������� ����� ������ �������� ����.
    /// ������ �������� - ������ (��� ������, ��� ������� �����
    /// ������ - ����.
    /// ����� ������������ �����: sf::Color::White, sf::Color::Red, sf::Color::Green, sf::Color::Blue,...
    /// ������ - �����.
	gameScene.setMainTextStyle(24, sf::Color::Black, sf::Text::Regular);

    /// ---------------------------------------------------------
    ///         �������� �������.
    /// ��� ������� ���� ����������� ���������� �������.
    /// � ����� ������� ��������, ��� "�����������" - ��������� �������, ������� ��������� � ���.
    /// � ���� ������ ���� ������ �������: setIsRepeatable - ����������, �������� �� �����������.
    /// setIsRepeatable(true) - ����� ������������ ��� ������ ������������� �������.
    /// setIsRepeatable(false) - ����� ����������� ������ ���� ���.
    /// ������ ������ ������� addAction(�������) - ��������� �������.

    /// ����� 2 ������� � ��������� ��������
    auto waitAction = make_shared<WaitAction>(2);                              /// ������� �������� 2 �������
    waitAction->addAction(make_shared<SpriteActionMove>(sprite, 300, 250, 2));  /// ������� ��������
    sprite->addAction(waitAction);                                             /// �������� � ������

    /// ����� ������ ������� �����, ����������� ������ � ���������� ������� sprite1
    auto clickAction = make_shared<OnSpriteMouseClickAction>(sprite);
    clickAction->setIsRepeatable(true);
    clickAction->addAction(make_shared<SpriteActionMoveToSprite>(sprite, sprite1, 3));
    sprite->addAction(clickAction);

    /// ����� ������ ������� ������� sprite1, ��������� �������� Flame (�����)
    auto collisionAction = make_shared<OnSpriteCollsionAction>(sprite, sprite1);
    collisionAction->setIsRepeatable(true);
    collisionAction->addAction(make_shared<SpriteActionAnimate>(sprite, "Flame", EAnimationType::Die));
    sprite->addAction(collisionAction);

    /// ����� ������ ������� ������ (Right), �������� ������ �� � �� 50 (�� y �� 0, �� 0 ������)
    auto keyRightAction = make_shared<OnKeyPressedAction>(Keyboard::Key::Right);
    keyRightAction->setIsRepeatable(true);
    keyRightAction->addAction(make_shared<SpriteActionMoveByVector>(sprite, 50, 0, 0));
    sprite->addAction(keyRightAction);

    /// ---------------------------------------------------------
    ///         ��������� (���������� ��������� ��������).

    /// �������� "������!" ���� ��������
    auto sendToAllMessage = make_shared<SentMessageAction>(sprite, "������!");
    sprite->addAction(sendToAllMessage);

    /// �������� "������!" ������ ������� demon
    auto sendToDemonMessage = make_shared<SentMessageAction>(sprite, demon, "������!");
    sprite->addAction(sendToDemonMessage);

    /// ����� � ������ "������!" ...
    auto onMessage = make_shared<OnMessageAction>(demon, "������!");
    onMessage->addAction(make_shared<SpriteActionMoveByVector>(demon, 50, 0, 0));
    demon->addAction(onMessage);
}

/// ������ ������� ������� ���������,
/// ������� ������ ����� � ����� �������� � ������������ ���������
/// ���������� ����� ����������� � main()
int mainSnippet()
{
    /// ������������� ���� � ������ ������ � ������
    initFoldersAndPathes();

    /// ������ �����, (������, ������)
    GameScene gameScene(512,    512   );

    /// ����� ������ ��������� � ����� �������, ������� ��� ���

    /// ������� ����: ������������ ���������, ����������� �������,
    /// ���� ���� �� �������
	while (gameScene.tick());

    /// ���������� ��� ������ 0
	return 0;
}
