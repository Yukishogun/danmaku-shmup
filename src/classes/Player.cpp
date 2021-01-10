#include "Player.h"
#include "../lists/KeyAction.h"

Player::Player(TextureManager textureManager, std::shared_ptr<CollisionManager> collisionManager, std::vector<std::shared_ptr<Entity>>* bullets, PlayerControlScheme controlScheme)
: Character(textureManager, collisionManager, bullets, "assets/flan.png", 3), controlScheme(controlScheme), hurtTimer()
{
    initTexture(textureManager);
    shootTimer.timeInterval = 500;
    hurtTimer.timeInterval = 1000;
    speed = 1000;
}

Player::~Player()
{
}

void Player::update(float timeStep) {
    Character::update(timeStep);

    hurtTimer.update(timeStep);

    float incr = timeStep * speed;

    if (controlScheme == arrow || controlScheme == arrowUD || controlScheme == arrowLR)
    {
        if (keysDown[ACTION_MOVE_LEFT] && controlScheme != arrowUD && hitbox.getX() > 0) {
            moveBy(-incr, 0);
        }

        if (keysDown[ACTION_MOVE_UP] && controlScheme != arrowLR) {
            moveBy(0, -incr);
        }

        if (keysDown[ACTION_MOVE_RIGHT] && controlScheme != arrowUD && hitbox.getX() < 1280 - hitbox.getWidth()) {
            moveBy(incr, 0);
        }

        if (keysDown[ACTION_MOVE_DOWN] && controlScheme != arrowLR) {
            moveBy(0, incr);
        }
    }

    else if (controlScheme == WASD || controlScheme == WASDUD)
    {
        if (keysDown[WASD_ACTION_MOVE_LEFT] && controlScheme == WASD) {
            moveBy(-incr, 0);
        }

        if (keysDown[WASD_ACTION_MOVE_UP]) {
            moveBy(0, -incr);
        }

        if (keysDown[WASD_ACTION_MOVE_RIGHT] && controlScheme == WASD) {
            moveBy(incr, 0);
        }

        if (keysDown[WASD_ACTION_MOVE_DOWN]) {
            moveBy(0, incr);
        }
    }

    if (keysDown[SDL_SCANCODE_Z]) {
        shoot(true);
    }
}

void Player::onCollision(EntityPtr otherEntity)
{
    otherEntity->onPlayerCollision(*this);
}

void Player::onEnemyProjCollision(Projectile &otherEntity)
{
    if (!otherEntity.allied) {
        hurt(1);
        moveTo(600, 800);
    }
}

void Player::onEnemyCollision(Enemy &otherEntity)
{
    hurt(1);
    moveTo(600, 800);
}

void Player::hurt(int howMuch) {
    if (hurtTimer.hasPassedDeadline())
    {
        hurtTimer.repeat();
        changeHP(-howMuch);
    }
}
