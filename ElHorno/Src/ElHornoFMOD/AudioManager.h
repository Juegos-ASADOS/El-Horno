#pragma once
#ifndef _AUDIO_MANAGER_AUDIO_MANAGER_H
#define _AUDIO_MANAGER_AUDIO_MANAGER_H

#include <string>
#include <map>
#include "fmod_common.h"
#include "HornoVector3.h"
//struct FMOD_VECTOR;
//enum FMOD_RESULT;

#define ROUTENAME "Assets/Sounds/"

namespace FMOD {
	class ChannelGroup;
	class Channel;
	class System;
	class Sound;
	class SoundGroup;
	namespace Studio {
		class System;
		class Bank;
	}
}

namespace El_Horno {
	class _declspec(dllexport) Implementation {
	public:
		Implementation();
		~Implementation();

		void Update();

		FMOD::Studio::System* mpStudioSystem;
		FMOD::System* mpSystem;

		int mnNextChannelId = 0;

		typedef std::map<std::string, FMOD::Sound*> SoundMap;
		typedef std::map<int, FMOD::Channel*> ChannelMap;
		//typedef std::map<std::string, FMOD::Studio::EventInstance*> EventMap;

		//EventMap mEvents;
		SoundMap mSounds;
		ChannelMap mChannels;
	};

	class _declspec(dllexport) AudioManager
	{
	public:
		void init();
		void update();
		static void erase();
		static int ErrorCheck(FMOD_RESULT result);
		static bool setupInstance();
		static AudioManager* getInstance();

		//void LoadBank(const std::string& strBankName, FMOD::FMOD_STUDIO_LOAD_BANK_FLAGS flags);
		//void LoadEvent(const string& strEventName);
		void Loadsound(const std::string& strSoundName, bool b3d = true, bool bLooping = false, bool bStream = false, bool isMusic = false);
		void UnLoadSound(const std::string& strSoundName);
		//void Set3dListenerAndOrientation(const FMOD_VECTOR& vPos = { 0, 0, 0 }, float fVolumedB = 0.0f);
		int playSound(const std::string& strSoundName, const FMOD_VECTOR& vPos, float fVolumedB = 1.0f, bool isMusic = false);
		//void PlayEvent(const string& strEventName);
		void StopChannel(int nChannelId);
		//void StopEvent(const string& strEventName, bool bImmediate = false);
		//void GeteventParameter(const string& strEventName, const string% strEventParameter, float* parameter);
		//void SetEventParameter(const string& strEventName, const string& strParameterName, flaot fValue);
		void StopAllChannels();
		void pauseAllChannels();
		void resumeAllChannels();
		void SetChannel3dPosition(int nChannelId, const FMOD_VECTOR& vPosition);
		void SetChannel3dPosition(int nChannelId, const HornoVector3& vPosition);
		void SetChannelvolume(int nChannelId, float fVolumedB);
		void upMusicVolume();
		void downMusicVolume();
		void upFxVolume();
		void downFxVolume();
		bool IsPlaying(int nChannelId) const;
		//bool IsEventPlaying(const string& strEventName) const;
		float dbToVolume(float db);
		float VolumeTodb(float volume);

		//int ErrorCheck(FMOD_RESULT result);

		void updateListener(int Listener, const FMOD_VECTOR& position, const FMOD_VECTOR& velocity, const FMOD_VECTOR& forward, const FMOD_VECTOR& up);
		void updateSound(const FMOD_VECTOR& position, const FMOD_VECTOR& velocity, int channel);



		void stopMusic();
		int getMusicChannel();
	private:
		static Implementation* sgpImplementation;
		static AudioManager* instance_;
		FMOD::SoundGroup* music;
		int musicChannel;
		FMOD::SoundGroup* fx;

		float changeQuantity = 0.1f;

		float musicVolume;
		float fxVolume;
	};
}
#endif _AUDIO_MANAGER_AUDIO_MANAGER_H