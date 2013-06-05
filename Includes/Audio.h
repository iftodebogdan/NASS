/*
 * Audio.h
 *
 *  Created on: Jun 4, 2013
 *      Author: Bogdan
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include <oslib/oslib.h>
#include <string>
using namespace std;

#define BGM_AUDIO_CHANNEL 0
#define MENU_SFX_AUDIO_CHANNEL 1
#define PLAYER_SFX_AUDIO_CHANNEL 2
#define WARP_SFX_AUDIO_CHANNEL 3
#define DEMATERIALIZE_SFX_AUDIO_CHANNEL 4
#define OVERDRIVE_SFX_AUDIO_CHANNEL 5
#define FORCE_FIELD_SFX_AUDIO_CHANNEL 6

class Sound
{
public:
	Sound(string pathToSndFile, bool isStreamed);
	~Sound();

	bool Play();
	bool PlayLooped();
	void Pause();
	void Resume();
	void PlayPause();
	void Stop();
	bool IsPlaying();

private:
	OSL_SOUND* mSound;
};

class Audio
{
	friend class Sound;
	friend class Game;

private:
	static int GetAvailableChannel();
	static bool IsChannelAvailable(int channelNumber);
	static bool ReserveChannel(int channelNumber);
	static bool UnreserveChannel(int channelNumber);
	static int UnreserveChannelCallback(OSL_SOUND *s, int voice);

	static bool mAvailableChannels[8];
};

#endif /* AUDIO_H_ */
