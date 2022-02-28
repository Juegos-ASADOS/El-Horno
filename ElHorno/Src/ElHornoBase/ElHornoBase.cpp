// ElHornoMain.cpp

#include <iostream>
#include <OgreRoot.h>
#include "ElHornoBase.h"
#include "ElHornoBullet.h"

void ElHornoBase::init()
{
    Ogre::Root* root;
    root = new Ogre::Root();
    ElHornoBullet::bullet();
}