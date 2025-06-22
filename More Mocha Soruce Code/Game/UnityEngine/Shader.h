#pragma once

struct Shader : UObject {

	typedef Shader* (*shaderFind_t)(Il2CppString* name);
	static Shader* shaderFind(Il2CppString* name) {
		const auto func = (shaderFind_t)(methods::UnityEngine::Shader::shaderFind);
		return func(name);
	}

};
