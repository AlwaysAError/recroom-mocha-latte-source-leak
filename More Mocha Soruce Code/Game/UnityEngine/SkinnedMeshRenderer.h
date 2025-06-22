#pragma once

struct AssetBundleRequest : UObject {

	typedef Il2CppArray* (*get_allAssets_t)(AssetBundleRequest*);
	Il2CppArray* get_allAssets() {
		const auto func = (get_allAssets_t)(GameAssembly + 0x93A28A0);
		return func(this);
	}

};

struct AssetBundle : UObject {

	typedef AssetBundle* (*LoadFromFile_t)(Il2CppString*);
	static AssetBundle* LoadFromFile(Il2CppString* path) {
		const auto func = (LoadFromFile_t)(GameAssembly + 0x93A3610);
		return func(path);
	}

	typedef AssetBundleRequest* (*LoadAllAssetsAsync_t)(AssetBundle*);
	AssetBundleRequest* LoadAllAssetsAsync() {
		const auto func = (LoadAllAssetsAsync_t)(GameAssembly + 0x93A2960);
		return func(this);
	}

};

struct SkinnedMeshRenderer : Renderer {

};