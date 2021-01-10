#pragma once

#include <vector>
#include "Entity.h"

class CollisionManager {
public:
    CollisionManager();
    ~CollisionManager();

    void addEntity(EntityPtr entity);
    void update();

private:
    std::vector<EntityPtr> entities;
};
