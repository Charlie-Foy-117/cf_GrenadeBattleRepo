#pragma once
#include "Screen.h"
#include "Player.h"
#include "Platform.h"
#include "Grenade.h"

class LevelScreen :
    public Screen
{
public:

    LevelScreen(Game* newGamePointer);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

    void FireGrenade(sf::Vector2f position, sf::Vector2f fireVelocity, int playerNum);

private:

    void Restart();

    bool LoadLevel(int levelNumber);
    bool LoadLevel(std::string fileName);

    std::vector<Player*> players;

    bool gameRunning;
    int currentLevel;

    std::vector<Platform*> platforms;
    std::vector<Grenade*> grenades;
};

