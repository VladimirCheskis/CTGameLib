#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GameLib.h"
#include "FileUtils.h"

using namespace std;
using namespace sf;

int main()
{
    /// ������������� ���� � ������ ������ � ������
    initFoldersAndPathes();

    auto test = createAnimatorFromFiles(DemonPNG + "Attack__", false);

    /// ������ �����, (������, ������)
    GameScene gameScene(712,    512   );

    /// ������ � ��������� � ����� �������, ������ ��� ��� �������

    /// ������ ������ ������ � ��������� ��� � �����. 100, 120 - ����������
    auto demon = createSpriteDemon(100, 120);
    gameScene.addObject(demon);

    /// ������ ������ ���������� � ��������� ��� � �����. 100, 120 - ����������
    auto wizard = createSpriteWizard(500, 120);
    gameScene.addObject(wizard);

    /// ����� ������ ������� �����, ����������� ������ � ���������� ������� sprite1
    auto clickAction = make_shared<OnSpriteMouseClickAction>(demon);
    clickAction->setIsRepeatable(true);
    clickAction->addAction(make_shared<SpriteActionAnimate>(demon, test, EAnimationType::Die));
    clickAction->addAction(make_shared<SentMessageAction>(demon, wizard , "������!"));
    demon->addAction(clickAction);

    auto onMessage = make_shared<OnMessageAction>(wizard, "������!");
    onMessage->addAction(make_shared<SpriteActionMoveByVector>(wizard, 50, 0, 1));
    onMessage->setIsRepeatable(true);
    wizard->addAction(onMessage);

    /// ������� ����: ������������ ���������, ����������� �������,
    /// ���� ���� �� �������
	while (gameScene.tick());

	return 0;
}
