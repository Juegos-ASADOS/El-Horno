#include <BulletCollision/CollisionShapes/btBox2dShape.h>
#include <iostream>
#include "ElHornoBullet.h"

void ElHornoBullet::bullet()
{
    btBox2dShape b(btVector3(1, 1, 1));
    std::cout << "Bullet compilado." << "\n";
}
