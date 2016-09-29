#ifndef GAMETEXT_H
#define GAMETEXT_H

#include "GameObject.h"

class GameText : public GameObject
{
    public:
        GameText() = default;
        GameText(const string& text, int x, int y);

        virtual void draw(GameScene& scene) override;


        void setText(const string& text);
        void setPlace(int x, int y);
    protected:

    private:
        sf::Text m_text;
};
DEFINE_STD(GameText);

#endif // GAMETEXT_H

