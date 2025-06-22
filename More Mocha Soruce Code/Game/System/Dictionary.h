#pragma once

typedef void* (*get_Keys_t)(void* instance);
void* get_Entry(void* instance) {
	const auto func = (get_Keys_t)(GameAssembly + 0x0);
	return func(instance);
}

struct Dictionary : Il2CppObject {
private:
	typedef void* (*get_Keys_t)(Dictionary* instance);
	void* get_Keys() {
		const auto func = (get_Keys_t)(GameAssembly + 0x0);
		return func(this);
	}
	typedef void* (*GetEnumerator_t)(Dictionary* instance);
	void* GetEnumerator() {
		const auto func = (GetEnumerator_t)(GameAssembly + 0x0);
		return func(this);
	}
	typedef bool (*MoveNext_t)(Dictionary* instance);
	bool MoveNext() {
		const auto func = (MoveNext_t)(GameAssembly + 0x0);
		return func(this);
	}
public:
	template <typename TKey>
	std::vector<TKey> get_keys()
	{

	}
};


struct ValueType : Il2CppObject {};

// Vinyl's Sex Dungeon

namespace System::Collections::Generic
{
	// Name: Entry
	// Stable Name: System::Collections::Generic::Dictionary_2_Entry
	// Il2Cpp Type Name: (System.Collections.Generic.Dictionary.Entry<TKey,TValue>, mscorlib)
	// System Type Name: (System.Collections.Generic.Dictionary.Entry`2, mscorlib)
	// Actual Size: 0x0
	// ClassType: ValueType | Generic | Normal
	// Flags: NestedPrivate_AutoLayout_SequentialLayout_Class_Sealed_AnsiClass_BeforeFieldInit
	// Inheritance: System::Collections::Generic::Dictionary_2_Entry -> System::ValueType -> System::Object
	// Generic Parameters: typename TKey, typename TValue
	#define MSCORLIB_SYSTEM_COLLECTIONS_GENERIC_DICTIONARY_2_ENTRY_CLASS
	template<typename TKey, typename TValue>
	struct Dictionary_2_Entry : public ValueType
	{

	public:
		enum { IsValueType = true };
		typedef System::Collections::Generic::Dictionary_2_Entry<TKey, TValue> CPPType;
		using TKeyPointerType = std::remove_pointer<TKey>::type;
		using TValuePointerType = std::remove_pointer<TValue>::type;

		// Name: hashCode
		// Offset: [0x0]
		// Type: System.Int32
		int32_t hashCode;

		// Name: next
		// Offset: [0x0]
		// Type: System.Int32
		int32_t next;

		// Name: key
		// Offset: [0x0]
		// Type: TKey
		TKey key;
		//Il2CppObject* key;

		// Name: value
		// Offset: [0x0]
		// Type: TValue
		//Il2CppObject* value;
		TValue value;

	};

	struct Dictionary_2 : Il2CppObject
	{

		Il2CppArray*& _entries2()
		{
			return *reinterpret_cast<Il2CppArray**>(reinterpret_cast<uintptr_t>(this) + 0x18);
		}
		
		Il2CppArray* _entries()
		{
			return *reinterpret_cast<Il2CppArray**>(reinterpret_cast<uintptr_t>(this) + 0x18);
		}
	};
}
