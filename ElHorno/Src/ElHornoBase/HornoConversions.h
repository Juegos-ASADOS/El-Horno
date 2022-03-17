#pragma once

//Bullet
class btVector3;
class btQuaternion;

//Ogre
namespace Ogre {
	typedef float Real;
	template <int dims, typename T> class Vector;
	typedef Vector<2, Real> Vector2;
	typedef Vector<3, Real> Vector3;
	class Quaternion;
};

static btVector3 VectorToBullet(const Ogre::Vector3& v);
static Ogre::Vector3 VectorToOgre(const btVector3& v);

static btQuaternion QuaternionToBullet(const Ogre::Quaternion& q);
static Ogre::Quaternion QuaternionToOgre(const btQuaternion& q);
