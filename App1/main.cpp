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

    /// Создаём сцену, (ширина, высота)
    GameScene gameScene(512,    512   );

    /// Здесь создаём добавляем в сцену спрайты, скрипты для них

    /// Игровой цикл: обрабатываем сообщения, проигрываем команды,
    /// пока окно не закроют
	while (gameScene.tick());

    /// Возвращаем код ошибки 0
	return 0;
}
