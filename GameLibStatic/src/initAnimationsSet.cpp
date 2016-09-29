#include "InitAnimationsSet.h"
#include "GameLib.h"

/// Инициализирует анимации Демона
void initAnimationsSetDemon(const GameSpritePtr& sprite, const string& demonFolder)
{
    auto& animations = sprite->animationsSet();
	auto start = demonFolder + "SPRITE SHEET/FW_Demon_Lord_";

    animations.setSheet("Flame",   start + "Attack_Flame.png", 6, 5);
    animations.setSheet("Attack",  start + "Attack.png", 6, 5);
    animations.setSheet("Crouch",  start + "Crouching.png", 6, 2);
    animations.setSheet("Die",  start + "Die.png", 6, 6);
    animations.setSheet("Hit",  start + "Hit.png", 6, 3);
    animations.setSheet("Jump",  start + "Jumping.png", 6, 4);
    animations.setSheet("Run",  start + "Running.png", 6, 4);
    animations.setSheet("Walk",  start + "Walking.png", 6, 6);
}

/// Инициализирует анимации Волшебника
void initAnimationsSetWizard(const GameSpritePtr& sprite, const string& wizardFolder)
{
    auto& animations = sprite->animationsSet();
	auto start = wizardFolder + "SPRITE_SHEET/FW_Hero_1_";

    animations.setSheet("Attack",  start + "Attacking.png", 6, 2, 9);
    animations.setSheet("Crouch",  start + "Crouching.png", 6, 2, 11);
    animations.setSheet("Die",  start + "Die.png", 6, 3, 16);
    animations.setSheet("Hit",  start + "Hit.png", 6, 4);
    animations.setSheet("Jump",  start + "Jumping.png", 6, 3, 14);
    animations.setSheet("Run",  start + "Running.png", 6, 3, 16);
    animations.setSheet("Walk",  start + "Walking.png", 6, 4);
}

void initTestAnimationsOnKeysActions(const GameSpritePtr& sprite)
{
    auto names = sprite->animationsSet().getAnimationsNames();
    for (size_t i = 0; i < names.size(); ++i)
    {
        auto key = (sf::Keyboard::Key)(sf::Keyboard::Key::Num1 + i);
        auto keyAction = make_shared<OnKeyPressedAction>(key);
        keyAction->setIsRepeatable(true);
        keyAction->addAction(make_shared<SpriteActionAnimate>(sprite, names[i], EAnimationType::Die));
        keyAction->addAction(make_shared<MaintTextAction>(names[i]));
        sprite->addAction(keyAction);
    }
}

GameSpritePtr createSpriteDemon(int x, int y)
{
    auto demon = make_shared<GameSprite>(DemonPNG + "Crouching__000.png", x, y);
    initAnimationsSetDemon(demon, SpritesFolder + "FW_Demon_Lord/");
    return demon;
}

GameSpritePtr createSpriteWizard(int x, int y)
{
    auto wizard = make_shared<GameSprite>(WizardPNG + "Crouching__000.png", x, y);
    initAnimationsSetWizard(wizard, SpritesFolder + "Wizard/");
    return wizard;
}
