#pragma once
#include <string>
#include "Texture.h"
#include "Hitbox.h"
#include "TextureManager.h"
#include "Animation.h"

class Player;
class Enemy;
class Projectile;

class Entity {
public:
    Entity();
    Entity(std::string path);
    Entity(std::string path, int hp);
    Entity(std::string path, int hp, int width, int height);
    ~Entity();

    TexturePtr texture;
    Hitbox hitbox;
    std::string path;
    int speed;
    AnimationPtr currAnimation;
    bool alive;
    int hp;
    bool sizeDefined;

    bool moveTo(float x, float y);
    bool moveBy(float dx, float dy);
    bool collidesWith(std::shared_ptr<Entity> otherEntity);
    void initTexture(TextureManager& textureManager);
    void changeHP(int howMuch);
    void playAnimation(std::string name);
    void addAnimation(std::string name, AnimationPtr animation);

    virtual int getScore();
    virtual void update(float timeStep);
    virtual void render(SDL_Renderer* renderer);
    virtual void onCollision(std::shared_ptr<Entity> otherEntity);
    virtual void onPlayerCollision(Player &otherEntity);
    virtual void onPlayerProjCollision(Projectile &otherEntity);
    virtual void onEnemyCollision(Enemy &otherEntity);
    virtual void onEnemyProjCollision(Projectile &otherEntity);


protected:
    std::map<std::string, AnimationPtr> animationMap;
};

typedef std::shared_ptr<Entity> EntityPtr;