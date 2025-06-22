#pragma once

struct AudioPlayer : MonoBehaviourPun {

	enum class Channel
	{
		Voice = 0,
		Sfx = 1,
		Music = 2,
		Ambience = 3,
		Master = 4,
		CoachVO = 5,
		VoiceCall = 6,
	};
	
	typedef void (*set_VolumeModifier_t)(AudioPlayer* instance, float value);
	void set_VolumeModifier(float value) {
		const auto func = (set_VolumeModifier_t)(GameAssembly + 0x1A915C0);
		return func(this, value);
	}

	typedef void (*set_SpeedModifier_t)(AudioPlayer* instance, float value);
	void set_SpeedModifier(float value) {
		const auto func = (set_SpeedModifier_t)(GameAssembly + 0x1A91500);
		return func(this, value);
	}

	typedef void (*set_LoopAudio_t)(AudioPlayer* instance, bool value);
	void set_LoopAudio(bool value) {
		const auto func = (set_LoopAudio_t)(GameAssembly + 0x1A913E0);
		return func(this, value);
	}

	typedef void (*set_AudioChannel_t)(AudioPlayer* instance, Channel value);
	void set_AudioChannel(Channel value) {
		const auto func = (set_AudioChannel_t)(GameAssembly + 0x1A912C0);
		return func(this, value);
	}
};