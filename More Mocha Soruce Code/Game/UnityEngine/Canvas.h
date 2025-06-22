#pragma once

enum class RenderMode
{
	ScreenSpaceOverlay = 0,
	ScreenSpaceCamera = 1,
	WorldSpace = 2,
};

struct Canvas : Behaviour {

	typedef Vector2(*set_renderMode_t)(Canvas* object, RenderMode value);
	Vector2 set_renderMode(RenderMode value) {
		const auto func = (set_renderMode_t)(methods::UnityEngineUI::Canvas::set_renderMode);
		return func(this, value);
	}

	typedef int(*get_sortingOrder_t)(Canvas* object);
	int get_sortingOrder() {
		const auto func = (get_sortingOrder_t)(methods::UnityEngineUI::Canvas::get_sortingOrder);
		return func(this);
	}

	typedef void(*set_sortingOrder_t)(Canvas* object, int value);
	void set_sortingOrder(int value) {
		const auto func = (set_sortingOrder_t)(methods::UnityEngineUI::Canvas::set_sortingOrder);
		return func(this, value);
	}
};