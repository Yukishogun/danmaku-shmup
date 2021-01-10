#pragma once
#include "TextureManager.h"
#include "Entity.h"

class Projectile
: public Entity {
public:
    explicit Projectile(TextureManager textureManager, bool allied);
    ~Projectile();

    void update(float timeStep);
    void onCollision(EntityPtr otherEntity);
    void onEnemyCollision(Enemy &otherEntity);
    void onPlayerCollision(Player& otherEntity);
    int damage;
    bool allied;

private:
    int speed;
};
