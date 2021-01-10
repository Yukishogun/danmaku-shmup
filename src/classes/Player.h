#pragma once
#include "Character.h"
#include <string>
#include <vector>
#include "Projectile.h"

enum PlayerControlScheme { arrow, WASD, arrowUD, WASDUD, arrowLR };

class Player :
	public Character
{
public:
    Player(TextureManager textureManager, std::shared_ptr<CollisionManager> collisionManager, std::vector<EntityPtr>* bullets, 
        PlayerControlScheme controlScheme=arrow);
    ~Player();

    void update(float timeStep);
    void onCollision(EntityPtr otherEntity);
    void onEnemyProjCollision(Projectile &otherEntity);
    void onEnemyCollision(Enemy &otherEntity);
    void hurt(int howMuch);

    PlayerControlScheme controlScheme;

private:
    Timer hurtTimer;
};
