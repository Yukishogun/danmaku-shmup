#include "CollisionManager.h"

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::addEntity(EntityPtr entity)
{
    entities.push_back(entity);
}

void CollisionManager::update()
{
    EntityPtr anEnt;
    EntityPtr anotherEnt;

    for (int i = 0; i < entities.size(); i++)
    {
        anEnt = entities.at(i);

        if (!anEnt->alive)
        {
            entities.erase(std::remove(entities.begin(), entities.end(), anEnt), entities.end());
            continue;
        }
        for (int j = 0; j < entities.size(); j++)
        {
            anotherEnt = entities.at(j);

            if (i != j && anEnt->collidesWith(anotherEnt))
            {
                anEnt->onCollision(anotherEnt);
                anotherEnt->onCollision(anEnt);
            }
        }
    }
}
