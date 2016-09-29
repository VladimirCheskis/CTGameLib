#pragma once
//#include "GameSprite.h"

struct GameMessage
{
    string            message;
    bool              toAllSprites = false;
    GameSpriteWeakPtr from;
    GameSpriteWeakPtr to;
};

struct MessageCompare
{
    bool operator()(const GameMessage& a, const GameMessage& b);
};

class GameMessageStorage
{
public:

    /// выдавать будем сообщения, полученные на прошлом тике.
    void tick();


    /// добавляет сообщение, находиться оно будет на следующем тике
    void addMessage(const GameMessage& msg);

    bool empty() const;

    bool hasMessages(const GameSpritePtr& to, const string& messageString) const;

    /// \return vector of from
    vector<GameSpritePtr> getMessages(const GameSpritePtr& to, const string& messageString) const;

public:
    vector<GameMessage> m_added;
    vector<GameMessage> m_received;
};


