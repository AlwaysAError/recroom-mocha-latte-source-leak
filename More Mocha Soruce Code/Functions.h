#pragma once

typedef Il2CppString* (*creatString_t)(DWORD* __this, int8_t* value, int startIndex, int length);
Il2CppString* WriteIl2CppString(const char* string) {

	const auto func = (creatString_t)(methods::System::String::CreateString);

	return func(nullptr, (int8_t*)string, 0, strlen(string));
}

char* ReadIl2CppString(Il2CppString* il2cppString) {

	if (il2cppString == nullptr) {
		return nullptr;
	}

	size_t length = static_cast<size_t>(il2cppString->length);
	const size_t bufferSize = (length + 1) * sizeof(wchar_t);
	char* internalString = new char[bufferSize];
	size_t convertedChars = 0;

	errno_t result = wcstombs_s(&convertedChars, internalString, bufferSize, reinterpret_cast<wchar_t*>(il2cppString) + 0xA, length);

	if (result != 0) {
		delete[] internalString;
		return nullptr;
	}

	return internalString;
}

std::unordered_map<std::string, Il2CppClass*> cachedClassMap;

Il2CppClass* FindClass(const char* className) {

	std::string classNameString = className;

	if (cachedClassMap.contains(classNameString))
		return cachedClassMap[classNameString];

	Il2CppDomain* pDomain = il2cpp_domain_get_clean();

	if (!pDomain) {
		Log::error("pDomain = nullptr!");
		Sleep(15000);
	}
	
	size_t m_sAssembliesCount{ 0U };

	const Il2CppAssembly** m_pAssemblies = il2cpp_domain_get_assemblies_spoof(pDomain, &m_sAssembliesCount);
	//const Il2CppAssembly** m_pAssemblies = il2cpp_domain_get_assemblies(testDomainShit22, &m_sAssembliesCount);
	if (!m_pAssemblies || 0U > m_sAssembliesCount) return nullptr;

	const char* m_pNameSpaceEnd = strrchr(className, '.');
	char* m_pNameSpace = nullptr;
	if (m_pNameSpaceEnd)
	{
		uintptr_t m_uNamespaceSize = static_cast<uintptr_t>(m_pNameSpaceEnd - className);
		m_pNameSpace = new char[m_uNamespaceSize + 1];
		memcpy(m_pNameSpace, className, m_uNamespaceSize);
		m_pNameSpace[m_uNamespaceSize] = '\0';

		className = m_pNameSpaceEnd + 1;
	}
	else
	{
		m_pNameSpace = new char[2];
		memset(m_pNameSpace, 0, 2);
	}

	Il2CppClass* classReturn = nullptr;
	for (size_t i = 0U; m_sAssembliesCount > i; ++i)
	{
		const Il2CppAssembly* m_pAssembly = m_pAssemblies[i];
		if (!m_pAssembly || !m_pAssembly->image) continue;

		classReturn = il2cpp_class_from_name_spoof(m_pAssembly->image, m_pNameSpace, className);
		if (classReturn) break;
	}
	//std::cout << "class ret" << classReturn << std::endl;
	delete[] m_pNameSpace;

	cachedClassMap[classNameString] = classReturn;
	return classReturn;
}

template <typename T>
T GetField(void* obj, std::ptrdiff_t offset) {
	return *(T*)((std::uint8_t*)obj + offset);
}

template <typename T>
void SetField(void* obj, std::ptrdiff_t offset, T val) {
	*(T*)((std::uint8_t*)obj + offset) = val;
}

template <typename T>
T GetStaticField(Il2CppClass* klass, const char* fieldName) {
	FieldInfo* staticFieldInfo = il2cpp_class_get_field_from_name_spoof(klass, fieldName);
	void* fieldValue = nullptr;
	if (staticFieldInfo != nullptr)
		il2cpp_field_static_get_value_spoof(staticFieldInfo, &fieldValue);
	return (T)fieldValue;
}

void SetStaticField(Il2CppClass* klass, const char* fieldName, void* val) {
	FieldInfo* staticFieldInfo = il2cpp_class_get_field_from_name_spoof(klass, fieldName);
	if (staticFieldInfo != nullptr)
		il2cpp_field_static_set_value_spoof(staticFieldInfo, val);
}