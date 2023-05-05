#pragma once
#include "Screen.h"
#include "Player.h"
#include "Platform.h"

class LevelScreen :
    public Screen
{
public:

    LevelScreen(Game* newGamePointer);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

private:

    void Restart();

    Player player;
    Platform platform;

    bool gameRunning;
};

