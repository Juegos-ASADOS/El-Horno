//#include "ElHornoFMOD.h"
////
//#include "fmod_studio.hpp"
//#include "fmod.hpp"
//#include "fmod.h"
//
////#include "fmod_errors.h"
//#include <iostream>
//#include <vector>
////#include <math.h>
//
//
//using namespace FMOD;
//
//Implementation::Implementation()
//{
//	mpStudioSystem = nullptr;
//	ElHornoFMOD::ErrorCheck(FMOD::Studio::System::create(&mpStudioSystem));
//	ElHornoFMOD::ErrorCheck(mpStudioSystem->initialize(32, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, NULL));
//
//	mpSystem = NULL;
//	ElHornoFMOD::ErrorCheck(mpStudioSystem->getCoreSystem(&mpSystem));
//}
//
//Implementation::~Implementation()
//{
//	ElHornoFMOD::ErrorCheck(mpStudioSystem->unloadAll());
//	ElHornoFMOD::ErrorCheck(mpStudioSystem->release());
//}
//
//void Implementation::Update()
//{
//	std::vector<ChannelMap::iterator> pStoppedChannels;
//	for (auto it = mChannels.begin(), itEnd = mChannels.end(); it != itEnd; ++it)
//	{
//		bool bIsPlaying = false;
//		it->second->isPlaying(&bIsPlaying);
//		if (!bIsPlaying)
//		{
//			pStoppedChannels.push_back(it);
//		}
//	}
//	for (auto& it : pStoppedChannels)
//	{
//		mChannels.erase(it);
//	}
//	ElHornoFMOD::ErrorCheck(mpStudioSystem->update());
//}
//
//void ElHornoFMOD::init()
//{
//	//// Inicialización de FMOD core
//	//FMOD_RESULT result;
//	//FMOD::System* system = nullptr;
//
//	//result = FMOD::System_Create(&system);      // Create the main system object.
//	//if (result != FMOD_OK)
//	//{
//	//	printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
//	//	return;
//	//}
//
//	//result = system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
//	//if (result != FMOD_OK)
//	//{
//	//	printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
//	//	return;
//	//}
//	//std::cout << "FMOD inciado.\n";
//
//	sgpImplementation = new Implementation();
//}
//
//void ElHornoFMOD::Update()
//{
//	sgpImplementation->Update();
//}
//
//void ElHornoFMOD::Shutdown()
//{
//	delete sgpImplementation;
//}
//
//int ElHornoFMOD::ErrorCheck(FMOD_RESULT result)
//{
//	if (result != FMOD_OK) {
//		std::cout << "FMOD ERROR " << result << std::endl;
//		return 1;
//	}
//	// cout << "FMOD all good" << endl;
//	return 0;
//}
//
////void ElHornoFMOD::LoadBank(const std::string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags)
////{
////	auto tFoundIt = sgpImplementation->mBanks.find(strBankName);
////	if (tFoundIt != sgpImplementation->mBanks.end())
////		return;
////	FMOD::Studio::Bank* pBank;
////	ErrorCheck(sgpImplementation->mpStudioSystem->loadBankFile(strBankName.c_str(), flags, &pBank));
////	if (pBank) {
////		sgpImplementation->mBanks[strBankName] = pBank;
////	}
////}
//
//void ElHornoFMOD::Loadsound(const std::string& strSoundName, bool b3d, bool bLooping, bool bStream)
//{
//	auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
//	if (tFoundIt != sgpImplementation->mSounds.end())
//		return;
//
//	FMOD_MODE eMode = FMOD_DEFAULT;
//	eMode |= b3d ? FMOD_3D : FMOD_2D;
//	eMode |= bLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
//	eMode |= bStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;
//
//	FMOD::Sound* pSound = nullptr;
//	ErrorCheck(sgpImplementation->mpSystem->createSound(strSoundName.c_str(), eMode, nullptr, &pSound));
//	if (pSound) {
//		sgpImplementation->mSounds[strSoundName] = pSound;
//	}
//}
//
//void ElHornoFMOD::UnLoadSound(const std::string& strSoundName)
//{
//	auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
//	if (tFoundIt == sgpImplementation->mSounds.end())
//		return;
//
//	ErrorCheck(tFoundIt->second->release());
//	sgpImplementation->mSounds.erase(tFoundIt);
//}
//
//int ElHornoFMOD::PlaySound(const std::string& strSoundName, const Vector3& vPosition, float fVolumedB)
//{
//	int nChannelId = sgpImplementation->mnNextChannelId++;
//	auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
//	if (tFoundIt == sgpImplementation->mSounds.end())
//	{
//		Loadsound(strSoundName);
//		tFoundIt = sgpImplementation->mSounds.find(strSoundName);
//		if (tFoundIt == sgpImplementation->mSounds.end())
//		{
//			return nChannelId;
//		}
//	}
//	FMOD::Channel* pChannel = nullptr;
//	ErrorCheck(sgpImplementation->mpSystem->playSound(tFoundIt->second, nullptr, true, &pChannel));
//	if (pChannel)
//	{
//		FMOD_MODE currMode;
//		tFoundIt->second->getMode(&currMode);
//		if (currMode & FMOD_3D) {
//			FMOD_VECTOR position = VectorToFmod(vPosition);
//			ErrorCheck(pChannel->set3DAttributes(&position, nullptr));
//		}
//		ErrorCheck(pChannel->setVolume(dbToVolume(fVolumedB)));
//		ErrorCheck(pChannel->setPaused(false));
//		sgpImplementation->mChannels[nChannelId] = pChannel;
//	}
//	return nChannelId;
//}
//
//void ElHornoFMOD::StopChannel(int nChannelId)
//{
//	sgpImplementation->mChannels[nChannelId]->stop();
//}
//
//void ElHornoFMOD::StopAllChannels()
//{
//	for (int i = 0; i < sgpImplementation->mChannels.size(); ++i) {
//		sgpImplementation->mChannels[i]->stop();
//	}
//}
//
//void ElHornoFMOD::SetChannel3dPosition(int nChannelId, const Vector3& vPosition)
//{
//	auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
//	if (tFoundIt == sgpImplementation->mChannels.end())
//		return;
//
//	FMOD_VECTOR position = VectorToFmod(vPosition);
//	ErrorCheck(tFoundIt->second->set3DAttributes(&position, NULL));
//}
//
//void ElHornoFMOD::SetChannelvolume(int nChannelId, float fVolumedB)
//{
//	auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
//	if (tFoundIt == sgpImplementation->mChannels.end())
//		return;
//
//	ErrorCheck(tFoundIt->second->setVolume(dbToVolume(fVolumedB)));
//}
//
//bool ElHornoFMOD::IsPlaying(int nChannelId) const
//{
//	bool aux = false;
//	sgpImplementation->mChannels[nChannelId]->isPlaying(&aux);
//	if (aux)
//		return true;
//	else
//		return false;
//}
//
//float ElHornoFMOD::dbToVolume(float db)
//{
//	return powf(10.0f, 0.05f * db);
//}
//
//float ElHornoFMOD::VolumeTodb(float volume)
//{
//	return 20.0f * log10f(volume);
//}
//
//FMOD_VECTOR ElHornoFMOD::VectorToFmod(const Vector3& vPosition)
//{
//	FMOD_VECTOR fVec;
//	fVec.x = vPosition.x;
//	fVec.y = vPosition.y;
//	fVec.z = vPosition.z;
//	return fVec;
//}
