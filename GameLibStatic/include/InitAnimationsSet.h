#pragma once

#include "Common.h"
#include "GameSprite.h"


/// ������ ������ �����
GameSpritePtr createSpriteDemon(int x, int y);

/// ������ ������ ���������
GameSpritePtr createSpriteWizard(int x, int y);

/// ����������� �������� �� ������� 1, 2, ...
void initTestAnimationsOnKeysActions(const GameSpritePtr& sprite);
