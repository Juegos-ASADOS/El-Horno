#include "HornoConversions.h"

#include "OgreVector3.h"
#include "btBulletCollisionCommon.h"
#include "HornoVector3.h"

#include "fmod_common.h"
#include "CheckML.h"

namespace El_Horno {
	btVector3 OgreVectorToBullet(const Ogre::Vector3& v)
	{
		return btVector3(v.x, v.y, v.z);
	}

	Ogre::Vector3 BulletVectorToOgre(const btVector3& v)
	{
		return Ogre::Vector3(v.x(), v.y(), v.z());
	}

	FMOD_VECTOR OgreVectorToFmod(const Ogre::Vector3& vPosition)
	{
		FMOD_VECTOR fVec;
		fVec.x = vPosition.x;
		fVec.y = vPosition.y;
		fVec.z = vPosition.z;
		return fVec;
	}

	btVector3 HornoVectorToBullet(const El_Horno::HornoVector3& v)
	{
		return btVector3(v.x_, v.y_, v.z_);
	}

	Ogre::Vector3 HornoVectorToOgre(const El_Horno::HornoVector3& v)
	{
		return Ogre::Vector3(v.x_, v.y_, v.z_);
	}

	FMOD_VECTOR HornoVectorToFmod(const El_Horno::HornoVector3& v)
	{
		FMOD_VECTOR fVec;
		fVec.x = v.x_;
		fVec.y = v.y_;
		fVec.z = v.z_;
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
}