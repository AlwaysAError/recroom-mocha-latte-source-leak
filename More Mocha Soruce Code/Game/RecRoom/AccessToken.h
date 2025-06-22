#pragma once

struct AccessToken : UObject {

	Il2CppArray* SigningKey;
	int32_t Length;
	Il2CppArray* Token;

	typedef AccessToken* (*GetAccessToken_t)();
	static AccessToken* GetAccessToken() {
		const auto func = (GetAccessToken_t)(GameAssembly + 0x0);
		return func();
	}

};