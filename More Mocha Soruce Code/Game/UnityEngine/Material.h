#pragma once

struct Material : UObject {

	typedef void (*StaticConstructor_t)(Material* obj, Shader* shader);
	static Material* ctor(Shader* shader)
	{
		Il2CppClass* klass = FindClass("UnityEngine.Material");
		Material* object = (Material*)il2cpp_object_new_spoof(klass);
		if (object == nullptr)
			return nullptr;
		const auto func = (StaticConstructor_t)(GameAssembly + 0x93C48F0);
		func(object, shader);
		return object;
	}

	typedef void (*setColor_t)(Material* material, ImVec4 colour);
	void setColor(ImVec4 colour) {
		const auto func = (setColor_t)(methods::UnityEngine::Material::setColor);
		return func(this, colour);
	}

	typedef void (*SetColor_t)(Material* material, Il2CppString* name, ImVec4 colour);
	void SetColor(Il2CppString* name, ImVec4 colour) {
		const auto func = (SetColor_t)(GameAssembly + 0x93C2EE0);
		return func(this, name, colour);
	}

	typedef void (*SetTexture_t)(Material* material, Il2CppString* name, void* texture);
	void SetTexture(Il2CppString* name, void* texture) {
		const auto func = (SetTexture_t)(GameAssembly + 0x93C42D0);
		return func(this, name, texture);
	}

	typedef void (*SetFloat_t)(Material* material, Il2CppString* name, float value);
	void SetFloat(Il2CppString* name, float value) {
		const auto func = (SetFloat_t)(GameAssembly + 0x93C35B0);
		return func(this, name, value);
	}

	typedef Shader* (*get_shader_t)(Material* material);
	Shader* get_shader() {
		const auto func = (get_shader_t)(GameAssembly + 0x93C4F70);
		return func(this);
	}

	typedef void (*setShader_t)(Material* material, void* shader);
	void setShader(void* shader) {
		const auto func = (setShader_t)(methods::UnityEngine::Material::setShader);
		return func(this, shader);
	}

	typedef Material* (*getDefaultMaterial_t)();
	static Material* getDefaultMaterial() {
		const auto func = (getDefaultMaterial_t)(methods::UnityEngine::Material::getDefaultMaterial);
		return func();
	}

};