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

    /// Игровой цикл: обрабатываем сообщения, проигрываем команды,
    /// пока окно не закроют
	while (gameScene.tick());

	return 0;
}
