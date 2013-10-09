/*
 * Audio.cpp
 *
 *  Created on: Jun 4, 2013
 *      Author: Bogdan
 */

#include "../Includes/Audio.hpp"

#include "../Includes/Resources.hpp"

Sound::Sound(string pathToSndFile, bool isStream)
{
	mSound = oslLoadSoundFile(pathToSndFile.c_str(), isStream ? (int)OSL_FMT_STREAM : (int)OSL_FMT_NONE);
	oslAssert(mSound != NULL);
}

Sound::~Sound()
{
	oslDeleteSound(mSound);
	delete mSound;
}

bool Sound::Play()
{
	int channel;
	if(IsPlaying())
		channel = oslGetSoundChannel(mSound);
	else
		channel = Audio::GetAvailableChannel();

	if(channel == -1)
		return false;

	oslSetSoundEndCallback(mSound, *Audio::UnreserveChannelCallback);
	oslPlaySound(mSound, channel);
	Audio::ReserveChannel(channel);

	return true;
}

bool Sound::PlayLooped()
{
	int channel;
	if(IsPlaying())
		channel = oslGetSoundChannel(mSound);
	else
		channel = Audio::GetAvailableChannel();

	if(channel == -1)
		return false;

	oslSetSoundLoop(mSound, true);
	oslPlaySound(mSound, channel);
	Audio::ReserveChannel(channel);

	return true;
}

void Sound::Pause()
{
	oslPauseSound(mSound, 1);
}

void Sound::Resume()
{
	oslPauseSound(mSound, 0);
}

void Sound::PlayPause()
{
	oslPauseSound(mSound, -1);
}

void Sound::Stop()
{
	oslStopSound(mSound);
	if(oslGetSoundChannel(mSound) != -1)
		Audio::UnreserveChannel(oslGetSoundChannel(mSound));
}

bool Sound::IsPlaying()
{
	if(oslGetSoundChannel(mSound) != -1)
		return true;

	return false;
}

bool Audio::mAvailableChannels[8] = {true, true, true, true, true, true, true, true};

int Audio::GetAvailableChannel()
{
	for(int i = 0; i <= 7; i++)
		if(mAvailableChannels[i] == true)
			return i;

	return -1;
}

bool Audio::IsChannelAvailable(int channelNumber)
{
	return mAvailableChannels[channelNumber];
}

bool Audio::ReserveChannel(int channelNumber)
{
	if(mAvailableChannels[channelNumber] == true)
	{
		mAvailableChannels[channelNumber] = false;
		return true;
	}
	else
		return false;
}

bool Audio::UnreserveChannel(int channelNumber)
{
	if(mAvailableChannels[channelNumber] == false)
	{
		mAvailableChannels[channelNumber] = true;
		return true;
	}
	else
		return false;
}

int Audio::UnreserveChannelCallback(OSL_SOUND* s, int voice)
{
	Audio::UnreserveChannel(voice);
	return 0;
}
