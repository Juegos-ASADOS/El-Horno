#include <BulletCollision/CollisionShapes/btBox2dShape.h>
#include <iostream>
#include "ElHornoBullet.h"

namespace El_Horno {
    void ElHornoBullet::init()
    {
        btBox2dShape b(btVector3(1, 1, 1));
        std::cout << "Bullet iniciado.\n";
    }
}
