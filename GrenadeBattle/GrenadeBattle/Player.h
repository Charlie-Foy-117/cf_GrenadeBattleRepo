#pragma once
#include "PhysicsObject.h"

class LevelScreen;

class Player:
    public PhysicsObject
{
public:

    Player(LevelScreen* newLevelscreen, int playerNum);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;
    void HandleCollision(PhysicsObject& other) override;

    void LoseLife();
    int GetLives();
    bool GetAlive();
    int GetCurrentPlayer();

private:

    void UpdateAcceleration() override;

    sf::Vector2f GetPipPosition(float pipTime, sf::Vector2f gravity, sf::Vector2f startVelocity, sf::Vector2f startPosition);
    void UpdatePipAngle();
    void SetGrenadeVelocity(float xVel, float yVel);

    std::vector<sf::Sprite> pips;
    sf::Vector2f grenadeVelocity;

    float controllerDeadzone;

    LevelScreen* levelScreen;

    sf::Clock cooldownClock;
    float cooldown;

    sf::Clock onGroundTimer;
    float onGroundCooldown;

    int currentPlayer;
    int lives;
    bool alive;
};


