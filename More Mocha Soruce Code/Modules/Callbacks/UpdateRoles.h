#pragma once

bool FindPlayerRoomRoleManager() {

	Il2CppArray* objects = UObject::FindObjectsOfType("UnityEngine.GameObject");

	for (int i = 0; i < objects->max_length; i++) {
		GameObject* gameObject = il2cpp_array_get(objects, GameObject*, i);

		if (gameObject != nullptr) {
			Component* PlayerRoomRoleManager = (Component*)gameObject->GetComponent("RecRoom.Systems.PlayerRoles.PlayerRoomRoleManager");

			if (PlayerRoomRoleManager != nullptr) {
				globals::cachedPlayerRoomRoleManager = PlayerRoomRoleManager;
				return true;
			}
		}
	}

	return false;
}

void RpcModifyRoleDefinitionForAll(RoleId roleId, const int gameRolePermission, const bool enabled, const bool roomRole = false) {
	
	auto* objectType = (Type*)Type::getType(il2cpp_string_new_spoof("System.Object"));
	auto* byteType = (Type*)Type::getType(il2cpp_string_new_spoof("System.Byte"));

	// this works cuz both are enums - genesis
	INT32 roleIdVar = (INT32)roleId;
	INT32 rolePermissionvar = (INT32)gameRolePermission;

	Il2CppObject* roleIdObject = il2cpp_value_box_spoof(FindClass("System.Int32"), &roleIdVar);
	Il2CppObject* rolePermissionObject = il2cpp_value_box_spoof(FindClass("System.Int32"), &rolePermissionvar);

	Il2CppArray* byteArray;

	if (enabled) {
		byteArray = Array::createInstance(byteType, 4);
		il2cpp_array_set(byteArray, uint8_t, 0, 8);
		il2cpp_array_set(byteArray, uint8_t, 1, 1);
		il2cpp_array_set(byteArray, uint8_t, 2, 16);
		il2cpp_array_set(byteArray, uint8_t, 3, 8);
	}
	else {
		byteArray = Array::createInstance(byteType, 2);
		il2cpp_array_set(byteArray, uint8_t, 0, 8);
		il2cpp_array_set(byteArray, uint8_t, 1, 1);
	}

	Il2CppArray* payloadArray = Array::createInstance(objectType, 3);
	il2cpp_array_set(payloadArray, Il2CppObject*, 0, roleIdObject);
	il2cpp_array_set(payloadArray, Il2CppObject*, 1, rolePermissionObject);
	il2cpp_array_set(payloadArray, Il2CppObject*, 2, byteArray);

	Component* PlayerRoleManager = nullptr;

	if (roomRole) {
		PlayerRoleManager = (Component*)globals::cachedPlayerRoomRoleManager;
	}
	else {
		PlayerRoleManager = (Component*)PlayerGameRoleManager::get_Instance();
	}

	if (PlayerRoleManager != nullptr) {
		
		if (GameObject* GameRoleManagerGO = PlayerRoleManager->get_gameObject()) {
			if (auto* photonCuntView = static_cast<PhotonView*>(GameRoleManagerGO->GetComponent("PhotonView")))
				photonCuntView->SendRPC("RpcModifyRoleDefinition", All, payloadArray);
		}
	}
}

void RpcModifyRoleDefinition(PhotonPlayer* targetPP, RoleId roleId, const int gameRolePermission, const bool enabled, const bool roomRole = false) {
	
	auto* objectType = (Type*)Type::getType(il2cpp_string_new_spoof("System.Object"));
	auto* byteType = (Type*)Type::getType(il2cpp_string_new_spoof("System.Byte"));

	// this works cuz both are enums - genesis
	INT32 roleIdVar = (INT32)roleId;
	INT32 rolePermissionvar = (INT32)gameRolePermission;

	Il2CppObject* roleIdObject = il2cpp_value_box_spoof(FindClass("System.Int32"), &roleIdVar);
	Il2CppObject* rolePermissionObject = il2cpp_value_box_spoof(FindClass("System.Int32"), &rolePermissionvar);

	Il2CppArray* byteArray;

	if (enabled) {
		byteArray = Array::createInstance(byteType, 4);
		il2cpp_array_set(byteArray, uint8_t, 0, 8);
		il2cpp_array_set(byteArray, uint8_t, 1, 1);
		il2cpp_array_set(byteArray, uint8_t, 2, 16);
		il2cpp_array_set(byteArray, uint8_t, 3, 8);
	}
	else {
		byteArray = Array::createInstance(byteType, 2);
		il2cpp_array_set(byteArray, uint8_t, 0, 8);
		il2cpp_array_set(byteArray, uint8_t, 1, 1);
	}
	
	Il2CppArray* payloadArray = Array::createInstance(objectType, 3);
	il2cpp_array_set(payloadArray, Il2CppObject*, 0, roleIdObject);
	il2cpp_array_set(payloadArray, Il2CppObject*, 1, rolePermissionObject);
	il2cpp_array_set(payloadArray, Il2CppObject*, 2, byteArray);
	
	Component* PlayerRoleManager = nullptr;

	if (roomRole) {
		PlayerRoleManager = (Component*)globals::cachedPlayerRoomRoleManager;
	}
	else {
		PlayerRoleManager = (Component*)PlayerGameRoleManager::get_Instance();
	}

	if (PlayerRoleManager != nullptr) {
		
		if (GameObject* GameRoleManagerGO = PlayerRoleManager->get_gameObject()) {
			if (auto* photonCuntView = static_cast<PhotonView*>(GameRoleManagerGO->GetComponent("PhotonView")))
				photonCuntView->SendRPC("RpcModifyRoleDefinition", targetPP, payloadArray);
		}
	}
}

