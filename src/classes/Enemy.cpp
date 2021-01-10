#include "Enemy.h"

Enemy::Enemy(TextureManager textureManager, std::shared_ptr<CollisionManager> collisionManager, std::vector<std::shared_ptr<Entity>>* bullets, std::function<float(float)>& xTrajectory, std::function<float(float)>& yTrajectory, float initialX, float initialY, int score)
: Character(textureManager, collisionManager, bullets, "assets/invaderSprites.png", 1, 100, 70),
xTrajectory(xTrajectory), yTrajectory(yTrajectory), initialX(initialX), initialY(initialY), score(score)
{
    initTexture(textureManager);
    std::vector<SDL_Rect> rectVect = {
        SDL_Rect {0, 0, 100, 70},
        SDL_Rect {100, 0, 100, 70}
    };

    AnimationPtr theAnim = std::make_shared<Animation>(texture, rectVect, 1000);

    addAnimation("idle", theAnim);
    playAnimation("idle");
}

Enemy::~Enemy() {
}

void Enemy::update(float timeStep) {
    Character::update(timeStep);
    moveTo(xTrajectory(time) + initialX, yTrajectory(time) + initialY);
    time += timeStep;

    if (randGen() >= 9980)
        shoot(false);
}

void Enemy::onCollision(EntityPtr otherEntity)
{
    otherEntity->onEnemyCollision(*this);
}

void Enemy::onPlayerProjCollision(Projectile &otherEntity)
{
    if(otherEntity.allied)
        changeHP(-otherEntity.damage);
}

int Enemy::randGen() {
    return rand() % 10000;
}

int Enemy::getScore() {
    return 100;
}
