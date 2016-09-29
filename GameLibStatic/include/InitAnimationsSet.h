#pragma once

#include "Common.h"
#include "GameSprite.h"


/// Создаёт спрайт Демон
GameSpritePtr createSpriteDemon(int x, int y);

/// Создаёт спрайт Волшебник
GameSpritePtr createSpriteWizard(int x, int y);

/// Подвешивает анимации на клавиши 1, 2, ...
void initTestAnimationsOnKeysActions(const GameSpritePtr& sprite);
