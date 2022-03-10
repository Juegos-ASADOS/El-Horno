//#pragma once
//#ifndef _FMOD_H
//#define _FMOD_H
//
//using namespace std;
//
//namespace FMOD {
//	class ChannelGroup;
//	class Channel;
//	class System;
//    class fmod_studio;
//}
//
//class Implementation {
//public:
//    Implementation();
//    ~Implementation();
//
//    void Update();
//
//    FMOD::Studio::System* mpStudioSystem;
//    FMOD::System* mpSystem;
//
//    int mnNextChannelId;
//
//    typedef map<string, FMOD::Sound*> SoundMap;
//    typedef map<int, FMOD::Channel*> ChannelMap;
//    typedef map<string, FMOD::Studio::EventInstance*> EventMap;
//    typedef map<string, FMOD::Studio::Bank*> BankMap;
//
//    BankMap mBanks;
//    EventMap mEvents;
//    SoundMap mSounds;
//    ChannelMap mChannels;
//};
//
//class ElHornoFMOD
//{
//public:
//	static void init();
//};
//
//#endif _FMOD_H