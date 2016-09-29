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
    /// устанавливаем пути к нужным папкам и файлам
    initFoldersAndPathes();

    auto test = createAnimatorFromFiles(DemonPNG + "Attack__", false);

    /// Создаём сцену, (ширина, высота)
    GameScene gameScene(712,    512   );

    /// Создаёт и добавляет в сцену спрайты, создаь для них скрипты

    /// Создаём спрайт демона и добавляем его в сцену. 100, 120 - координаты
    auto demon = createSpriteDemon(100, 120);
    gameScene.addObject(demon);

    /// Создаём спрайт волшебника и добавляем его в сцену. 100, 120 - координаты
    auto wizard = createSpriteWizard(500, 120);
    gameScene.addObject(wizard);

    /// Когда спрайт кликнут мышью, переместить спрайт в координаты спрайта sprite1
    auto clickAction = make_shared<OnSpriteMouseClickAction>(demon);
    clickAction->setIsRepeatable(true);
    clickAction->addAction(make_shared<SpriteActionAnimate>(demon, test, EAnimationType::Die));
    clickAction->addAction(make_shared<SentMessageAction>(demon, wizard , "Привет!"));
    demon->addAction(clickAction);

    auto onMessage = make_shared<OnMessageAction>(wizard, "Привет!");
    onMessage->addAction(make_shared<SpriteActionMoveByVector>(wizard, 50, 0, 1));
    onMessage->setIsRepeatable(true);
    wizard->addAction(onMessage);

    /// Игровой цикл: обрабатываем сообщения, проигрываем команды,
    /// пока окно не закроют
	while (gameScene.tick());

	return 0;
}
