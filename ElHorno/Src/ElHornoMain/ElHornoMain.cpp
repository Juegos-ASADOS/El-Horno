// ElHornoMain.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <OgreRoot.h>
#include "ElHornoMain.h"
#include "ElHornoBullet.h"

void ElHornoMain::init()
{
    Ogre::Root* root;
    root = new Ogre::Root();
    ElHornoBullet::bullet();
}