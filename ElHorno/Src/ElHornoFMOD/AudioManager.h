#pragma once
#ifndef _FMOD_H
#define _FMOD_H

#include <string>
#include <map>


namespace FMOD {
	class ChannelGroup;
	class Channel;
	class System;
	class fmod_studio;
}

class Implementation {
public:
	Implementation();
	~Implementation();

	void Update();

	FMOD::Studio::System* mpStudioSystem;
	FMOD::System* mpSystem;

	int mnNextChannelId;

	typedef std::map<std::string, FMOD::Sound*> SoundMap;
	typedef std::map<int, FMOD::Channel*> ChannelMap;
	//typedef std::map<std::string, FMOD::Studio::EventInstance*> EventMap;
	typedef std::map<std::string, FMOD::Studio::Bank*> BankMap;

	BankMap mBanks;
	//EventMap mEvents;
	SoundMap mSounds;
	ChannelMap mChannels;
};

class AudioManager
{
public:
	static void init();
	static void Update();
	static void Shutdown();
	static int ErrorCheck(FMOD_RESULT result);
	bool setInstance();
	static AudioManager* getInstance();

	//void LoadBank(const std::string& strBankName, FMOD::FMOD_STUDIO_LOAD_BANK_FLAGS flags);
	//void LoadEvent(const string& strEventName);
	void Loadsound(const std::string& strSoundName, bool b3d = true, bool bLooping = false, bool bStream = false);
	void UnLoadSound(const std::string& strSoundName);
	void Set3dListenerAndOrientation(const FMOD_VECTOR& vPos = { 0, 0, 0 }, float fVolumedB = 0.0f);
	int PlaySound(const std::string& strSoundName, const FMOD_VECTOR& vPos = { 0, 0, 0 }, float fVolumedB = 0.0f);
	//void PlayEvent(const string& strEventName);
	void StopChannel(int nChannelId);
	//void StopEvent(const string& strEventName, bool bImmediate = false);
	//void GeteventParameter(const string& strEventName, const string% strEventParameter, float* parameter);
	//void SetEventParameter(const string& strEventName, const string& strParameterName, flaot fValue);
	void StopAllChannels();
	void SetChannel3dPosition(int nChannelId, const FMOD_VECTOR& vPosition);
	void SetChannelvolume(int nChannelId, float fVolumedB);
	bool IsPlaying(int nChannelId) const;
	//bool IsEventPlaying(const string& strEventName) const;
	float dbToVolume(float db);
	float VolumeTodb(float volume);

	int ErrorCheck(FMOD_RESULT result);

	void updateListener(int Listener, const FMOD_VECTOR& position, const FMOD_VECTOR& velocity, const FMOD_VECTOR& forward, const FMOD_VECTOR& up);
	void updateSound(const FMOD_VECTOR& position, const FMOD_VECTOR& velocity, int channel);

private:
	static Implementation* sgpImplementation;
	static AudioManager* instance_;
};

#endif _FMOD_H