namespace Callbacks
{
	bool UpdateRolesTarget(PhotonPlayer* targetPP) {

		if (!globals::inPromotion)
		{
			if (targetPP != nullptr && localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED) {

				if (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer)) {
					if (!PhotonNetwork::set_MasterClient(localPlayer.photonPlayer)) {
						Log::error("Failed to set master client for: " + std::string(localPlayer.DisplayName));
						return false;
					}
				}

				globals::inPromotion = true;
				
				RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)GameRolePermission::CAN_MOVE, true);
				RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)GameRolePermission::CAN_FLY, true);
				RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)GameRolePermission::IS_INVINCIBLE, true);
				RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)GameRolePermission::CAN_SWITCH_TEAMS, true);
				RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)GameRolePermission::VR_CAN_JUMP, true);
				RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)GameRolePermission::VR_CAN_DODGE, true);
				RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)GameRolePermission::SCREENS_CAN_JUMP, true);
				RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)GameRolePermission::SCREENS_CAN_DODGE, true);
				RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)GameRolePermission::SCREENS_CAN_WALL_RUN, true);
				RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)GameRolePermission::VR_CAN_WALL_RUN, true);
				RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)GameRolePermission::VR_CAN_GET_PUSHED, false);
				RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)GameRolePermission::SCREENS_CAN_GET_PUSHED, false);
				RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)GameRolePermission::VR_CAN_RAM, true);
				RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)GameRolePermission::SCREENS_CAN_RAM, true);
				RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)GameRolePermission::CAN_ALWAYS_SPRINT, true);
				RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)GameRolePermission::CAN_CLAMBER, true);
				RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)GameRolePermission::CAN_USE_MAKER_PEN, true);
				RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)GameRolePermission::CAN_SAVE_INVENTIONS, true);
				RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)GameRolePermission::CAN_SPAWN_INVENTIONS, true);
				RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)GameRolePermission::CAN_USE_ROOM_RESET_BUTTON, true);
				RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)GameRolePermission::CAN_USE_DELETE_ALL_BUTTON, true);
				RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)GameRolePermission::CAN_CREATE_ROLE_ASSIGNMENT_CHIPS, true);
				RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)GameRolePermission::CAN_USE_PLAY_GIZMOS_TOGGLE, true);

				// using AG_EVERYONE works on room roles cuz 0 
				// is everyone role anyways but roleids are different otherwise
				if (globals::roomRolePromotion) {
					if (FindPlayerRoomRoleManager()) {
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_EDIT_ROOM_ROLES, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_INVITE, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_TALK, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_PRINT_PHOTOS, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_START_GAMES, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_SELF_REVIVE, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_CHANGE_GAME_MODE, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_USE_MAKER_PEN, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_USE_DELETE_ALL_BUTTON, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_SAVE_INVENTIONS, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::DISABLE_MIC_AUTO_MUTE, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_END_GAMES_EARLY, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_USE_SHARE_CAM, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_SPAWN_INVENTIONS, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_SPAWN_CONSUMABLES, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_USE_ROOM_RESET_BUTTON, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_USE_PLAY_GIZMOS_TOGGLE, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_USE_RRS, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_SAVE_ROOM, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_PUBLISH_ROOM, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_CLONE_ROOM, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_RESTORE_ROOM, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_EDIT_MAIN_ROOM_SETTINGS, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_EDIT_ROOM_ECON_SETTINGS, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_CREATE_SUBROOMS, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_NAME_SUBROOMS, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_CLONE_SUBROOMS, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_EDIT_ROOM_ROLES, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_MOVE_SUBROOMS, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_DELETE_SUBROOMS, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_EDIT_SUBROOM_SETTINGS, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_RESET_CLOUD_VARIABLES, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_DELETE_CLOUD_VARIABLES, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_EDIT_ROOM_PROGRESSION, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_REMOVE_ROOM_BANS, true, true);
						RpcModifyRoleDefinition(targetPP, RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_ADD_ROOM_BANS, true, true);
					}
					else {
						Log::error("Failed to find PlayerRoomRoleManager!");
					}
				}
			}
		}

		globals::inPromotion = false;
		return true;
	}

	bool UpdateRolesAll()
	{
		if (!globals::inPromotion) {

			if (localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED) {

				if (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer)) {
					if (!PhotonNetwork::set_MasterClient(localPlayer.photonPlayer)) {
						Log::error("Failed to set master client for: " + std::string(localPlayer.DisplayName));
						return false;
					}
				}
			
				globals::inPromotion = true;

				RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)GameRolePermission::CAN_MOVE, true);
				RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)GameRolePermission::CAN_FLY, true);
				RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)GameRolePermission::IS_INVINCIBLE, true);
				RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)GameRolePermission::CAN_SWITCH_TEAMS, true);
				RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)GameRolePermission::VR_CAN_JUMP, true);
				RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)GameRolePermission::VR_CAN_DODGE, true);
				RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)GameRolePermission::SCREENS_CAN_JUMP, true);
				RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)GameRolePermission::SCREENS_CAN_DODGE, true);
				RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)GameRolePermission::SCREENS_CAN_WALL_RUN, true);
				RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)GameRolePermission::VR_CAN_WALL_RUN, true);
				RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)GameRolePermission::VR_CAN_GET_PUSHED, false);
				RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)GameRolePermission::SCREENS_CAN_GET_PUSHED, false);
				RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)GameRolePermission::VR_CAN_RAM, true);
				RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)GameRolePermission::SCREENS_CAN_RAM, true);
				RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)GameRolePermission::CAN_ALWAYS_SPRINT, true);
				RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)GameRolePermission::CAN_CLAMBER, true);
				RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)GameRolePermission::CAN_USE_MAKER_PEN, true);
				RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)GameRolePermission::CAN_SAVE_INVENTIONS, true);

				// using AG_EVERYONE works on room roles cuz 0 
				// is everyone role anyways but roleids are different otherwise
				if (globals::roomRolePromotion) {
					if (FindPlayerRoomRoleManager()) {
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_EDIT_ROOM_ROLES, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_INVITE, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_TALK, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_PRINT_PHOTOS, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_START_GAMES, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_SELF_REVIVE, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_CHANGE_GAME_MODE, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_USE_MAKER_PEN, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_USE_DELETE_ALL_BUTTON, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_SAVE_INVENTIONS, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::DISABLE_MIC_AUTO_MUTE, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_END_GAMES_EARLY, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_USE_SHARE_CAM, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_SPAWN_INVENTIONS, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_SPAWN_CONSUMABLES, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_USE_ROOM_RESET_BUTTON, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_USE_PLAY_GIZMOS_TOGGLE, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_USE_RRS, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_SAVE_ROOM, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_PUBLISH_ROOM, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_CLONE_ROOM, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_RESTORE_ROOM, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_EDIT_MAIN_ROOM_SETTINGS, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_EDIT_ROOM_ECON_SETTINGS, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_CREATE_SUBROOMS, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_NAME_SUBROOMS, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_CLONE_SUBROOMS, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_EDIT_ROOM_ROLES, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_MOVE_SUBROOMS, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_DELETE_SUBROOMS, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_EDIT_SUBROOM_SETTINGS, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_RESET_CLOUD_VARIABLES, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_DELETE_CLOUD_VARIABLES, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_EDIT_ROOM_PROGRESSION, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_REMOVE_ROOM_BANS, true, true);
						RpcModifyRoleDefinitionForAll(RoleId::AG_EVERYONE, (int)RoomRolePermission::CAN_ADD_ROOM_BANS, true, true);
					}
					else {
						Log::error("Failed to find PlayerRoomRoleManager component!");
					}
				}
			}
		}
		
		globals::inPromotion = false;
		return true;
	}
}