#include "HornoConversions.h"

#include "OgreVector3.h"
#include "btBulletCollisionCommon.h"

#include "fmod_common.h"
#include "CheckML.h"

btVector3 VectorToBullet(const Ogre::Vector3& v)
{
	return btVector3(v.x, v.y, v.z);
}

Ogre::Vector3 VectorToOgre(const btVector3& v)
{
	return Ogre::Vector3(v.x(), v.y(), v.z());
}

FMOD_VECTOR vectorToFmod(const Ogre::Vector3& vPosition)
{
	FMOD_VECTOR fVec;
	fVec.x = vPosition.x;
	fVec.y = vPosition.y;
	fVec.z = vPosition.z;
	return fVec;
}

btQuaternion QuaternionToBullet(const Ogre::Quaternion& q)
{
	return btQuaternion(q.x, q.y, q.z, q.w);
}

Ogre::Quaternion QuaternionToOgre(const btQuaternion& q)
{
	return Ogre::Quaternion(q.w(), q.x(), q.y(), q.z());
}
