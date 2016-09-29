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
    /// óñòàíàâëèâàåì ïóòè ê íóæíûì ïàïêàì è ôàéëàì
    initFoldersAndPathes();

    auto test = createAnimatorFromFiles(DemonPNG + "Attack__", false);

    /// Ñîçäà¸ì ñöåíó, (øèðèíà, âûñîòà)
    /// Create a game scene
    GameScene gameScene(712,    512   );

    /// Ñîçäà¸ò è äîáàâëÿåò â ñöåíó ñïðàéòû, ñîçäàü äëÿ íèõ ñêðèïòû

    /// Создаём спрайт демона и добавляем его в сцену. 100, 120 - координаты
    auto demon = createSpriteDemon(100, 120);
    gameScene.addObject(demon);

    /// Èãðîâîé öèêë: îáðàáàòûâàåì ñîîáùåíèÿ, ïðîèãðûâàåì êîìàíäû,
    /// ïîêà îêíî íå çàêðîþò
	while (gameScene.tick());

	return 0;
}
