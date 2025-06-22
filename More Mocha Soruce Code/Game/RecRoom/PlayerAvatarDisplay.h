#pragma once

struct PlayerAvatarDisplay : MonoBehaviour {

	typedef void (*SetSkinColor_t)(PlayerAvatarDisplay* instance, ImVec4 color);
	void SetSkinColor(ImVec4 color) {
		const auto func = (SetSkinColor_t)(methods::PlayerAvatarDisplay::SetSkinColor);
		return func(this, color);
	}

};