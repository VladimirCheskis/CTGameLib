/// Этот файл создан для того,
/// чтобы из неё копировали кусочки, вставляли куда нужно, измееняли значения параметров

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GameLib.h"

using namespace std;
using namespace sf;

/// Примеры добавления спрайтов и скриптов
/// Сама функция будет определена ниже
/// Аргумент - сцена
void createSpritesAndActios(GameScene& gameScene)
{
    /// ---------------------------------------------------------
    /// Создание спрайтов

    /// Создаём спрайт демона и добавляем его в сцену. 100, 120 - координаты
    auto demon = createSpriteDemon(100, 120);
    gameScene.addObject(demon);

    /// Создаём спрайт волшебника и добавляем его в сцену. 100, 120 - координаты
    auto wizard = createSpriteWizard(100, 120);
    gameScene.addObject(wizard);

    /// Создаём спрайт и добавляем его в сцену. GameSprite(путь к файлу с изображением, x, y)
    auto sprite = make_shared<GameSprite>(DemonPNG + "Crouching__000.png", 100, 120);
    gameScene.addObject(sprite);

    /// Создаём ещё один спрайт и добавляем его в сцену. GameSprite(путь к файлу с изображением, x, y)
    auto sprite1 = make_shared<GameSprite>(WizardPNG + "Walking__000.png", 300, 120);
    gameScene.addObject(sprite1);

    /// Поворачиваем sprite1 лицом в другую сторону (к sprite)
    sprite1->turnBack();


    /// ---------------------------------------------------------
    /// Команды движения (см. MoveActions.h)
    /// Последний параметр - время движения в секундах
    /// Если задать 0 - будет мгновенно

    /// Плавно двигает спрайт в точку 300, 250 за 2 секунды
    auto moveToPoint = make_shared<SpriteActionMove>(sprite, 300, 250, 2);
    sprite->addAction(moveToPoint);

    /// Мгновенно перемещает спрайт в точку 300, 250
    auto jumpToPoint = make_shared<SpriteActionMove>(sprite, 300, 250, 0);
    sprite->addAction(jumpToPoint);

    /// Двигает спрайт в точку, где сейчас мышь за 3 секунды
    auto moveToMouse = make_shared<SpriteActionMoveToMouse>(sprite, 3);
    sprite->addAction(moveToMouse);

    /// Двигает спрайт в точку, где сейчас другой спрайт sprite1 за 3 секунды
    auto moveToSprite = make_shared<SpriteActionMoveToSprite>(sprite, sprite1, 3);
    sprite->addAction(moveToSprite);

    /// Сдвигает спрайт на 10 по х и на -10 по y за 3 секунды
    /// Если координаты спрайта были (100,100), в конце движения будут (110, 90).
    auto moveByVector = make_shared<SpriteActionMoveByVector>(sprite, 10, -10, 3);
    sprite->addAction(moveByVector);

    /// ---------------------------------------------------------
    /// Команды смены изображения и анимации (см. ImageActions.h)

    /// Устанавливает изображение из файла imageFileName, первый пиксель задаёт прозрачный фон
    auto imageFileName = DemonPNG + "Crouching__000.png";
    auto setImageAction = make_shared<SpriteActionSetImage>(sprite, GameImage(imageFileName, true));
    sprite->addAction(setImageAction);

    /// Запускает анимацию "Flame". Вместо Die поставить EAnimationType::Loop - проигрывать в цикле
    auto animationAction = make_shared<SpriteActionAnimate>(sprite, "Flame", EAnimationType::Die);
    sprite->addAction(animationAction);

    /// Анимации Demon'а:  "Attack", "Crouch", "Die", "Hit", "Jump", "Run", "Walk", "Flame".
    /// Анимации Wizard'а: "Attack", "Crouch", "Die", "Hit", "Jump", "Run", "Walk".

    /// ---------------------------------------------------------
    /// Команды работы со звуком (см. SoundActions.h)

    /// Играть звук AAA.wav с громкостью 70. Присвоить ему идентификатор(Id) AAA
    auto playSoundAction = make_shared<PlaySoundAction>(sprite, "AAA", SoundsFolder + "AAA.wav", 70);
    sprite->addAction(playSoundAction);

    /// Выключить звуки спрайта с идентификатором (Id) AAA
    auto stopAAAAction = make_shared<StopSoundsByIdAction>(sprite, "AAA");
    sprite->addAction(stopAAAAction);

    /// Выключить все звуки спрайта
    auto stopAllSoundsAction = make_shared<StopAllSoundsAction>(sprite);
    sprite->addAction(stopAllSoundsAction);

    /// ---------------------------------------------------------
    /// Текст (пока главного окна, потом будут реплики персонажей)

    /// Вывести титры главного окна "Игра начинается!"
    auto textAction = make_shared<MaintTextAction>("Игра начинается!");
    sprite->addAction(textAction);

    /// Установка титров главного окна напрямую через сцену
    gameScene.setMainText("Вы проиграли!");

    /// Установка фонта титров главного окна. В скобках - строка ссылка на фонт.
	gameScene.loadMainFont(FontFile);

    /// Установка стиля титров главного окна.
    /// Первый параметр - размер (чем больше, тем крупнее буквы
    /// Второй - цвет.
    /// Можно использовать цвета: sf::Color::White, sf::Color::Red, sf::Color::Green, sf::Color::Blue,...
    /// Третий - стиль.
	gameScene.setMainTextStyle(24, sf::Color::Black, sf::Text::Regular);

    /// ---------------------------------------------------------
    ///         Ожидание событий.
    /// Эти команды ждут наступления некоторого события.
    /// И когда событие наступит, они "срабатывают" - запускают команды, которые добавлены в них.
    /// У этих команд есть важная функция: setIsRepeatable - установить, является ли повторяемой.
    /// setIsRepeatable(true) - будет срабатываьть при каждом возникновении события.
    /// setIsRepeatable(false) - будет срабатывать только один раз.
    /// Другая важная функция addAction(команда) - добавляет команду.

    /// Ждать 2 секунды и выполнить движение
    auto waitAction = make_shared<WaitAction>(2);                              /// Создали задержку 2 секунды
    waitAction->addAction(make_shared<SpriteActionMove>(sprite, 300, 250, 2));  /// Команда движения
    sprite->addAction(waitAction);                                             /// Добавили в спрайт

    /// Когда спрайт кликнут мышью, переместить спрайт в координаты спрайта sprite1
    auto clickAction = make_shared<OnSpriteMouseClickAction>(sprite);
    clickAction->setIsRepeatable(true);
    clickAction->addAction(make_shared<SpriteActionMoveToSprite>(sprite, sprite1, 3));
    sprite->addAction(clickAction);

    /// Когда спрайт коснётся спрайта sprite1, проиграть анимацию Flame (пламя)
    auto collisionAction = make_shared<OnSpriteCollsionAction>(sprite, sprite1);
    collisionAction->setIsRepeatable(true);
    collisionAction->addAction(make_shared<SpriteActionAnimate>(sprite, "Flame", EAnimationType::Die));
    sprite->addAction(collisionAction);

    /// Когда нажмут стрелку вправо (Right), сдвинуть спрайт по х на 50 (по y на 0, за 0 секунд)
    auto keyRightAction = make_shared<OnKeyPressedAction>(Keyboard::Key::Right);
    keyRightAction->setIsRepeatable(true);
    keyRightAction->addAction(make_shared<SpriteActionMoveByVector>(sprite, 50, 0, 0));
    sprite->addAction(keyRightAction);

    /// ---------------------------------------------------------
    ///         Сообщения (посылаемые спрайтами спрайтам).

    /// Посылаем "Привет!" всем спрайтам
    auto sendToAllMessage = make_shared<SentMessageAction>(sprite, "Привет!");
    sprite->addAction(sendToAllMessage);

    /// Посылаем "Привет!" только спрайту demon
    auto sendToDemonMessage = make_shared<SentMessageAction>(sprite, demon, "Привет!");
    sprite->addAction(sendToDemonMessage);

    /// Когда я получу "Привет!" ...
    auto onMessage = make_shared<OnMessageAction>(demon, "Привет!");
    onMessage->addAction(make_shared<SpriteActionMoveByVector>(demon, 50, 0, 0));
    demon->addAction(onMessage);
}

/// Пример главной функции программы,
/// которая создаёт сцену с одним спрайтом и обрабатывает сообщения
/// Содержимое можно скопировать в main()
int mainSnippet()
{
    /// устанавливаем пути к нужным папкам и файлам
    initFoldersAndPathes();

    /// Создаём сцену, (ширина, высота)
    GameScene gameScene(512,    512   );

    /// Здесь создаём добавляем в сцену спрайты, скрипты для них

    /// Игровой цикл: обрабатываем сообщения, проигрываем команды,
    /// пока окно не закроют
	while (gameScene.tick());

    /// Возвращаем код ошибки 0
	return 0;
}
