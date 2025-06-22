#pragma once

struct UObject : Il2CppObject {
	typedef Il2CppString* (*GetName_t)(UObject* object);
	Il2CppString* GetName() {
		const auto func = (GetName_t)(methods::UnityEngine::Object::GetName);
		return func(this);
	}

	typedef void (*set_name_t)(UObject* object, Il2CppString* name);
	void set_name(Il2CppString* name) {
		const auto func = (set_name_t)(methods::UnityEngine::Object::set_name);
		return func(this, name);
	}

	typedef void (*Destroy_t)(UObject* object);
	void Destroy() {
		const auto func = (Destroy_t)(methods::UnityEngine::Object::Destroy);
		return func(this);
	}

	typedef Il2CppString* (*ToString_t)(UObject* object);
	Il2CppString* ToString() {
		const auto func = (ToString_t)(methods::UnityEngine::Object::ToString);
		return func(this);
	}

	typedef Il2CppArray* (*FindObjectsOfType_t)(Il2CppType* typeObject);
	static Il2CppArray* FindObjectsOfType(const char* typeName) {
		Il2CppClass* klass = FindClass(typeName);
		if (!klass) return nullptr;
		Il2CppString* typeString = il2cpp_string_new_spoof(typeName);
		Il2CppType* typeObject = Type::getType(typeString);
		const auto func = (FindObjectsOfType_t)(methods::UnityEngine::Object::FindObjectsOfType);
		return func(typeObject);
	}

};