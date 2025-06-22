#pragma once

struct NativeJson {

	typedef Il2CppString* (*SerializeObject_t)(Il2CppObject* value);
	static Il2CppString* SerializeObject(Il2CppObject* value) {
		const auto func = (SerializeObject_t)(GameAssembly + 0x6F0E6B0); //json convert
		return func(value);
	}

	typedef Il2CppObject* (*DeserializeObject_t)(Il2CppString* value, Il2CppType* type, Il2CppObject* converters);
	static Il2CppObject* DeserializeObject(Il2CppString* value, Il2CppType* type, Il2CppObject* converters) {
		const auto func = (DeserializeObject_t)(GameAssembly + 0x0);
		return spoof_call(returnSpoofAddress, func, value, type, converters);
	}

};

struct FakeDictionary : Il2CppObject {


};