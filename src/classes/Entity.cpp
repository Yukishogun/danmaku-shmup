#include "Entity.h"

Entity::Entity()
    : hitbox(0, 0), currAnimation(nullptr), alive(true), hp(1), sizeDefined(false)
{
}

Entity::Entity(std::string path)
        : hitbox(0, 0), path(path), currAnimation(nullptr), alive(true), hp(1), sizeDefined(false)
{
}

Entity::Entity(std::string path, int hp)
: hitbox(0, 0), path(path), currAnimation(nullptr), alive(true), hp(hp), sizeDefined(false)
{

}

Entity::Entity(std::string path, int hp, int width, int height) :
    hitbox(width, height), path(path), currAnimation(nullptr), alive(true), hp(hp), sizeDefined(true)
{

}

Entity::~Entity()
{}

/**
 * Move to (x, y)
 * @param x x-coord
 * @param y y-coord
 * @return true if moved, false otherwise.
 */
bool Entity::moveTo(float x, float y) {
    hitbox.moveTo(x, y);
    return true;
}

/**
 * Move dx on x-axis, dy on y-axis
 * @param dx Difference in x-coord
 * @param dy Difference in y-coord
 * @return true if moved, false otherwise.
 */
bool Entity::moveBy(float dx, float dy) {
    hitbox.moveBy(dx, dy);

    return true;
}

void Entity::render(SDL_Renderer* renderer) {
    if (currAnimation != nullptr)
    {
        currAnimation->render(renderer, hitbox.getX(), hitbox.getY());
    }
    else
    {
        texture->render(renderer, hitbox.getX(), hitbox.getY(), NULL);
    }
}

bool Entity::collidesWith(EntityPtr otherEntity) {
    return hitbox.collidesWith(otherEntity->hitbox);
}

void Entity::update(float timeStep)
{
    if (currAnimation != nullptr)
    {
        currAnimation->update(timeStep);
    }
}

void Entity::initTexture(TextureManager& textureManager)
{
    texture = textureManager.loadImage(path);

    if (!sizeDefined)
    {
        hitbox.setSize(texture->getWidth(), texture->getHeight());
    }
}

void Entity::playAnimation(std::string name) {
    currAnimation = animationMap.at(name);
}

void Entity::addAnimation(std::string name, AnimationPtr animation) {
    animationMap.insert(std::pair<std::string, AnimationPtr>(name, animation));
}

void Entity::changeHP(int howMuch) {
    hp += howMuch;

    if (hp <= 0)
    {
        alive = false;
    }
}

void Entity::onCollision(EntityPtr otherEntity)
{
}

void Entity::onPlayerCollision(Player &otherEntity)
{
}

void Entity::onPlayerProjCollision(Projectile &otherEntity)
{
}

void Entity::onEnemyCollision(Enemy &otherEntity)
{
}

void Entity::onEnemyProjCollision(Projectile &otherEntity)
{
}

int Entity::getScore() {
    return 0;
}


