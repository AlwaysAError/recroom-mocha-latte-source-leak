#pragma once

struct MonoBehaviourPun : MonoBehaviour {

	typedef PhotonView* (*get_PhotonView_t)(MonoBehaviourPun* MonoBehaviourPun);
	PhotonView* get_PhotonView() {
		const auto func = (get_PhotonView_t)(methods::PhotonPun::MonoBehaviourPun::get_PhotonView);
		return func(this);
	}

};