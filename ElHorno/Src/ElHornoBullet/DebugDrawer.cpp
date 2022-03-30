#include "DebugDrawer.h"
#include "HornoConversions.h"
#include <OgreManualObject.h>
#include <OgreSceneManager.h>
#include <OgreMaterial.h>
#include <OgreMaterialManager.h>
#include <OgreRoot.h>
#include <OgreLogManager.h>
#include <OgreTextureUnitState.h>
#include <GraphicsManager.h>
#include <OgreTimer.h>
#include <OgreTechnique.h>

using namespace Ogre;

namespace El_Horno {

    OgreDebugDrawer::OgreDebugDrawer(SceneManager* scm)
    {
        mContactPoints = &mContactPoints1;
        mLines = new ManualObject("physics lines");
        assert(mLines);
        mTriangles = new ManualObject("physics triangles");
        assert(mTriangles);
        mLines->setDynamic(true);
        mTriangles->setDynamic(true);
        //mLines->estimateVertexCount( 100000 );
        //mLines->estimateIndexCount( 0 );

        scm->getRootSceneNode()->attachObject(mLines);
        scm->getRootSceneNode()->attachObject(mTriangles);

        static const char* matName = "OgreBulletCollisionsDebugDefault";
        MaterialPtr mtl = MaterialManager::getSingleton().getDefaultSettings()->clone(matName);
        mtl->setReceiveShadows(false);
        mtl->setSceneBlending(SBT_TRANSPARENT_ALPHA);
        mtl->setDepthBias(0.1, 0);
        TextureUnitState* tu = mtl->getTechnique(0)->getPass(0)->createTextureUnitState();
        assert(tu);
        tu->setColourOperationEx(LBX_SOURCE1, LBS_DIFFUSE);
        mtl->getTechnique(0)->setLightingEnabled(false);
        //mtl->getTechnique(0)->setSelfIllumination( ColourValue::White ); 

        mLines->begin(matName, RenderOperation::OT_LINE_LIST);
        mLines->position(Vector3::ZERO);
        mLines->colour(ColourValue::Blue);
        mLines->position(Vector3::ZERO);
        mLines->colour(ColourValue::Blue);

        mTriangles->begin(matName, RenderOperation::OT_TRIANGLE_LIST);
        mTriangles->position(Vector3::ZERO);
        mTriangles->colour(ColourValue::Blue);
        mTriangles->position(Vector3::ZERO);
        mTriangles->colour(ColourValue::Blue);
        mTriangles->position(Vector3::ZERO);
        mTriangles->colour(ColourValue::Blue);

        mDebugModes = (DebugDrawModes)DBG_DrawWireframe;
        GraphicsManager::getInstance()->getRoot()->getSingleton().addFrameListener(this);
    }

    OgreDebugDrawer::~OgreDebugDrawer()
    {
        GraphicsManager::getInstance()->getRoot()->getSingleton().removeFrameListener(this);
        delete mLines;
        delete mTriangles;
    }

    void OgreDebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
    {
        ColourValue c(color.getX(), color.getY(), color.getZ());
        c.saturate();
        mLines->position(VectorToOgre(from));
        mLines->colour(c);
        mLines->position(VectorToOgre(to));
        mLines->colour(c);
    }

    void OgreDebugDrawer::drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color, btScalar alpha)
    {
        ColourValue c(color.getX(), color.getY(), color.getZ(), alpha);
        c.saturate();
        mTriangles->position(VectorToOgre(v0));
        mTriangles->colour(c);
        mTriangles->position(VectorToOgre(v1));
        mTriangles->colour(c);
        mTriangles->position(VectorToOgre(v2));
        mTriangles->colour(c);
    }

    void OgreDebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
    {
        mContactPoints->resize(mContactPoints->size() + 1);
        ContactPoint p = mContactPoints->back();
        p.from = VectorToOgre(PointOnB);
        p.to = p.from + VectorToOgre(normalOnB) * distance;
        p.dieTime = GraphicsManager::getInstance()->getRoot()->getSingleton().getTimer()->getMilliseconds() + lifeTime;
        p.color.r = color.x();
        p.color.g = color.y();
        p.color.b = color.z();
    }

    bool OgreDebugDrawer::frameStarted(const Ogre::FrameEvent& evt)
    {
        size_t now = GraphicsManager::getInstance()->getRoot()->getSingleton().getTimer()->getMilliseconds();
        std::vector< ContactPoint >* newCP = mContactPoints == &mContactPoints1 ? &mContactPoints2 : &mContactPoints1;
        for (std::vector< ContactPoint >::iterator i = mContactPoints->begin(); i < mContactPoints->end(); i++) {
            ContactPoint& cp = *i;
            mLines->position(cp.from);
            mLines->colour(cp.color);
            mLines->position(cp.to);
            if (now <= cp.dieTime)
                newCP->push_back(cp);
        }
        mContactPoints->clear();
        mContactPoints = newCP;

        mLines->end();
        mTriangles->end();

        return true;
    }

    bool OgreDebugDrawer::frameEnded(const Ogre::FrameEvent& evt)
    {
        mLines->beginUpdate(0);
        mTriangles->beginUpdate(0);
        return true;
    }

    void OgreDebugDrawer::reportErrorWarning(const char* warningString)
    {
        LogManager::getSingleton().getDefaultLog()->logMessage(warningString);
    }

    void OgreDebugDrawer::draw3dText(const btVector3& location, const char* textString)
    {

    }

    void OgreDebugDrawer::setDebugMode(int debugMode)
    {
        mDebugModes = (DebugDrawModes)debugMode;
    }

    int OgreDebugDrawer::getDebugMode() const
    {
        return mDebugModes;
    }
}