#pragma once

//Bullet
class btVector3;
class btQuaternion;
#include <string>
//FMOD
class FMOD_VECTOR;

//Ogre
namespace Ogre {
	typedef float Real;
	template <int dims, typename T> class Vector;
	typedef Vector<2, Real> Vector2;
	typedef Vector<3, Real> Vector3;
	typedef Vector<4, Real> Vector4;
	class Quaternion;
};

namespace El_Horno {
	class HornoVector3;

	_declspec(dllexport) btVector3 OgreVectorToBullet(const Ogre::Vector3& v);
	_declspec(dllexport) Ogre::Vector3 BulletVectorToOgre(const btVector3& v);
	_declspec(dllexport) FMOD_VECTOR OgreVectorToFmod(const Ogre::Vector3& vPosition);

	_declspec(dllexport) btVector3 HornoVectorToBullet(const El_Horno::HornoVector3& v);
	_declspec(dllexport) Ogre::Vector3 HornoVectorToOgre(const El_Horno::HornoVector3& v);
	_declspec(dllexport) El_Horno::HornoVector3 OgreVectorToHorno(const Ogre::Vector3& v);
	_declspec(dllexport) El_Horno::HornoVector3 BulletVectorToHorno(const btVector3& v);
	_declspec(dllexport) FMOD_VECTOR HornoVectorToFmod(const El_Horno::HornoVector3& v);
	_declspec(dllexport) El_Horno::HornoVector3 StringToHorno(std::string vec);


	_declspec(dllexport) btQuaternion QuaternionToBullet(const Ogre::Quaternion& q);
	_declspec(dllexport) Ogre::Quaternion QuaternionToOgre(const btQuaternion& q);
	_declspec(dllexport) Ogre::Vector3 StringToVector(std::string vec);
	_declspec(dllexport) Ogre::Vector4 StringToColor(std::string vec);
}