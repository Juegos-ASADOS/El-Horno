#pragma once

//Bullet
class btVector3;
class btQuaternion;

//FMOD
class FMOD_VECTOR;

//Ogre
namespace Ogre {
	typedef float Real;
	template <int dims, typename T> class Vector;
	typedef Vector<2, Real> Vector2;
	typedef Vector<3, Real> Vector3;
	class Quaternion;
};

btVector3 VectorToBullet(const Ogre::Vector3& v);
Ogre::Vector3 VectorToOgre(const btVector3& v);
FMOD_VECTOR vectorToFmod(const Ogre::Vector3& vPosition);

btQuaternion QuaternionToBullet(const Ogre::Quaternion& q);
Ogre::Quaternion QuaternionToOgre(const btQuaternion& q);
