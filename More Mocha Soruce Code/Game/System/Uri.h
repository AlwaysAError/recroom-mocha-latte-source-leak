#pragma once

struct Uri : Il2CppObject {

	enum class UriKind
	{
		RelativeOrAbsolute = 0,
		Absolute = 1,
		Relative = 2,
	};

	typedef bool (*tryCreate_t)(Il2CppString* uriString, UriKind uriKind, Uri** result);
	static Uri* TryCreate(const char* uriString, UriKind uriKind) { // RelativeOrAbsolute = 0, Absolute = 1, Relative = 2
		Uri* resultUri = nullptr;
		Il2CppString* il2cppUriString = WriteIl2CppString(uriString);
		const auto func = (tryCreate_t)(methods::System::Uri::TryCreate);

		if (func(il2cppUriString, uriKind, &resultUri))
			return resultUri;

		Log::error("Failed to create uri!");
		return nullptr;
	}

	typedef Il2CppString* (*ToString_t)(Uri*);
	Il2CppString* ToString() {
		const auto func = (ToString_t)(methods::System::Uri::ToString);

		return func(this);
	}


};