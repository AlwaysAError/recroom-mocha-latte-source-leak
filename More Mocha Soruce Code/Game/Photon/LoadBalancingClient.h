#pragma once

struct AuthenticationValues
{
	typedef AuthenticationValues* (*get_AuthenticationValues_t)();
	static AuthenticationValues* get_AuthenticationValues() {
		const auto func = (get_AuthenticationValues_t)(GameAssembly + 0x0);
		return func();
	}

	typedef Il2CppString* (*toString_t)(AuthenticationValues* instance);
	Il2CppString* toString() {
		const auto func = (toString_t)(GameAssembly + 0x0);
		return func(this);
	}

	typedef Il2CppString* (*get_AuthGetParemeters_t)(AuthenticationValues* instance);
	Il2CppString* get_AuthGetParemeters() {
		const auto func = (get_AuthGetParemeters_t)(GameAssembly + 0x0);
		return func(this);
	}

	typedef Il2CppString* (*get_RandomOne_t)(AuthenticationValues* instance);
	Il2CppString* get_RandomOne() {
		const auto func = (get_RandomOne_t)(GameAssembly + 0x0);
		return func(this);
	}

	typedef Il2CppString* (*get_RandomTwo_t)(AuthenticationValues* instance);
	Il2CppString* get_RandomTwo() {
		const auto func = (get_RandomTwo_t)(GameAssembly + 0x0);
		return func(this);
	}

	typedef Il2CppString* (*get_RandomThree_t)(AuthenticationValues* instance);
	Il2CppString* get_RandomThree() {
		const auto func = (get_RandomThree_t)(GameAssembly + 0x0);
		return func(this);
	}
};

struct LoadBalancingClient : Il2CppObject {
	typedef AuthenticationValues* (*get_authenticationValues_t)(LoadBalancingClient* instance);
	AuthenticationValues* get_authenticationValues() {
		const auto func = (get_authenticationValues_t)(GameAssembly + 0x0);
		return func(this);
	}

	typedef Il2CppString* (*get_appId_t)(LoadBalancingClient* instance);
	Il2CppString* get_appId() {
		const auto func = (get_appId_t)(GameAssembly + 0x0);
		return func(this);
	}

	typedef Il2CppString* (*get_appVersion_t)(LoadBalancingClient* instance);
	Il2CppString* get_appVersion() {
		const auto func = (get_appVersion_t)(GameAssembly + 0x0);
		return func(this);
	}
};

struct AppSettings
{
	typedef Il2CppString* (*toStringFull_t)(AppSettings* appSettings);
	Il2CppString* toStringFull() {
		const auto func = (toStringFull_t)(GameAssembly + 0x0);
		return func(this);
	}
};

struct ServerSettings
{
	typedef ServerSettings* (*get_serverSettings_t)();
	static ServerSettings* get_serverSettings() {
		const auto func = (get_serverSettings_t)(GameAssembly + 0x0);
		return func();
	}

	typedef Il2CppString* (*toString_t)();
	Il2CppString* toString() {
		const auto func = (toString_t)(GameAssembly + 0x0);
		return func();
	}
};

struct ConnectionHandler : MonoBehaviour {

	typedef LoadBalancingClient* (*get_Client_t)(ConnectionHandler* instance);
	LoadBalancingClient* get_Client() {
		const auto func = (get_Client_t)(GameAssembly + 0x0);
		return func(this);
	}

};