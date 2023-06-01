#pragma once
#include "PhysicsObject.h"
class Grenade :
    public PhysicsObject
{
public:

    Grenade();

    void Update(sf::Time frameTime) override;

    void SetPlayerNum(int newPlayerNum);
    void SetFireVelocity(sf::Vector2f newVelocity);

    void HandleCollision(PhysicsObject& other) override;

    int GetPlayerNum();

private:

    void UpdateAcceleration() override;

    int playerNum;
};

