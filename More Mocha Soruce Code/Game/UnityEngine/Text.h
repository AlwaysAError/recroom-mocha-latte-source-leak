#pragma once

struct UFont : Component {
	typedef UFont* (*getDefaultFont_t)();
	static UFont* getDefaultFont() {
		const auto func = (getDefaultFont_t)(methods::UnityEngine::Font::getDefaultFont);
		return func();
	}
};

struct UText : Component {

	typedef void (*set_Text_t)(UText* component, Il2CppString* text);
	void set_Text(Il2CppString* text) {
		const auto func = (set_Text_t)(methods::UnityEngineUI::Text::set_Text);
		return func(this, text);
	}

	typedef void (*setFontSize_t)(UText* component, int size);
	void setFontSize(int size) {
		const auto func = (setFontSize_t)(methods::UnityEngineUI::Text::setFontSize);
		return func(this, size);
	}

	typedef void* (*getFont_t)(UText* component);
	void* getFont() {
		const auto func = (getFont_t)(methods::UnityEngineUI::Text::getFont);
		return func(this);
	}

	typedef void* (*getMainTexture_t)(UText* component);
	void* getMainTexture() {
		const auto func = (getMainTexture_t)(methods::UnityEngineUI::Text::getMainTexture);
		return func(this);
	}

	typedef void* (*getFontStyle_t)(UText* component);
	void* getFontStyle() {
		const auto func = (getFontStyle_t)(methods::UnityEngineUI::Text::getFontStyle);
		return func(this);
	}

	typedef void (*setFont_t)(UText* component, UFont* value);
	void setFont(UFont* value) {
		const auto func = (setFont_t)(methods::UnityEngineUI::Text::setFont);
		return func(this, value);
	}

	typedef void (*set_alignment_t)(UText* component, int value);
	void set_alignment(int value) {
		const auto func = (set_alignment_t)(GameAssembly + 0x9650130);
		return func(this, value);
	}

};