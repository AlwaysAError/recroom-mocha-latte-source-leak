#pragma once

#include "Dependencies/RetSpoof/ReturnSpoof.hpp"

uint64_t* returnSpoofAddress = nullptr;

#define DO_API(r, n, p) typedef r (* n##_t) p; inline n##_t n
//#define INIT_API(h, n) n = reinterpret_cast<n##_t>(GetProcAddress(h, #n))

#define INIT_API(h, n)                             \
    do {                                           \
        n = reinterpret_cast<n##_t>(spoof_call(    \
            returnSpoofAddress, GetProcAddress,	   \
            h, #n));                               \
        if (!n) {                                  \
            printf("Failed to resolve: %s\n", #n); \
        }                                          \
    } while (0)

#include <vm/Array.h>
#include <il2cpp-api-types.h>
#include <il2cpp-api-functions.h> // use the modified one
#include <il2cpp-class-internals.h>
#include <il2cpp-object-internals.h>

auto assembly = LoadLibraryA("GameAssembly.dll");

namespace IL2CPPAPI { 
	static void Init() {

		if (!assembly) {
			Log::error("Failed to load GameAssembly.dll!");
			return;
		}

		/// !! remember to use _spoof variant of the exports !!

		/// assembly
		INIT_API(assembly, il2cpp_assembly_get_image);

		/// image
		INIT_API(assembly, il2cpp_image_get_class);

		/// domain
		INIT_API(assembly, il2cpp_domain_get);
		INIT_API(assembly, il2cpp_domain_get_assemblies);
		INIT_API(assembly, il2cpp_domain_assembly_open);

		/// class
		INIT_API(assembly, il2cpp_class_from_name);
		INIT_API(assembly, il2cpp_class_from_type);
		INIT_API(assembly, il2cpp_class_get_method_from_name);
		INIT_API(assembly, il2cpp_class_get_property_from_name);
		INIT_API(assembly, il2cpp_class_from_il2cpp_type);
		INIT_API(assembly, il2cpp_class_get_field_from_name);
		INIT_API(assembly, il2cpp_class_get_fields);
		INIT_API(assembly, il2cpp_class_get_properties);
		INIT_API(assembly, il2cpp_class_get_name);
		INIT_API(assembly, il2cpp_class_get_image);
		INIT_API(assembly, il2cpp_class_get_methods);

		/// field
		INIT_API(assembly, il2cpp_field_get_name);
		INIT_API(assembly, il2cpp_field_get_value);
		INIT_API(assembly, il2cpp_field_get_value_object);
		INIT_API(assembly, il2cpp_field_get_type);
		INIT_API(assembly, il2cpp_field_set_value);
		INIT_API(assembly, il2cpp_field_set_value_object);

		INIT_API(assembly, il2cpp_field_static_get_value);
		INIT_API(assembly, il2cpp_field_static_set_value);


		/// property
		INIT_API(assembly, il2cpp_property_get_name);

		/// method
		INIT_API(assembly, il2cpp_method_get_name);
		INIT_API(assembly, il2cpp_method_get_return_type);

		/// type
		INIT_API(assembly, il2cpp_type_get_type);
		INIT_API(assembly, il2cpp_type_get_name);
		INIT_API(assembly, il2cpp_type_get_object);

		/// runtime
		INIT_API(assembly, il2cpp_runtime_invoke);
		INIT_API(assembly, il2cpp_runtime_invoke_convert_args);
		INIT_API(assembly, il2cpp_runtime_object_init);

		/// string
		INIT_API(assembly, il2cpp_string_new);

		/// thread
		INIT_API(assembly, il2cpp_thread_attach);

		/// object
		INIT_API(assembly, il2cpp_object_new);
		INIT_API(assembly, il2cpp_object_unbox);
		INIT_API(assembly, il2cpp_object_get_class);
		INIT_API(assembly, il2cpp_value_box);

		/// exception
		INIT_API(assembly, il2cpp_raise_exception);
		INIT_API(assembly, il2cpp_get_exception_argument_null);
	}

	void Scan();
}

uintptr_t cleanDomainAddress = 0x0;
//uintptr_t cleanMethodsAddress = 0x0;
uintptr_t cleanThreadAddress = 0x0;
uintptr_t cleanGetMethodPointerAddress = 0x0;
uintptr_t cleanGetMethodInfoAddress = 0x0;
uintptr_t cleanGetVirtualMethod = 0x0;
//uintptr_t cleanRuntimeInvokeAddress = 0x0;

void IL2CPPAPI::Scan() {

	uint64_t* domainScanResult = PatternScan<uint64_t*>("48 83 EC ? 48 63 05 ? ? ? ? 48 8D 0D ? ? ? ? 48 8D 15 ? ? ? ? 8B 0C 08 48 8B 44 24 ? 48 C1 E1 ? 48 03 CA 48 3B C1 73 ? 48 8B 44 24 ? 48 3B C2 73 ? 4C 8B 05 ? ? ? ? 49 63 40 ? 42 8B 4C 00 ? 48 8B 44 24 ? 49 8D 14 88 48 3B C2 73 ? 48 8B 44 24 ? 49 3B C0 72 ? 48 8B 05", BaseAddress, SizeOfImage);

	cleanDomainAddress = domainScanResult ? (uintptr_t)domainScanResult : (Log::error("[!] No results found for cleanDomainAddress!"), 0x0);

	uint64_t* threadScanResult = PatternScan<uint64_t*>("40 56 48 83 EC 20 48 8B F1 48 8B 0D ? ? ? ? 8B 09 FF 15 ? ? ? ? 48 85 C0 75 5F 48 89 5C 24 ? 48 89 7C 24 ? FF 15 ? ? ? ? E8 ? ? ? ? E8 ? ? ? ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B D8 E8 ? ? ? ? 48 8B D3 48 8B C8 48 8B F8 E8 ? ? ? ? 48 8B 4F 10 48 8B D6 C7 41 ? ? ? ? ? 48 8B CF E8 ? ? ? ? 48 8B 5C 24 ? 48 8B C7 48 8B 7C 24 ? 48 83 C4 20", BaseAddress, SizeOfImage);

	cleanThreadAddress = threadScanResult ? (uintptr_t)threadScanResult : (Log::error("[!] No results found for cleanThreadAddress!"), 0x0);

	//uint64_t* methodsScanResult = PatternScan<uint64_t*>("48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 4C 8B F2 48 8B F9 4C 63 15", BaseAddress, SizeOfImage);

	//cleanMethodsAddress = methodsScanResult ? (uintptr_t)methodsScanResult : (Log::error("[!] No results found for cleanMethodsAddress!"), 0x0);

	uint64_t* methodPointerScanResult = PatternScan<uint64_t*>("48 83 EC ?? 44 8B CA 4C 8B D1", BaseAddress, SizeOfImage);

	cleanGetMethodPointerAddress = methodPointerScanResult ? (uintptr_t)methodPointerScanResult : (Log::error("[!] No results found for cleanGetMethodPointerAddress!"), 0x0);

	/// why does this signature rotate every update lmao
	uint64_t* methodInfoScanResult = PatternScan<uint64_t*>("48 89 5C 24 ? 57 48 83 EC ? 48 8B 82 ? ? ? ? 48 8B F9 8B 40 ? 41 03 C0 4C 8B 05", BaseAddress, SizeOfImage);

	if (!methodInfoScanResult)
		methodInfoScanResult = PatternScan<uint64_t*>("48 89 5C 24 ? 57 48 83 EC ? 48 8B 42 ? 48 8B F9 8B 40 ? 41 03 C0 4C 8B 05", BaseAddress, SizeOfImage);

	cleanGetMethodInfoAddress = methodInfoScanResult ? (uintptr_t)methodInfoScanResult : (Log::error("[!] No results found for cleanGetMethodInfoAddress!"), 0x0);

	uint64_t* virtualMethodScanResult = PatternScan<uint64_t*>("40 55 41 56 41 57 48 83 EC 50 48 8D 6C 24 ? 44 0F B6 71 ? 49 FF C6 48 89 5D 50 48", BaseAddress, SizeOfImage);

	cleanGetVirtualMethod = virtualMethodScanResult ? (uintptr_t)virtualMethodScanResult : (Log::error("[!] No results found for cleanGetVirtualMethod!"), 0x0);

	/// mocha only below

	//uint64_t* runtimeInvokeScanResult = PatternScan<uint64_t*>("48 89 5C 24 ? 48 89 74 24 ? 4C 89 4C 24 ? 57 48 83 EC ? 49 8B F8", BaseAddress, SizeOfImage);

	//cleanRuntimeInvokeAddress = runtimeInvokeScanResult ? (uintptr_t)runtimeInvokeScanResult : (Log::error("[!] No results found for cleanRuntimeInvokeAddress!"), 0x0);

	Log::debug("Il2Cpp scans complete.");

	return;
}

Il2CppDomain* s_Domain{ nullptr };

typedef Il2CppDomain* (*il2cpp_domain_get_clean_t)();
Il2CppDomain* il2cpp_domain_get_clean() {
	il2cpp_domain_get_clean_t domain_get_clean = (il2cpp_domain_get_clean_t)reinterpret_cast<void*>(cleanDomainAddress);
	if (!s_Domain) // why? view il2cpp_domain_get source code
	{
		s_Domain = spoof_call(returnSpoofAddress, domain_get_clean);
	}
	return s_Domain;
}

typedef Il2CppThread* (*il2cpp_thread_attach_clean_t)(Il2CppDomain* domain);
Il2CppThread* il2cpp_thread_attach_clean(Il2CppDomain* domain) {

	il2cpp_thread_attach_clean_t thread_attach_clean = (il2cpp_thread_attach_clean_t)reinterpret_cast<void*>(cleanThreadAddress);

	return spoof_call(returnSpoofAddress, thread_attach_clean, domain);
}

typedef const MethodInfo* (*il2cpp_class_get_methods_clean_t)(Il2CppClass* klass, void** iter);
const MethodInfo* il2cpp_class_get_methods_clean(Il2CppClass* klass, void** iter) {

	return spoof_call(returnSpoofAddress, il2cpp_class_get_methods, klass, iter);
}

typedef void* (__fastcall* GetMethodInfo_t)(Il2CppMetadataMethodInfo* methodInfo, Il2CppClass* klass, int index);
void* GetMethodInfo(Il2CppMetadataMethodInfo* methodInfo, Il2CppClass* klass, int index) {
	const auto func = (GetMethodInfo_t)reinterpret_cast<void*>(cleanGetMethodInfoAddress);
	return func(methodInfo, klass, index);
}

typedef Il2CppMethodPointer(*GetMethodPointer_t)(const Il2CppImage* klassImage, uint32_t methodToken);
Il2CppMethodPointer GetMethodPointer(const Il2CppImage* klassImage, uint32_t methodToken) {
	const auto func = (GetMethodPointer_t)reinterpret_cast<void*>(cleanGetMethodPointerAddress);
	return func(klassImage, methodToken);
}

typedef Il2CppMethodPointer(*GetVirtualMethod_t)(const MethodInfo* method);
Il2CppMethodPointer GetVirtualMethod(const MethodInfo* method) {
	const auto func = (GetVirtualMethod_t)reinterpret_cast<void*>(cleanGetVirtualMethod);
	return func(method);
}

/*typedef Il2CppObject* (*CleanRuntimeInvoke_t)(const MethodInfo* method, void* obj, void** params, Il2CppException** exc);
Il2CppObject* CleanRuntimeInvoke(const MethodInfo* method, void* obj, void** params, Il2CppException** exc) {
	const auto func = (CleanRuntimeInvoke_t)reinterpret_cast<void*>(cleanRuntimeInvokeAddress);
	return spoof_call(returnSpoofAddress, func, method, obj, params, exc);
}*/

bool ThreadFix() {
	Il2CppThread* pAttachedThread = il2cpp_thread_attach_clean(il2cpp_domain_get_clean());
	return pAttachedThread ? true : false;
}

const Il2CppImage* il2cpp_assembly_get_image_spoof(const Il2CppAssembly* assembly) { return spoof_call(returnSpoofAddress, il2cpp_assembly_get_image, assembly); }
const Il2CppClass* il2cpp_image_get_class_spoof(const Il2CppImage* image, size_t index) { return spoof_call(returnSpoofAddress, il2cpp_image_get_class, image, index); }
const MethodInfo* il2cpp_class_get_methods_spoof(Il2CppClass* klass, void** iter) { return spoof_call(returnSpoofAddress, il2cpp_class_get_methods, klass, iter); }
const MethodInfo* il2cpp_class_get_method_from_name_spoof(Il2CppClass* klass, const char* name, int argsCount) { return spoof_call(returnSpoofAddress, il2cpp_class_get_method_from_name, klass, name, argsCount); }
const Il2CppAssembly** il2cpp_domain_get_assemblies_spoof(const Il2CppDomain* domain, size_t* size) { return spoof_call(returnSpoofAddress, il2cpp_domain_get_assemblies, domain, size); }
const Il2CppAssembly* il2cpp_domain_assembly_open_spoof(Il2CppDomain* domain, const char* name) { return spoof_call(returnSpoofAddress, il2cpp_domain_assembly_open, domain, name); }
Il2CppClass* il2cpp_class_from_name_spoof(const Il2CppImage* image, const char* namespaze, const char* name) { return spoof_call(returnSpoofAddress, il2cpp_class_from_name, image, namespaze, name); }
Il2CppClass* il2cpp_class_from_type_spoof(const Il2CppType* type) { return spoof_call(returnSpoofAddress, il2cpp_class_from_type, type); }
const PropertyInfo* il2cpp_class_get_property_from_name_spoof(Il2CppClass* klass, const char* name) { return spoof_call(returnSpoofAddress, il2cpp_class_get_property_from_name, klass, name); }
Il2CppClass* il2cpp_class_from_il2cpp_type_spoof(const Il2CppType* type) { return spoof_call(returnSpoofAddress, il2cpp_class_from_il2cpp_type, type); }
FieldInfo* il2cpp_class_get_field_from_name_spoof(Il2CppClass* klass, const char* name) { return spoof_call(returnSpoofAddress, il2cpp_class_get_field_from_name, klass, name); }
FieldInfo* il2cpp_class_get_fields_spoof(Il2CppClass* klass, void** iter) { return spoof_call(returnSpoofAddress, il2cpp_class_get_fields, klass, iter); }
const PropertyInfo* il2cpp_class_get_properties_spoof(Il2CppClass* klass, void** iter) { return spoof_call(returnSpoofAddress, il2cpp_class_get_properties, klass, iter); }
const char* il2cpp_field_get_name_spoof(FieldInfo* field) { return spoof_call(returnSpoofAddress, il2cpp_field_get_name, field); }
void il2cpp_field_get_value_spoof(Il2CppObject* obj, FieldInfo* field, void* value) { return spoof_call(returnSpoofAddress, il2cpp_field_get_value, obj, field, value); }
void il2cpp_field_static_get_value_spoof(FieldInfo* field, void* value) { return spoof_call(returnSpoofAddress, il2cpp_field_static_get_value, field, value); }
Il2CppObject* il2cpp_field_get_value_object_spoof(FieldInfo* field, Il2CppObject* obj) { return spoof_call(returnSpoofAddress, il2cpp_field_get_value_object, field, obj); }
const Il2CppType* il2cpp_field_get_type_spoof(FieldInfo* field) { return spoof_call(returnSpoofAddress, il2cpp_field_get_type, field); }
void il2cpp_field_set_value_spoof(Il2CppObject* obj, FieldInfo* field, void* value) { return spoof_call(returnSpoofAddress, il2cpp_field_set_value, obj, field, value); }
void il2cpp_field_static_set_value_spoof(FieldInfo* field, void* value) { return spoof_call(returnSpoofAddress, il2cpp_field_static_set_value, field, value); }
void il2cpp_field_set_value_object_spoof(Il2CppObject* instance, FieldInfo* field, Il2CppObject* value) { return spoof_call(returnSpoofAddress, il2cpp_field_set_value_object, instance, field, value); }
const char* il2cpp_property_get_name_spoof(PropertyInfo* prop) { return spoof_call(returnSpoofAddress, il2cpp_property_get_name, prop); }
const char* il2cpp_method_get_name_spoof(const MethodInfo* method) { return spoof_call(returnSpoofAddress, il2cpp_method_get_name, method); }
const Il2CppType* il2cpp_method_get_return_type_spoof(const MethodInfo* method) { return spoof_call(returnSpoofAddress, il2cpp_method_get_return_type, method); }
int il2cpp_type_get_type_spoof(const Il2CppType* type) { return spoof_call(returnSpoofAddress, il2cpp_type_get_type, type); }
char* il2cpp_type_get_name_spoof(const Il2CppType* type) { return spoof_call(returnSpoofAddress, il2cpp_type_get_name, type); }
Il2CppObject* il2cpp_type_get_object_spoof(const Il2CppType* type) { return spoof_call(returnSpoofAddress, il2cpp_type_get_object, type); }
Il2CppObject* il2cpp_runtime_invoke_spoof(const MethodInfo* method, void* obj, void** params, Il2CppException** exc) { return spoof_call(returnSpoofAddress, il2cpp_runtime_invoke, method, obj, params, exc); }
Il2CppObject* il2cpp_runtime_invoke_convert_args_spoof(const MethodInfo* method, void* obj, Il2CppObject** params, int paramCount, Il2CppException** exc) { return spoof_call(returnSpoofAddress, il2cpp_runtime_invoke_convert_args, method, obj, params, paramCount, exc); }
Il2CppString* il2cpp_string_new_spoof(const char* str) { return spoof_call(returnSpoofAddress, il2cpp_string_new, str); }
Il2CppObject* il2cpp_value_box_spoof(Il2CppClass* klass, void* data) { return spoof_call(returnSpoofAddress, il2cpp_value_box, klass, data); }
Il2CppObject* il2cpp_object_new_spoof(const Il2CppClass* klass) { return spoof_call(returnSpoofAddress, il2cpp_object_new, klass); }
void* il2cpp_object_unbox_spoof(Il2CppObject* obj) { return spoof_call(returnSpoofAddress, il2cpp_object_unbox, obj); }
void il2cpp_runtime_object_init_spoof(Il2CppObject* obj) { return spoof_call(returnSpoofAddress, il2cpp_runtime_object_init, obj); }
const Il2CppImage* il2cpp_class_get_image_spoof(Il2CppClass* klass) { return spoof_call(returnSpoofAddress, il2cpp_class_get_image, klass); }
Il2CppClass* il2cpp_object_get_class_spoof(Il2CppObject* object) { return spoof_call(returnSpoofAddress, il2cpp_object_get_class, object); }
const char* il2cpp_class_get_name_spoof(Il2CppClass* klass) { return spoof_call(returnSpoofAddress, il2cpp_class_get_name, klass); }
void il2cpp_raise_exception_spoof(Il2CppException* exception) { return spoof_call(returnSpoofAddress, il2cpp_raise_exception, exception); }
Il2CppException* il2cpp_get_exception_argument_null_spoof(const char* arg) { return spoof_call(returnSpoofAddress, il2cpp_get_exception_argument_null, arg); }

__declspec(noinline) void* FindMethod(const char* assemblyName, const char* namespaceName, const char* className, const char* methodName, int methodArgsCount, int index) {
	
	auto pAssembly = [&]() -> const Il2CppAssembly* { return il2cpp_domain_assembly_open_spoof(il2cpp_domain_get_clean(), assemblyName); }(); // initializing this in the pClass lambda didn't work for some reason

	auto pClass = [&]() -> Il2CppClass* { return pAssembly ? il2cpp_class_from_name_spoof(il2cpp_assembly_get_image_spoof(il2cpp_domain_assembly_open_spoof(il2cpp_domain_get_clean(), assemblyName)), namespaceName, className) : nullptr; }();
	Il2CppMetadataMethodInfo methodInfo;

	bool good = false;
	
	if (index == 0 && pClass != nullptr)
	{
		//Log::debug("coonInitialize()14222");
		int i = 0;
		void* methodsIterator = nullptr;
		MethodInfo* method = nullptr;

		while ((method = const_cast<MethodInfo*>(il2cpp_class_get_methods_clean(pClass, &methodsIterator))) != nullptr)
		{
			//Log::debug("coonInitialize()142221");
			Il2CppMetadataMethodInfo methodInfoFind;
			
			spoof_call(returnSpoofAddress, GetMethodInfo, &methodInfoFind, pClass, i);

			std::string methodNewName = methodInfoFind.name;

			i++;

			if (methodNewName == std::string(methodName))
			{

				methodInfo = methodInfoFind;
				good = true;
				break;
			}
		}
	}
	else if (pClass != nullptr)
	{
		//Log::debug("coonInitialize()1411111");
		int i = 0;
		void* methodsIterator = nullptr;
		MethodInfo* method = nullptr;
		std::vector<Il2CppMetadataMethodInfo> metadataMethodInfo;
		while ((method = const_cast<MethodInfo*>(il2cpp_class_get_methods_clean(pClass, &methodsIterator))) != nullptr)
		{
			Il2CppMetadataMethodInfo methodInfoFind;

			spoof_call(returnSpoofAddress, GetMethodInfo, &methodInfoFind, pClass, i);

			std::string methodNewName = methodInfoFind.name;

			i++;

			if (methodNewName == std::string(methodName))
			{
				metadataMethodInfo.push_back(methodInfoFind);
			}
		}

		methodInfo = metadataMethodInfo.at(index);
		good = true;
	}

	
	const Il2CppImage* image = il2cpp_class_get_image_spoof(pClass);

	Il2CppMethodPointer methodPointer = nullptr;

	if (good)
	{
		methodPointer = spoof_call(returnSpoofAddress, GetMethodPointer, image, methodInfo.token);
	}

	return methodPointer ? methodPointer : [&]() -> void* { Log::error("No MethodInfo* found for: " + std::string(methodName) + "!"); return nullptr; } ();
}

__declspec(noinline) void* FindMethodOverload(const char* assemblyName, const char* namespaceName, const char* className, const char* methodName, int methodArgsCount, int index) {

	auto pAssembly = [&]() -> const Il2CppAssembly* { return il2cpp_domain_assembly_open_spoof(il2cpp_domain_get_clean(), assemblyName); }(); // initializing this in the pClass lambda didn't work for some reason

	auto pClass = [&]() -> Il2CppClass* { return pAssembly ? il2cpp_class_from_name_spoof(il2cpp_assembly_get_image_spoof(il2cpp_domain_assembly_open_spoof(il2cpp_domain_get_clean(), assemblyName)), namespaceName, className) : nullptr; }();

	Il2CppMetadataMethodInfo methodInfo;

	bool good = false;
	
	if (index == 0)
	{
		int i = 0;
		void* methodsIterator = nullptr;
		MethodInfo* method = nullptr;
		while ((method = const_cast<MethodInfo*>(il2cpp_class_get_methods_clean(pClass, &methodsIterator))) != nullptr)
		{
			Il2CppMetadataMethodInfo methodInfoFind;

			spoof_call(returnSpoofAddress, GetMethodInfo, &methodInfoFind, pClass, i);

			std::string methodNewName = methodInfoFind.name;

			i++;

			if ((methodNewName == std::string(methodName)) && (methodInfoFind.parameterCount == methodArgsCount))
			{
				methodInfo = methodInfoFind;
				good = true;
				break;
			}
		}
	}
	else
	{
		int i = 0;
		void* methodsIterator = nullptr;
		MethodInfo* method = nullptr;
		std::vector<Il2CppMetadataMethodInfo> metadataMethodInfo;
		while ((method = const_cast<MethodInfo*>(il2cpp_class_get_methods_clean(pClass, &methodsIterator))) != nullptr)
		{
			Il2CppMetadataMethodInfo methodInfoFind;

			spoof_call(returnSpoofAddress, GetMethodInfo, &methodInfoFind, pClass, i);

			std::string methodNewName = methodInfoFind.name;

			i++;

			if ((methodNewName == std::string(methodName)) && (methodInfoFind.parameterCount == methodArgsCount))
			{
				metadataMethodInfo.push_back(methodInfoFind);
			}
		}

		methodInfo = metadataMethodInfo.at(index);
		good = true;
	}

	const Il2CppImage* image = il2cpp_class_get_image_spoof(pClass);

	Il2CppMethodPointer methodPointer = nullptr;

	if (good)
	{
		methodPointer = spoof_call(returnSpoofAddress, GetMethodPointer, image, methodInfo.token);
	}

	return methodPointer ? methodPointer : [&]() -> void* { Log::error("No MethodInfo* overload found for: " + std::string(methodName) + "!"); return nullptr; } ();
}

__declspec(noinline) void* FindKlass(const char* assemblyName, const char* namespaceName, const char* className) { // doesn't support overloads yet uhg

	auto pAssembly = [&]() -> const Il2CppAssembly* { return il2cpp_domain_assembly_open_spoof(il2cpp_domain_get_clean(), assemblyName); }(); // initializing this in the pClass lambda didn't work for some reason

	auto pClass = [&]() -> Il2CppClass* { return pAssembly ? il2cpp_class_from_name_spoof(il2cpp_assembly_get_image_spoof(il2cpp_domain_assembly_open_spoof(il2cpp_domain_get_clean(), assemblyName)), namespaceName, className) : nullptr; }();

	return pClass;
}

// so we can multi-thread using the AEAC.dll (Async-EAC)
uintptr_t threadAddr = 0x0;

typedef void (*newThread_t)(void* funcaddr, void* args);
void newThread(void* funcaddr, void* args) {
	const auto func = (newThread_t)threadAddr;
	return func(funcaddr, args);
}