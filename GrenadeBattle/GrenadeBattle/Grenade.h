#pragma once
#include "PhysicsObject.h"
#include "Player.h"

class Grenade :
    public PhysicsObject
{
public:

    Grenade(int newPlayerNum);

    void Update(sf::Time frameTime) override;

    void SetPlayerNum(int newPlayerNum);
    void SetFireVelocity(sf::Vector2f newVelocity);

    void HandleCollision(PhysicsObject& other) override;

    int GetPlayerNum();
    bool GetAlive();

private:

    void UpdateAcceleration() override;

    int playerNum;
    bool alive;

    float spawnLife;
    sf::Clock spawnLifeClock;
};

