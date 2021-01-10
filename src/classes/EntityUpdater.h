#pragma once
#include "Entity.h"

class EntityUpdater {
public:
    EntityUpdater();
    ~EntityUpdater();

    void add(Entity entity);
    void update(float timeStep);

private:
    std::vector<std::shared_ptr<Entity>> entities;
};