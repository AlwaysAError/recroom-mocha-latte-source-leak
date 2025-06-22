#pragma once

enum PhotonTargets {
	All = 0,
	Others = 1,
	MasterClient = 2,
	AllBuffered = 3,
	OthersBuffered = 4,
	AllViaServer = 5,
	AllBufferedViaServer = 6
};

struct PhotonView : Component {

	typedef void (*RPC_t)(PhotonView* photonView, Il2CppString* rpcEventName, PhotonTargets photonTarget, Il2CppObject* objectList);
	void RPC(Il2CppString* rpcEventName, PhotonTargets photonTarget, Il2CppObject* objectList) {
		const auto func = (RPC_t)(methods::PhotonPun::PhotonView::RPC);
		return func(this, rpcEventName, photonTarget, objectList);
	}

	typedef void (*RPC_PP_t)(PhotonView* photonView, Il2CppString* rpcEventName, PhotonPlayer* photonTarget, Il2CppObject* objectList);
	void RPC(Il2CppString* rpcEventName, PhotonPlayer* photonTarget, Il2CppObject* objectList) {
		const auto func = (RPC_PP_t)(methods::PhotonPun::PhotonView::RPC_PP);
		return func(this, rpcEventName, photonTarget, objectList);
	}

	typedef int (*get_ViewID_t)(PhotonView* photonView);
	int get_ViewID() {
		const auto func = (get_ViewID_t)(methods::PhotonPun::PhotonView::get_ViewID);
		return func(this);
	}

	typedef void (*TransferOwnership_t)(PhotonView* photonView, PhotonPlayer* newOwner);
	void TransferOwnership(PhotonPlayer* newOwner) {
		const auto func = (TransferOwnership_t)(methods::PhotonPun::PhotonView::TransferOwnership);
		return func(this, newOwner);
	}

	typedef PhotonView* (*findPhotonView_t)(int32_t viewId);
	static PhotonView* findPhotonView(const int32_t viewId) {
		const auto func = (findPhotonView_t)(methods::PhotonPun::PhotonView::findPhotonView);
		return func(viewId);
	}

	typedef PhotonPlayer* (*get_Owner_t)(PhotonView* photonView);
	PhotonPlayer* get_Owner() {
		const auto func = (get_Owner_t)(GameAssembly + 0x7169380);
		return func(this);
	}

	struct PayloadEntry {
		std::any value;
		std::string klassName = "$boxed"; // we assume the item is or inherits Il2CppObject*
	};


	static Il2CppArray* CreateRPCPayloadArray(std::vector<PayloadEntry>& payloadVector);
	
	template<typename Target>
	void SendRPC(std::string rpcEventName, Target photonTarget, std::vector<PayloadEntry>& payloadVector);
	template<typename Target>
	void SendRPC(std::string rpcEventName, Target photonTarget, Il2CppArray*& payloadArray);
};

Il2CppArray* PhotonView::CreateRPCPayloadArray(std::vector<PayloadEntry>& payloadVector)
{
	auto* objectType = (Type*)Type::getType(il2cpp_string_new_spoof("System.Object"));
	Il2CppArray* payloadArray = Array::createInstance(objectType, payloadVector.size());

	for (unsigned long long i = 0; i < payloadVector.size(); i++) {

		PayloadEntry& vectorItem = payloadVector[i];

		if (vectorItem.klassName == "$boxed") {

			auto* object = std::any_cast<Il2CppObject*>(vectorItem.value);
			il2cpp_array_set(payloadArray, Il2CppObject*, i, object); //! you will crash here if value is not a pointer

			continue;
		}

		if (Il2CppClass* klass = FindClass(vectorItem.klassName.c_str())) {

			Il2CppObject* boxedObject = il2cpp_value_box_spoof(klass, &vectorItem.value);
			il2cpp_array_set(payloadArray, Il2CppObject*, i, boxedObject);
		}
		else {
			Log::error("[CreateRPCPayloadArray] Il2CppClass* not found for: [" + vectorItem.klassName + "]!");
		}
	}

	return payloadArray;
}

template<typename Target>
void PhotonView::SendRPC(std::string rpcEventName, Target photonTarget, std::vector<PayloadEntry>& payloadVector) {

	Il2CppString* eventName = WriteIl2CppString(rpcEventName.c_str());

	Il2CppArray* payloadArray = CreateRPCPayloadArray(payloadVector);

	if constexpr (std::is_same_v<Target, PhotonTargets>) {
		const PhotonTargets target = photonTarget;
		this->RPC(eventName, target, payloadArray);
	}
	else if constexpr (std::is_same_v<Target, PhotonPlayer*>) {
		PhotonPlayer* target = photonTarget;
		this->RPC(eventName, target, payloadArray);
	}
}

template<typename Target>
void PhotonView::SendRPC(std::string rpcEventName, Target photonTarget, Il2CppArray*& payloadArray) {

	Il2CppString* eventName = WriteIl2CppString(rpcEventName.c_str());

	if constexpr (std::is_same_v<Target, PhotonTargets>) {
		const PhotonTargets target = photonTarget;
		this->RPC(eventName, target, payloadArray);
	}
	else if constexpr (std::is_same_v<Target, PhotonPlayer*>) {
		PhotonPlayer* target = photonTarget;
		this->RPC(eventName, target, payloadArray);
	}
}