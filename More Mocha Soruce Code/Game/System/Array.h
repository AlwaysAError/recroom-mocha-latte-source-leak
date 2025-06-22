#pragma once

struct Array : Il2CppArray {

	typedef Il2CppArray* (*createInstance_t)(Il2CppType* elementType, int32_t length);
	static Il2CppArray* createInstance(Il2CppType* elementType, int32_t length) {
		const auto func = (createInstance_t)(methods::System::Array::createInstance);
		return func(elementType, length);
	}

	typedef Il2CppObject* (*GetValue_t)(Array* instance, int32_t index);
	Il2CppObject* GetValue(int32_t index) {
		const auto func = (GetValue_t)(GameAssembly + 0x6E50200);
		return func(this, index);
	}

	typedef void (*SetValue_t)(Array* instance, Il2CppObject* value, int32_t index);
	void SetValue(Il2CppObject* value, int32_t index) {
		const auto func = (SetValue_t)(GameAssembly + 0x6E50DD0);
		return func(this, value, index);
	}

};