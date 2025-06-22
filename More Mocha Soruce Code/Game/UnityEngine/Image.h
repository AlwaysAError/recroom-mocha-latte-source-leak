#pragma once

struct UFile : Il2CppObject
{
	typedef bool (*exists_t)(Il2CppString* value);
	static bool Exists(Il2CppString* value) {
		const auto func = (exists_t)(GameAssembly + 0x6DD7700);
		return func(value);
	}

	typedef Il2CppArray* (*readAllBytes_t)(Il2CppString* value);
	static Il2CppArray* ReadAllBytes(Il2CppString* value) {
		const auto func = (readAllBytes_t)(GameAssembly + 0x6DD90A0);
		return func(value);
	}
};

struct Rect
{
	float xMin;
	float yMin;
	float width;
	float height;
};

enum Transition
{
	NoneT = 0,
	ColorTint = 1,
	SpriteSwap = 2,
	Animation = 3
};

struct RectTransform : Component {

	typedef void (*set_sizeDelta_t)(RectTransform* object, Vector2 value);
	void set_sizeDelta(Vector2 value) {
		const auto func = (set_sizeDelta_t)(GameAssembly + 0x9405520);
		return func(this, value);
	}

	typedef void (*set_anchoredPosition_t)(RectTransform* object, Vector2 value);
	void set_anchoredPosition(Vector2 value) {
		const auto func = (set_anchoredPosition_t)(GameAssembly + 0x9404D90);
		return func(this, value);
	}

	/*
	typedef void (*set_pivot_t)(RectTransform* object, Vector2 value);
	void set_pivot(Vector2 value) {
		set_pivotconst auto func = (set_pivot_t)(GameAssembly + 0x83BCFC0);
		return func(this, value);
	}
	*/
};

struct Graphic : MonoBehaviour {

	typedef void (*set_color_t)(Graphic* object, ImVec4 value);
	void set_color(ImVec4 value) {
		const auto func = (set_color_t)(GameAssembly + 0x94DE9F0);
		return func(this, value);
	}

	typedef RectTransform* (*get_rectTransform_t)(Graphic* object);
	RectTransform* get_rectTransform() {
		const auto func = (get_rectTransform_t)(GameAssembly + 0x94DE820);
		return func(this);
	}

};

struct ColorBlock
{
	/*typedef void (*StaticConstructor_t)(ColorBlock* colorBlock);
	static ColorBlock* ctor()
	{
		Il2CppClass* klass = findClass("UnityEngine.UI.ColorBlock");
		ColorBlock* object = (ColorBlock*)il2cpp_object_new_spoof(klass);
		if (object == nullptr)
			return nullptr;

		StaticConstructorconst auto func = (StaticConstructor_t)(GameAssembly + 0x8557140);

		func(object);
		return object;
	}

	typedef void (*set_normalColor_t)(ColorBlock* object, Color value);
	void set_normalColor(Color value) {
		set_normalColorconst auto func = (set_normalColor_t)(GameAssembly + 0xDC76F0);
		return func(this, value);
	}

	typedef void (*set_highlightedColor_t)(ColorBlock* object, Color value);
	void set_highlightedColor(Color value) {
		set_highlightedColorconst auto func = (set_highlightedColor_t)(GameAssembly + 0xB885D0);
		return func(this, value);
	}

	typedef void (*set_pressedColor_t)(ColorBlock* object, Color value);
	void set_pressedColor(Color value) {
		set_pressedColorconst auto func = (set_pressedColor_t)(GameAssembly + 0xA6D210);
		return func(this, value);
	}*/

	ImVec4 normalColor;
	ImVec4 highlightedColor;
	ImVec4 pressedColor;
	ImVec4 selectedColor;
	ImVec4 disabledColor;
	float colorMultiplier;
	float fadeDuration;
};

struct Texture2D
{
	typedef void (*StaticConstructor_t)(Texture2D* texture2D, int width, int height);
	static Texture2D* ctor(int width, int height)
	{
		Il2CppClass* klass = FindClass("UnityEngine.Texture2D");
		Texture2D* object = (Texture2D*)il2cpp_object_new_spoof(klass);
		if (object == nullptr)
			return nullptr;

		const auto func = (StaticConstructor_t)(GameAssembly + 0x93F4370); // last ctor

		func(object, width, height);
		return object;
	}

	typedef bool (*loadImage_t)(Texture2D* object, Il2CppArray* value);
	bool loadImage(Il2CppArray* value) {
		const auto func = (loadImage_t)(GameAssembly + 0x943ECA0); // search term -> "static bool LoadImage(UnityEngine::Texture2D* tex, Array<uint8_t>* data)"
		return func(this, value);
	}

	// two below inherited from Texture.h

	typedef int (*get_width_t)(Texture2D* object);
	int get_width() {
		const auto func = (get_width_t)(GameAssembly + 0x93F5BA0);
		return func(this);
	}

	typedef int (*get_height_t)(Texture2D* object);
	int get_height() {
		const auto func = (get_height_t)(GameAssembly + 0x93F5B60);
		return func(this);
	}
};

struct Sprite
{
	typedef Sprite*(*create_t)(Texture2D* texture, Rect rect, Vector2 pivot);
	static Sprite* Create(Texture2D* texture, Rect rect, Vector2 pivot) {
		const auto func = (create_t)(GameAssembly + 0x9429300);
		return func(texture, rect, pivot);
	}
};

struct Image : Graphic {
	typedef void (*set_material_t)(Image* object, Material* value);
	void set_material(Material* value) {
		const auto func = (set_material_t)(GameAssembly + 0x94DEA40);
		return func(this, value);
	}

	typedef void (*set_sprite_t)(Image* object, Sprite* value);
	void set_sprite(Sprite* value) {
		const auto func = (set_sprite_t)(GameAssembly + 0x94E6340);
		return func(this, value);
	}
};