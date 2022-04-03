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

    //Comunica Bullet con Ogre para debugear la grafica de los rg
    OgreDebugDrawer::OgreDebugDrawer(SceneManager* scm)
    {
        mContactPoints_ = &mContactPoints1_;
        mLines_ = new ManualObject("physics lines");
        assert(mLines_);
        mTriangles_ = new ManualObject("physics triangles");
        assert(mTriangles_);
        mLines_->setDynamic(true);
        mTriangles_->setDynamic(true);
        //mLines_->estimateVertexCount( 100000 );
        //mLines_->estimateIndexCount( 0 );

        scm->getRootSceneNode()->attachObject(mLines_);
        scm->getRootSceneNode()->attachObject(mTriangles_);

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

        mLines_->begin(matName, RenderOperation::OT_LINE_LIST);
        mLines_->position(Vector3::ZERO);
        mLines_->colour(ColourValue::Blue);
        mLines_->position(Vector3::ZERO);
        mLines_->colour(ColourValue::Blue);

        mTriangles_->begin(matName, RenderOperation::OT_TRIANGLE_LIST);
        mTriangles_->position(Vector3::ZERO);
        mTriangles_->colour(ColourValue::Blue);
        mTriangles_->position(Vector3::ZERO);
        mTriangles_->colour(ColourValue::Blue);
        mTriangles_->position(Vector3::ZERO);
        mTriangles_->colour(ColourValue::Blue);

        mDebugModes_ = (DebugDrawModes)DBG_DrawWireframe;
        GraphicsManager::getInstance()->getRoot()->getSingleton().addFrameListener(this);
    }

    OgreDebugDrawer::~OgreDebugDrawer()
    {
        GraphicsManager::getInstance()->getRoot()->getSingleton().removeFrameListener(this);
        delete mLines_;
        delete mTriangles_;
    }

    void OgreDebugDrawer::drawLine(const btVector3& from_, const btVector3& to_, const btVector3& color_)
    {
        ColourValue c(color_.getX(), color_.getY(), color_.getZ());
        c.saturate();
        mLines_->position(VectorToOgre(from_));
        mLines_->colour(c);
        mLines_->position(VectorToOgre(to_));
        mLines_->colour(c);
    }

    void OgreDebugDrawer::drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color_, btScalar alpha)
    {
        ColourValue c(color_.getX(), color_.getY(), color_.getZ(), alpha);
        c.saturate();
        mTriangles_->position(VectorToOgre(v0));
        mTriangles_->colour(c);
        mTriangles_->position(VectorToOgre(v1));
        mTriangles_->colour(c);
        mTriangles_->position(VectorToOgre(v2));
        mTriangles_->colour(c);
    }

    void OgreDebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color_)
    {
        mContactPoints_->resize(mContactPoints_->size() + 1);
        ContactPoint p = mContactPoints_->back();
        p.from_ = VectorToOgre(PointOnB);
        p.to_ = p.from_ + VectorToOgre(normalOnB) * distance;
        p.dieTime_ = GraphicsManager::getInstance()->getRoot()->getSingleton().getTimer()->getMilliseconds() + lifeTime;
        p.color_.r = color_.x();
        p.color_.g = color_.y();
        p.color_.b = color_.z();
    }

    bool OgreDebugDrawer::frameStarted(const Ogre::FrameEvent& evt)
    {
        size_t now = GraphicsManager::getInstance()->getRoot()->getSingleton().getTimer()->getMilliseconds();
        std::vector< ContactPoint >* newCP = mContactPoints_ == &mContactPoints1_ ? &mContactPoints2_ : &mContactPoints1_;
        for (std::vector< ContactPoint >::iterator i = mContactPoints_->begin(); i < mContactPoints_->end(); i++) {
            ContactPoint& cp = *i;
            mLines_->position(cp.from_);
            mLines_->colour(cp.color_);
            mLines_->position(cp.to_);
            if (now <= cp.dieTime_)
                newCP->push_back(cp);
        }
        mContactPoints_->clear();
        mContactPoints_ = newCP;

        mLines_->end();
        mTriangles_->end();

        return true;
    }

    bool OgreDebugDrawer::frameEnded(const Ogre::FrameEvent& evt)
    {
        mLines_->beginUpdate(0);
        mTriangles_->beginUpdate(0);
        return true;
    }

    void OgreDebugDrawer::reportErrorWarning(const char* warningString)
    {
        LogManager::getSingleton().getDefaultLog()->logMessage(warningString);
    }

    void OgreDebugDrawer::setDebugMode(int debugMode)
    {
        mDebugModes_ = (DebugDrawModes)debugMode;
    }

    int OgreDebugDrawer::getDebugMode() const
    {
        return mDebugModes_;
    }
}