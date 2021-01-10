#pragma once
#include "Entity.h"
#include <cmath>
#include <functional>
#include <random>
#include "Projectile.h"
#include "CollisionManager.h"
#include "Character.h"

class Enemy
: public Character
{
public:
    explicit Enemy(TextureManager textureManager, std::shared_ptr<CollisionManager> collisionManager, std::vector<std::shared_ptr<Entity>>* bullets, std::function<float(float)>& xTrajectory, std::function<float(float)>& yTrajectory, float initialX, float initialY, int score);
    ~Enemy();
    void update(float timeStep);
    void onCollision(EntityPtr otherEntity);
    void onPlayerProjCollision(Projectile &otherEntity);
    int getScore();

private:
    std::function<float(float)>& xTrajectory;
    std::function<float(float)>& yTrajectory;
    float time = 0;
    float initialX;
    float initialY;
    bool seedSet = false;
    int score;

    int randGen();
};