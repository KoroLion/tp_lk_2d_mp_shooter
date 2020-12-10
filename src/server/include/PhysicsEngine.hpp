#ifndef TP_LK_2D_MP_SHOOTER_PHYSICSENGINE_H
#define TP_LK_2D_MP_SHOOTER_PHYSICSENGINE_H

#include "GameObject.hpp"

bool testAABBOverlap(std::shared_ptr<GameObject> a, std::shared_ptr<GameObject> b) {
    if(a->maxCoord().x < b->minCoord().x || a->minCoord().x > b->maxCoord().x)
        return false;
    if(a->maxCoord().y < b->minCoord().y || a->minCoord().y > b->maxCoord().y)
        return false;

    return true;
}


bool testCircleOverlap(std::shared_ptr<GameObject> a, std::shared_ptr<GameObject> b) {
    float r = a.getRadius() + b.getRadius();
    r *= r;
    return r < pow(a->getCoordinates().x + b->getCoordinates().x, 2) + pow(a->getCoordinates().y + b->getCoordinates().y, 2);
}

void move(std::shared_ptr<GameObject> obj) {
    auto time = std::chrono::steady_clock::now();
    auto delta = obj->speed() * (time - obj->getTime());
    //
}

#endif //TP_LK_2D_MP_SHOOTER_PHYSICSENGINE_H
