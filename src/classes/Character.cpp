#include "Character.h"

Character::Character (TextureManager textureManager, std::shared_ptr<CollisionManager> collisionManager, std::vector<std::shared_ptr<Entity>>* bullets, std::string path)
: Entity(path), textureManager(textureManager), collisionManager(collisionManager), bullets(bullets), shootTimer()
{
    shootTimer.timeInterval = 1000;
}

Character::Character (TextureManager textureManager, std::shared_ptr<CollisionManager> collisionManager, std::vector<std::shared_ptr<Entity>>* bullets, std::string path, int hp)
        : Entity(path, hp), textureManager(textureManager), collisionManager(collisionManager), bullets(bullets), shootTimer()
{
    shootTimer.timeInterval = 1000;
}

Character::Character(TextureManager textureManager, std::shared_ptr<CollisionManager> collisionManager,
                     std::vector<std::shared_ptr<Entity>> *bullets, std::string path, int hp, int width, int height)
: Entity(path, hp, width, height), textureManager(textureManager), collisionManager(collisionManager), bullets(bullets), shootTimer() {
    shootTimer.timeInterval = 1000;
}

void Character::shoot(bool allied)
{
    if (shootTimer.hasPassedDeadline())
    {
        shootTimer.repeat();
        Projectile bullet(textureManager, allied);
        bullet.moveTo(hitbox.getX() + hitbox.getWidth()/2, hitbox.getY() + hitbox.getHeight() / 2);

        EntityPtr bulletPtr = std::make_shared<Projectile>(bullet);

        bullets->push_back(bulletPtr);
        collisionManager->addEntity(bulletPtr);
    }
}

void Character::update(float timeStep) {
    Entity::update(timeStep);
    shootTimer.update(timeStep);
}
