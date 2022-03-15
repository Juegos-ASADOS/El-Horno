//#pragma once
//#ifndef _FMOD_H
//#define _FMOD_H
//
//#include <string>
//#include <map>
//
//
//namespace FMOD {
//	class ChannelGroup;
//	class Channel;
//	class System;
//	class fmod_studio;
//}
//
//struct Vector3 {
//	float x;
//	float y;
//	float z;
//};
//
//class Implementation {
//public:
//	Implementation();
//	~Implementation();
//
//	void Update();
//
//	FMOD::Studio::System* mpStudioSystem;
//	FMOD::System* mpSystem;
//
//	int mnNextChannelId;
//
//	typedef std::map<std::string, FMOD::Sound*> SoundMap;
//	typedef std::map<int, FMOD::Channel*> ChannelMap;
//	typedef std::map<std::string, FMOD::Studio::EventInstance*> EventMap;
//	typedef std::map<std::string, FMOD::Studio::Bank*> BankMap;
//
//	BankMap mBanks;
//	EventMap mEvents;
//	SoundMap mSounds;
//	ChannelMap mChannels;
//};
//
//class ElHornoFMOD
//{
//public:
//	static void init();
//	static void Update();
//	static void Shutdown();
//	static int ErrorCheck(FMOD_RESULT result);
//
//	//void LoadBank(const std::string& strBankName, FMOD::FMOD_STUDIO_LOAD_BANK_FLAGS flags);
//	//void LoadEvent(const string& strEventName);
//	void Loadsound(const std::string& strSoundName, bool b3d = true, bool bLooping = false, bool bStream = false);
//	void UnLoadSound(const std::string& strSoundName);
//	void Set3dListenerAndOrientation(const Vector3& vPos = Vector3{ 0, 0, 0 }, float fVolumedB = 0.0f);
//	int PlaySound(const std::string& strSoundName, const Vector3& vPos = Vector3{ 0, 0, 0 }, float fVolumedB = 0.0f);
//	//void PlayEvent(const string& strEventName);
//	void StopChannel(int nChannelId);
//	//void StopEvent(const string& strEventName, bool bImmediate = false);
//	//void GeteventParameter(const string& strEventName, const string% strEventParameter, float* parameter);
//	//void SetEventParameter(const string& strEventName, const string& strParameterName, flaot fValue);
//	void StopAllChannels();
//	void SetChannel3dPosition(int nChannelId, const Vector3& vPosition);
//	void SetChannelvolume(int nChannelId, float fVolumedB);
//	bool IsPlaying(int nChannelId) const;
//	//bool IsEventPlaying(const string& strEventName) const;
//	float dbToVolume(float db);
//	float VolumeTodb(float volume);
//	FMOD_VECTOR VectorToFmod(const Vector3& vPosition);
//
//	int ErrorCheck(FMOD_RESULT result);
//
//	void updateListener(int Listener, const Vector3& position, const Vector3& velocity, const Vector3& forward, const Vector3& up);
//	void updateSound(const Vector3& position, const Vector3& velocity, int channel);
//
//private:
//	static Implementation* sgpImplementation;
//};
//
//#endif _FMOD_H