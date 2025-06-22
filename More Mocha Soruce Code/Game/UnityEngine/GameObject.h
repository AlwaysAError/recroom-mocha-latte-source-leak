#pragma once

struct Transform;
struct Type;

enum PrimitiveType {
	Sphere = 0,
	Capsule = 1,
	Cylinder = 2,
	Cube = 3,
	Plane = 4,
	Quad = 5,
};

struct GameObject : UObject {

	typedef void (*StaticConstructor_t)(GameObject* object, Il2CppString* name);
	static GameObject* ctor(Il2CppString* name)
	{
		Il2CppClass* klass = FindClass("UnityEngine.GameObject");
		GameObject* object = (GameObject*)il2cpp_object_new_spoof(klass);;
		if (object == nullptr)
			return nullptr;
		const auto func = (StaticConstructor_t)(methods::UnityEngine::GameObject::ctor);
		func(object, name);
		return object;
	}

	typedef Il2CppArray* (*GetComponents_t)(GameObject* object, Il2CppType* typeObject);
	Il2CppArray* GetComponents(const char* typeName) {
		Il2CppString* typeString = il2cpp_string_new_spoof(typeName);
		Il2CppType* typeObject = Type::getType(typeString);
		const auto func = (GetComponents_t)(methods::UnityEngine::GameObject::GetComponents);
		return func(this, typeObject);
	}

	typedef Component* (*GetComponent_t)(GameObject* object, Il2CppString* typeString);
	Component* GetComponent(const char* type) {
		Il2CppString* typeString = il2cpp_string_new_spoof(type);
		const auto func = (GetComponent_t)(methods::UnityEngine::GameObject::GetComponent);
		return func(this, typeString);
	}

	typedef Transform* (*get_transform_t)(GameObject* object);
	Transform* get_transform() {
		const auto func = (get_transform_t)(methods::UnityEngine::GameObject::get_transform);
		return func(this);
	}

	typedef bool (*get_active_t)(GameObject* object);
	bool get_active() {
		const auto func = (get_active_t)(methods::UnityEngine::GameObject::get_active);
		return func(this);
	}

	typedef void (*set_active_t)(GameObject* object, bool enabled);
	void set_active(bool enabled) {
		const auto func = (set_active_t)(methods::UnityEngine::GameObject::set_active);
		return func(this, enabled);
	}

	typedef Component* (*AddComponent_t)(GameObject* object, Il2CppType* componentType);
	Component* AddComponent(Il2CppType* componentType) {
		const auto func = (AddComponent_t)(methods::UnityEngine::GameObject::AddComponent);
		return func(this, componentType);
	}

	typedef GameObject* (*CreatePrimitive_t)(PrimitiveType type);
	static GameObject* CreatePrimitive(PrimitiveType type) {
		const auto func = (CreatePrimitive_t)(methods::UnityEngine::GameObject::CreatePrimitive);
		return func(type);
	}

	typedef GameObject* (*Find_t)(Il2CppString* objectName);
	static GameObject* Find(Il2CppString* objectName) {
		const auto func = (Find_t)(methods::UnityEngine::GameObject::Find);
		return func(objectName);
	}

	typedef void (*set_layer_t)(GameObject* object, int value);
	void set_layer(int value) {
		const auto func = (set_layer_t)(methods::UnityEngine::GameObject::set_layer);
		return func(this, value);
	}

	typedef int (*get_layer_t)(GameObject* object);
	int get_layer() {
		const auto func = (get_layer_t)(methods::UnityEngine::GameObject::get_layer);
		return func(this);
	}

};