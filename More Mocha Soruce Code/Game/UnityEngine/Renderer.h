#pragma once

struct Renderer : Component {

	typedef int32_t (*GetMaterialCount_t)(Renderer* renderer);
	int32_t GetMaterialCount() {
		const auto func = (GetMaterialCount_t)(GameAssembly + 0x93CC3A0);
		return func(this);
	}

	typedef void (*set_materials_t)(Renderer* renderer, Il2CppArray* materials);
	void set_materials(Il2CppArray* materials) {
		const auto func = (set_materials_t)(GameAssembly + 0x93CCA60);
		return func(this, materials);
	}

	typedef Material* (*getMaterial_t)(Renderer* renderer);
	Material* getMaterial() {
		const auto func = (getMaterial_t)(methods::UnityEngine::Renderer::getMaterial);
		return func(this);
	}

	typedef void (*setMaterial_t)(Renderer* renderer, Material* material);
	void setMaterial(Material* material) {
		const auto func = (setMaterial_t)(methods::UnityEngine::Renderer::setMaterial);
		return func(this, material);
	}

};