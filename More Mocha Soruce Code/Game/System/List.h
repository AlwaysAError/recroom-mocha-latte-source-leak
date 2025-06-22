#pragma once

struct List : Il2CppObject {

	typedef int32_t (*get_Count_t)(List* instance);
	int32_t get_Count() {
		const auto func = (get_Count_t)(GameAssembly + 0x0); // 		METHOD(int32_t, (List*, MethodInfo*), "System.Int32 get_Count()");
		return func(this);
	}

	typedef Il2CppObject* (*get_Item_t)(List* instance, int32_t index);
	Il2CppObject* get_Item(int32_t index) {
		const auto func = (get_Item_t)(GameAssembly + 0x0); // 		METHOD(Il2CppObject*, (List*, int32_t, MethodInfo*), "System.Object System.Collections.IList.get_Item(System.Int32)");
		return func(this, index);
	}

};