#include "AudioManager.h"
//
#include "fmod_studio.hpp"
#include "fmod.hpp"
#include "fmod.h"
#include <filesystem>


#include <iostream>
#include <vector>
#include "CheckML.h"


using namespace FMOD;
namespace El_Horno {
	AudioManager* AudioManager::instance_;
	Implementation* AudioManager::sgpImplementation;

	Implementation::Implementation()
	{
		mpStudioSystem = nullptr;
		AudioManager::ErrorCheck(FMOD::Studio::System::create(&mpStudioSystem));
		AudioManager::ErrorCheck(mpStudioSystem->initialize(32, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, NULL));

		mpSystem = NULL;
		AudioManager::ErrorCheck(mpStudioSystem->getCoreSystem(&mpSystem));
	}

	Implementation::~Implementation()
	{
		AudioManager::ErrorCheck(mpStudioSystem->unloadAll());
		AudioManager::ErrorCheck(mpStudioSystem->release());
	}

	void Implementation::Update()
	{
		std::vector<ChannelMap::iterator> pStoppedChannels;
		for (auto it = mChannels.begin(), itEnd = mChannels.end(); it != itEnd; ++it)
		{
			bool bIsPlaying = false;
			it->second->isPlaying(&bIsPlaying);
			if (!bIsPlaying)
			{
				pStoppedChannels.push_back(it);
			}
		}
		for (auto& it : pStoppedChannels)
		{
			mChannels.erase(it);
		}
		AudioManager::ErrorCheck(mpStudioSystem->update());
	}

	void AudioManager::init()
	{
		//// Inicialización de FMOD core
		//FMOD_RESULT result;
		//FMOD::System* system = nullptr;

		//result = FMOD::System_Create(&system);      // Create the main system object.
		//if (result != FMOD_OK)
		//{
		//	printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		//	return;
		//}

		//result = system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
		//if (result != FMOD_OK)
		//{
		//	printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		//	return;
		//}
		//std::cout << "FMOD inciado.\n";

		sgpImplementation = new Implementation();
	}

	void AudioManager::update()
	{
		sgpImplementation->Update();
	}

	void AudioManager::erase()
	{
		delete sgpImplementation;
		delete instance_;
	}

	int AudioManager::ErrorCheck(FMOD_RESULT result)
	{
		if (result != FMOD_OK) {
			std::cout << "FMOD ERROR " << result << std::endl;
			return 1;
		}
		// cout << "FMOD all good" << endl;
		return 0;
	}

	bool AudioManager::setupInstance()
	{
		if (instance_ == nullptr) {
			instance_ = new AudioManager();
			return true;
		}
		return false;
	}

	AudioManager* AudioManager::getInstance()
	{
		return instance_;
	}

	//void ElHornoFMOD::LoadBank(const std::string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags)
	//{
	//	auto tFoundIt = sgpImplementation->mBanks.find(strBankName);
	//	if (tFoundIt != sgpImplementation->mBanks.end())
	//		return;
	//	FMOD::Studio::Bank* pBank;
	//	ErrorCheck(sgpImplementation->mpStudioSystem->loadBankFile(strBankName.c_str(), flags, &pBank));
	//	if (pBank) {
	//		sgpImplementation->mBanks[strBankName] = pBank;
	//	}
	//}

	void AudioManager::Loadsound(const std::string& strSoundName, bool b3d, bool bLooping, bool bStream, bool isMusic)
	{
		auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
		if (tFoundIt != sgpImplementation->mSounds.end())
			return;

		FMOD_MODE eMode = FMOD_DEFAULT;
		eMode |= b3d ? FMOD_3D : FMOD_2D;
		eMode |= bLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
		eMode |= bStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;

		//std::string tmp = ;
		FMOD::Sound* pSound = nullptr;
		std::string path = ROUTENAME + strSoundName;
		ErrorCheck(sgpImplementation->mpSystem->createSound(path.c_str(), eMode, nullptr, &pSound));
		if (pSound) {
			sgpImplementation->mSounds[strSoundName] = pSound;
			if (isMusic)
				pSound->setSoundGroup(music);
			else
				pSound->setSoundGroup(fx);
		}
	}

