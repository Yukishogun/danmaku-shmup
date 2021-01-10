#include "EntityUpdater.h"

EntityUpdater::EntityUpdater()
{}

EntityUpdater::~EntityUpdater() {}

void EntityUpdater::update(float timeStep)
{
    for (int i = 0; i < entities.size(); i++)
    {
        if (!entities.at(i)->alive)
        {
            entities.erase(entities.begin() + i);
        }
    }
}

void EntityUpdater::add(Entity entity) {
    entities.push_back(std::make_shared<Entity>(entity));
}

