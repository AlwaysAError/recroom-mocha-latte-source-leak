#pragma once

struct ShareCameraPhotonView : PhotonView {

	typedef void (*RpcPlayRemoteTakePictureFeedback_t)(ShareCameraPhotonView* instance, bool useFlash);
	void RpcPlayRemoteTakePictureFeedback(bool useFlash) {

		bool useFlashParam = useFlash;

		Il2CppString* RPCEvent = il2cpp_string_new_spoof("RpcPlayRemoteTakePictureFeedback");
		Type* objectType = (Type*)Type::getType(il2cpp_string_new_spoof("System.Object"));
		Il2CppArray* payloadArray = Array::createInstance((Il2CppType*)objectType, 1);

		Il2CppObject* useFlashObject = il2cpp_value_box_spoof(FindClass("System.Boolean"), &useFlashParam);

		il2cpp_array_set(payloadArray, Il2CppObject*, 0, (Il2CppObject*)useFlashObject);

		Il2CppObject* RPCPayload = reinterpret_cast<Il2CppObject*>(payloadArray);

		this->RPC(RPCEvent, All, RPCPayload);

		return;
	}

};