	void AudioManager::UnLoadSound(const std::string& strSoundName)
	{
		auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
		if (tFoundIt == sgpImplementation->mSounds.end())
			return;

		ErrorCheck(tFoundIt->second->release());
		sgpImplementation->mSounds.erase(tFoundIt);
	}

	int AudioManager::playSound(const std::string& strSoundName, const FMOD_VECTOR& vPosition, float fVolumedB, bool isMusic)
	{
		int nChannelId = sgpImplementation->mnNextChannelId++;
		auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
		if (tFoundIt == sgpImplementation->mSounds.end())
		{
			Loadsound(strSoundName, isMusic);
			tFoundIt = sgpImplementation->mSounds.find(strSoundName);
			if (tFoundIt == sgpImplementation->mSounds.end())
			{
				return nChannelId;
			}
		}
		FMOD::Channel* pChannel = nullptr;
		ErrorCheck(sgpImplementation->mpSystem->playSound(tFoundIt->second, nullptr, true, &pChannel));
		if (pChannel)
		{
			FMOD_MODE currMode;
			tFoundIt->second->getMode(&currMode);
			if (currMode & FMOD_3D) {
				ErrorCheck(pChannel->set3DAttributes(&vPosition, nullptr));
			}
			ErrorCheck(pChannel->setVolume(dbToVolume(fVolumedB)));
			ErrorCheck(pChannel->setPaused(false));
			sgpImplementation->mChannels[nChannelId] = pChannel;
		}
		return nChannelId;
	}

	void AudioManager::StopChannel(int nChannelId)
	{
		sgpImplementation->mChannels[nChannelId]->stop();
	}

	void AudioManager::StopAllChannels()
	{
		for (int i = 0; i < sgpImplementation->mChannels.size(); ++i) {
			sgpImplementation->mChannels[i]->stop();
		}
	}

	void AudioManager::SetChannel3dPosition(int nChannelId, const FMOD_VECTOR& vPosition)
	{
		auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
		if (tFoundIt == sgpImplementation->mChannels.end())
			return;

		ErrorCheck(tFoundIt->second->set3DAttributes(&vPosition, NULL));
	}

	void AudioManager::SetChannelvolume(int nChannelId, float fVolumedB)
	{
		auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
		if (tFoundIt == sgpImplementation->mChannels.end())
			return;

		ErrorCheck(tFoundIt->second->setVolume(dbToVolume(fVolumedB)));
	}

	/*void AudioManager::upMusicVolume()
	{
		musicVolume += changeQuantity;
		music->setVolume();
	}

	void AudioManager::downMusicVolume()
	{
		musicVolume -= changeQuantity;
		music->setVolume();
	}

	void AudioManager::upFxVolume()
	{
		fxVolume += changeQuantity;
		fx->setVolume();
	}

	void AudioManager::downFxVolume()
	{
		fxVolume -= changeQuantity;
		fx->setVolume();
	}*/

	bool AudioManager::IsPlaying(int nChannelId) const
	{
		bool aux = false;
		sgpImplementation->mChannels[nChannelId]->isPlaying(&aux);
		if (aux)
			return true;
		else
			return false;
	}

	float AudioManager::dbToVolume(float db)
	{
		return powf(10.0f, 0.05f * db);
	}

	float AudioManager::VolumeTodb(float volume)
	{
		return 20.0f * log10f(volume);
	}




	void AudioManager::updateListener(int Listener, const FMOD_VECTOR& position, const FMOD_VECTOR& velocity, const FMOD_VECTOR& forward, const FMOD_VECTOR& up)
	{
		sgpImplementation->mpSystem->set3DListenerAttributes(Listener, &position, &velocity, &forward, &up);
	}


	void AudioManager::updateSound(const FMOD_VECTOR& position, const FMOD_VECTOR& velocity, int channel)
	{
		sgpImplementation->mChannels[channel]->set3DAttributes(&position, &velocity);
	}
}