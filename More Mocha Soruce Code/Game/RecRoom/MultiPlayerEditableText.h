#pragma once

struct MultiPlayerEditableText : MonoBehaviourPun {

	typedef void (*SynchronizedMessageSet_t)(MultiPlayerEditableText* instance, int i, Il2CppString* newMessage, bool sanitize, bool forceSync);
	void SynchronizedMessageSet(int i, Il2CppString* newMessage, bool sanitize = false, bool forceSync = false) {
		const auto func = (SynchronizedMessageSet_t)(GameAssembly + 0x1D824F0); // this is obfuscated do not be fooled search term -> "METHOD(void, (MultiPlayerEditableText*, int32_t, Il2CppString*, bool, bool, MethodInfo*)"
		return func(this, i, newMessage, sanitize, forceSync);
	}
};

struct MultiPlayerEditableTextV2 : MonoBehaviourPun {

	typedef void* (*DefaultMessageSet_t)(MultiPlayerEditableTextV2* instance, Il2CppString* value);
	void DefaultMessageSet(Il2CppString* newMessage) {
		const auto func = (DefaultMessageSet_t)(GameAssembly + 0x1D813E0); // search term -> "METHOD(void, (MultiPlayerEditableTextV2*, Il2CppString*, MethodInfo*)"

		func(this, newMessage);
	}

};