#pragma once

struct BaseAccountModel : MonoBehaviour {

	typedef int32_t (*get_AccountId_t)(BaseAccountModel* instance);
	int32_t get_AccountId() {
		const auto func = (get_AccountId_t)(GameAssembly + 0x2212060);
		return func(this);
	}
	
};