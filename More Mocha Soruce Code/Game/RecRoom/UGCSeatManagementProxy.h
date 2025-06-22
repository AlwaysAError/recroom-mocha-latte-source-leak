#pragma once

struct UGCSeatManagement : MonoBehaviourPun {

	typedef void (*CV2SetSeatedPlayer_t)(UGCSeatManagement* instance, ExecParams* exec, RecRoomPlayer* target);
	void CV2SetSeatedPlayer(RecRoomPlayer* target) {
		const auto func = (CV2SetSeatedPlayer_t)(methods::UGCSeatManagement::CV2SetSeatedPlayer);

		return func(this, ExecParams::get_ExecParams(), target);
	}

	typedef void (*set_LockPlayersIn_t)(UGCSeatManagement* instance, bool value);
	void set_LockPlayersIn(bool value) { // inherited from SeatManagement class
		const auto func = (set_LockPlayersIn_t)(GameAssembly + 0x15DEF40);

		return func(this, value);
	}

	typedef void (*set_LockPlayersOut_t)(UGCSeatManagement* instance, bool value);
	void set_LockPlayersOut(bool value) { // inherited from SeatManagement class, obfuscated below get_LockPlayersOut
		const auto func = (set_LockPlayersOut_t)(GameAssembly + 0x15DC900);

		return func(this, value);
	}

	typedef void (*SeatCollisionEnabled_Set_t)(UGCSeatManagement* instance, bool value);
	void SeatCollisionEnabled_Set(bool value) {
		const auto func = (SeatCollisionEnabled_Set_t)(GameAssembly + 0x15E0880);

		return func(this, value);
	}

};

struct UGCSeatManagementProxy : MonoBehaviour {

	typedef UGCSeatManagement* (*get_UgcSeatManagement_t)(UGCSeatManagementProxy* instance);
	UGCSeatManagement* get_UgcSeatManagement() {
		const auto func = (get_UgcSeatManagement_t)(GameAssembly + 0x9FA770);
		return func(this);
	}

};

struct MoveableProp : MonoBehaviourPun {

	typedef void (*ForceSetLocomotionCollisionEnabled_t)(MoveableProp* instance, bool value);
	void ForceSetLocomotionCollisionEnabled(bool value) {
		const auto func = (ForceSetLocomotionCollisionEnabled_t)(GameAssembly + 0x13B8FA0);
		return func(this, value);
	}

};