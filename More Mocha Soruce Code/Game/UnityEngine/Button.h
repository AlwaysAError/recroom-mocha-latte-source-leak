#pragma once

struct Toggle : MonoBehaviour
{
	typedef bool(*get_isOn_t)(Toggle* object);
	bool get_isOn() {
		const auto func = (get_isOn_t)(methods::UnityEngineUI::Toggle::get_isOn);
		return func(this);
	}

	typedef void(*set_isOn_t)(Toggle* object, bool value);
	void set_isOn(bool value) {
		const auto func = (set_isOn_t)(methods::UnityEngineUI::Toggle::set_isOn);
		return func(this, value);
	}

	typedef void(*set_colors_t)(Toggle* object, ColorBlock value);
	void set_colors(ColorBlock value) {
		const auto func = (set_colors_t)(methods::UnityEngineUI::Selectable::set_colors);
		return func(this, value);
	}

	typedef void(*set_transition_t)(Toggle* object, Transition value);
	void set_transition(Transition value) {
		const auto func = (set_transition_t)(methods::UnityEngineUI::Selectable::set_transition);
		return func(this, value);
	}

	typedef void(*set_targetGraphic_t)(Toggle* object, Graphic* value);
	void set_targetGraphic(Graphic* value) {
		const auto func = (set_targetGraphic_t)(methods::UnityEngineUI::Selectable::set_targetGraphic);
		return func(this, value);
	}
};