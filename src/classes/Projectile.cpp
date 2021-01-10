#include "Projectile.h"

Projectile::Projectile(TextureManager textureManager, bool allied)
: Entity("assets/ribbis.png"), speed(500), damage(1), allied(allied)
{
    if(!allied)
        Entity::path = "assets/anis.png";
    initTexture(textureManager);
    if (!allied)
        speed *= -1;
}

Projectile::~Projectile() {

}

void Projectile::update(float timeStep) {
    hitbox.moveBy(0, -speed*timeStep);
    moveBy(0, -speed*timeStep);
}

void Projectile::onCollision(EntityPtr otherEntity) {
    // TODO: separate player and enemy projectiles
    otherEntity->onPlayerProjCollision(*this);
    otherEntity->onEnemyProjCollision(*this);
}

void Projectile::onEnemyCollision(Enemy &otherEntity) {
    if (allied)
        alive = false;
}

void Projectile::onPlayerCollision(Player &otherEntity) {
    if (!allied)
        alive = false;
}
