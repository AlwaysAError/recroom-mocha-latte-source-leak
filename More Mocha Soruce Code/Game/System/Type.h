#pragma once

struct Type : Il2CppType {

	typedef Il2CppString* (*getComponentName_t)(Il2CppClass* klass);
	static Il2CppString* getClassName(Il2CppClass* klass) {
		const auto func = (getComponentName_t)(methods::SystemComponentModel::TypeDescriptor::getClassName);
		return func(klass);
	}

	typedef Il2CppType* (*getType_t)(Il2CppString* typeName);
	static Il2CppType* getType(Il2CppString* typeName) { // automating this one results in it always being Il2CppString* for some reason
		const auto func = (getType_t)(GameAssembly + 0x6E642D0); // \mscorlib\System\Type.h	Il2CppType* GetType(Il2CppString* typeName)
		return func(typeName);
	}

	typedef Il2CppType* (*GetType_t)(Il2CppObject* object);
	static Il2CppType* GetType(Il2CppObject* object) {
		const auto func = (GetType_t)(GameAssembly + 0x6E643D0); // \mscorlib\System\Type.h   Il2CppType* GetType()
		return func(object);
	}

	typedef Il2CppString* (*ToString_t)(Type* type);
	Il2CppString* ToString() {
		const auto func = (ToString_t)(GameAssembly + 0x6E65540); // \mscorlib\System\Type.h   Il2CppString* ToString()
		return func(this);
	}

};
