#pragma once
#include "Entity.h"
#include "Projectile.h"
#include "CollisionManager.h"

class Character :
	public Entity
{
public:
    Character(std::string path);
    Character(TextureManager textureManager, std::shared_ptr<CollisionManager> collisionManager, std::vector<std::shared_ptr<Entity>>* bullets, std::string path);
    Character(TextureManager textureManager, std::shared_ptr<CollisionManager> collisionManager, std::vector<std::shared_ptr<Entity>>* bullets, std::string path, int hp);
	Character(TextureManager textureManager, std::shared_ptr<CollisionManager> collisionManager, std::vector<std::shared_ptr<Entity>>* bullets, std::string path, int hp, int width, int height);

    void update(float timeStep);
    void shoot(bool allied);

protected:
    Timer shootTimer;
    std::vector<std::shared_ptr<Entity>>* bullets;
    TextureManager textureManager;
    std::shared_ptr<CollisionManager> collisionManager;
};
