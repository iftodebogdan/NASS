void InitAudio()
{
	oslInit(0);
	oslInitAudio();
	oslSetModSampleRate(44100, 1, 0);
	BGM = oslLoadSoundFileBGM("res/snd/BgSnd.bgm", OSL_FMT_STREAM);
	oslPlaySound(BGM, 0);
	oslSetSoundLoop(BGM, 1);
	
	SFXConfirm = oslLoadSoundFileBGM("res/snd/SFXConfirm.bgm", OSL_FMT_NONE);
    SFXNavigate = oslLoadSoundFileBGM("res/snd/SFXNavigate.bgm", OSL_FMT_NONE);
	SFXNavigateErr = oslLoadSoundFileBGM("res/snd/SFXNavigateErr.bgm", OSL_FMT_NONE);
	SFXComet = oslLoadSoundFileBGM("res/snd/SFXComet.bgm", OSL_FMT_NONE);
	SFXExplosion = oslLoadSoundFileBGM("res/snd/SFXExplosion.bgm", OSL_FMT_NONE);
	SFXLaunch = oslLoadSoundFileBGM("res/snd/SFXLaunch.bgm", OSL_FMT_NONE);
	SFXDamage = oslLoadSoundFileBGM("res/snd/SFXDamage.bgm", OSL_FMT_NONE);
}
