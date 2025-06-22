#pragma once

struct UMethodInfo;

//uintptr_t rev_method = 0x0;

namespace methods {

	namespace UnityEngine {

		namespace Transform {
			uintptr_t get_position = 0x0;
			uintptr_t set_localPosition = 0x0;
			uintptr_t get_childCount = 0x0;
			uintptr_t GetChild = 0x0;
			uintptr_t set_localScale = 0x0;
			uintptr_t SetParent = 0x0;
			uintptr_t get_localRotation = 0x0;
			uintptr_t set_localRotation = 0x0;
			uintptr_t get_parent = 0x0;
			uintptr_t Find = 0x0;
			uintptr_t get_forward = 0x0;
			uintptr_t get_localScale = 0x0;
			uintptr_t get_up = 0x0;
			uintptr_t get_right = 0x0;
			uintptr_t set_position = 0x0;
			uintptr_t get_rotation = 0x0;
			uintptr_t set_rotation = 0x0;
		}

		namespace Object {
			uintptr_t GetName = 0x0;
			uintptr_t FindObjectsOfType = 0x0;
			uintptr_t set_name = 0x0;
			uintptr_t Destroy = 0x0;
			uintptr_t ToString = 0x0;
		}

		namespace Physics {
			uintptr_t set_gravity = 0x0;
			uintptr_t get_gravity = 0x0;
		}

		namespace GameObject {
			uintptr_t get_transform = 0x0;
			uintptr_t GetComponents = 0x0;
			uintptr_t GetComponent = 0x0;
			uintptr_t get_active = 0x0;
			uintptr_t set_active = 0x0;
			uintptr_t AddComponent = 0x0;
			uintptr_t Find = 0x0;
			uintptr_t CreatePrimitive = 0x0;
			uintptr_t ctor = 0x0;
			uintptr_t set_layer = 0x0;
			uintptr_t get_layer = 0x0;
		}

		namespace Component {
			uintptr_t get_transform = 0x0;
			uintptr_t get_gameObject = 0x0;
		}

		namespace Behaviour {
			uintptr_t get_enabled = 0x0;
			uintptr_t set_enabled = 0x0;
			uintptr_t get_isActiveAndEnabled = 0x0;
		}

		namespace Camera {
			uintptr_t set_fieldOfView = 0x0;
			uintptr_t get_fieldOfView = 0x0;
			uintptr_t get_current = 0x0;
		}

		namespace RectTransformUtility {
			uintptr_t WorldToScreenPoint = 0x0;
		}

		namespace Time {
			uintptr_t get_Time = 0x0;
			uintptr_t get_deltaTime = 0x0;
		}

		namespace Material {
			uintptr_t setColor = 0x0;
			uintptr_t setShader = 0x0;
			uintptr_t getDefaultMaterial = 0x0;
		}

		namespace Cursor {
			uintptr_t get_lockState = 0x0;
			uintptr_t set_lockState = 0x0;
		}

		namespace SystemInfo {
			uintptr_t get_deviceUniqueIdentifier = 0x0;
		}

		namespace Application {
			uintptr_t Quit1 = 0x0;
			uintptr_t Quit2 = 0x0;
			uintptr_t Internal_ApplicationQuit = 0x0;
			uintptr_t Internal_ApplicationWantsToQuit = 0x0;
		}

		namespace Shader {
			uintptr_t shaderFind = 0x0;
		}

		namespace Renderer {
			uintptr_t getMaterial = 0x0;
			uintptr_t setMaterial = 0x0;
		}

		namespace Font {
			uintptr_t getDefaultFont = 0x0;
		}
	}

	namespace MakerPen {
		uintptr_t get_Tool = 0x0;
	}

	namespace RecRoomCoreCombat {
		namespace RangedWeapon {
			uintptr_t get_IsOnCooldown = 0x0;
			uintptr_t Fire = 0x0;
		}

		namespace Weapon {
			uintptr_t get_HasEnoughMagazineAmmunition = 0x0;
			uintptr_t get_TotalAmmunition = 0x0;
			uintptr_t get_Tool = 0x0;
		}
	}

	namespace UGCSeatManagement
	{
		uintptr_t CV2SetSeatedPlayer = 0x0;
	}
	namespace RecRoomCoreCreation {
		namespace SandboxGunHandle {
			uintptr_t get_IsOnCooldown = 0x0;
		}
	}

	namespace RecRoomConsumable {
		namespace ConsumableManager {
			uintptr_t SpawnConsumableForLocalPlayer = 0x0;
		}
	}

	namespace RecRoomCoreLocomotion {
		namespace PlayerMovement {
			uintptr_t get_IsFlyingEnabled = 0x0;
			uintptr_t AddFlyEnabled = 0x0;
			uintptr_t RemoveFlyEnabled = 0x0;
		}
	}

	namespace CodeStageAntiCheatDetectors {
		namespace RRCheatDetector {
			uintptr_t StartDetection1 = 0x0;
			uintptr_t StartDetection2 = 0x0;
			uintptr_t StartDetection3 = 0x0;
			uintptr_t StartDetection4 = 0x0;
			uintptr_t StartDetection5 = 0x0;
		}

		namespace InjectionDetector {
			uintptr_t StartDetection1 = 0x0;
			uintptr_t StartDetection2 = 0x0;
		}

		namespace ObscuredCheatingDetector {
			uintptr_t StartDetection1 = 0x0;
			uintptr_t StartDetection2 = 0x0;
		}

		namespace SpeedHackDetector {
			uintptr_t StartDetection1 = 0x0;
			uintptr_t StartDetection2 = 0x0;
			uintptr_t StartDetection3 = 0x0;
			uintptr_t StartDetection4 = 0x0;
			uintptr_t StartDetection5 = 0x0;
		}

		namespace TimeCheatingDetector {
			uintptr_t StartDetection1 = 0x0;
			uintptr_t StartDetection2 = 0x0;
		}

		namespace WallHackDetector {
			uintptr_t StartDetection1 = 0x0;
			uintptr_t StartDetection2 = 0x0;
			uintptr_t StartDetection3 = 0x0;
			uintptr_t StartDetection4 = 0x0;
		}
	}

	namespace RecRoomSceneManager {
		uintptr_t get_Instance = 0x0;
	}

	namespace SessionManager {
		uintptr_t FatalApplicationQuit = 0x0;
	}

	namespace RecRoomSystems {
		namespace InputManager {
			uintptr_t OnUpdate = 0x0;
		}
	}

	namespace RecRoomSystemsPlayerRoles {
		namespace PlayerGameRoleManager {
			uintptr_t get_Instance = 0x0;
		}
		namespace PlayerRoomRoleManager {
			uintptr_t ctor = 0x0;
		}
	}

	namespace CircuitsV2 {
		namespace CircuitsV2Manager {
			uintptr_t RpcSendMajorNotification = 0x0;
		}
	}

	namespace PlayerAvatarDisplay {
		uintptr_t SetSkinColor = 0x0;
	}

	namespace Player {
		uintptr_t get_PlayerMovement = 0x0;
		uintptr_t get_IsInitialized = 0x0;
		uintptr_t SetHeadScale = 0x0;
		uintptr_t set_AvatarSkeletonIsEnabled = 0x0;
		uintptr_t get_DesiredAvatarSkeletonTrackingSpaceScale = 0x0;
		uintptr_t get_RightHand = 0x0;
		uintptr_t get_LeftHand = 0x0;
		uintptr_t get_CurrentHeadPosition = 0x0;
		uintptr_t get_CurrentBodyPosition = 0x0;
		uintptr_t get_Head = 0x0;
		uintptr_t get_Ping = 0x0;
		uintptr_t get_HardwareType = 0x0;
		uintptr_t get_RecNetDeviceClass = 0x0;
		uintptr_t get_HasVisibleRecRoomPlus = 0x0;
		uintptr_t get_IsFriend = 0x0;
		uintptr_t GetFromActorNumber = 0x0;
		uintptr_t get_AllToolsOnPlayer = 0x0;
		uintptr_t getPlayerName = 0x0;
		uintptr_t getHand = 0x0;
		uintptr_t get_TrackingSpace = 0x0;
		uintptr_t GetRotation = 0x0;
		uintptr_t RpcAuthorityCV2EquipObject = 0x0;
		uintptr_t get_IsInitialLoadFinished = 0x0;
	}

	namespace CreationObject {
		uintptr_t Scale = 0x0;
		uintptr_t get_IsFrozen = 0x0;
		uintptr_t set_IsFrozen = 0x0;
		uintptr_t get_IsGrabbable = 0x0;
		uintptr_t set_IsGrabbable = 0x0;
		uintptr_t get_Initialized = 0x0;
		uintptr_t set_DynamicCollisionEnabled = 0x0;
	}

	namespace PlayerHand {
		uintptr_t TryReleaseTool = 0x0;
		uintptr_t TryPickupTool = 0x0;
	}

	namespace QuestManager {
		uintptr_t get_Instance = 0x0;
		uintptr_t set_DefaultRoomIndex = 0x0;
	}

	namespace RRUIData {
		namespace StoreItemModel {
			uintptr_t get_IsBuyButtonInteractable = 0x0;
			uintptr_t get_IsOwnedButtonVisible = 0x0;
			uintptr_t get_IsOwnedTextVisible = 0x0;
		}
	}

	namespace ExitGamesClientPhoton {
		namespace Hashtable {
			uintptr_t StaticConstructor = 0x0;
			uintptr_t Add = 0x0;
			uintptr_t get_Item = 0x0;
			uintptr_t get_Item2 = 0x0;
			uintptr_t set_Item2 = 0x0;
			uintptr_t set_Item = 0x0;
			uintptr_t ToString = 0x0;
		}

		namespace EventData {
			uintptr_t toStringEvent = 0x0;
			uintptr_t getCustomDataEvent = 0x0;
			uintptr_t getSenderEvent = 0x0;
		}
	}

	namespace PhotonPun {
		namespace PhotonView {
			uintptr_t get_ViewID = 0x0;
			uintptr_t findPhotonView = 0x0;
			uintptr_t RPC = 0x0;
			uintptr_t RPC_PP = 0x0;
			uintptr_t TransferOwnership = 0x0;
		}

		namespace MonoBehaviourPun {
			uintptr_t get_PhotonView = 0x0;
		}
	}

	namespace UnityEngineUI {
		namespace Text {
			uintptr_t set_Text = 0x0;
			uintptr_t setFontSize = 0x0;
			uintptr_t getFont = 0x0;
			uintptr_t getMainTexture = 0x0;
			uintptr_t getFontStyle = 0x0;
			uintptr_t setFont = 0x0;
		}

		namespace Toggle {
			uintptr_t get_isOn = 0x0;
			uintptr_t set_isOn = 0x0;
		}

		namespace Selectable {
			uintptr_t set_colors = 0x0;
			uintptr_t set_transition = 0x0;
			uintptr_t set_targetGraphic = 0x0;
		}

		namespace Canvas {
			uintptr_t set_renderMode = 0x0;
			uintptr_t get_sortingOrder = 0x0;
			uintptr_t set_sortingOrder = 0x0;
		}
	}

	namespace System {
		namespace Uri {
			uintptr_t CreateUri = 0x0;
			uintptr_t TryCreate = 0x0;
			uintptr_t ToString = 0x0;
		}

		namespace String {
			uintptr_t CreateString = 0x0;
		}

		namespace Type {
			uintptr_t GetType = 0x0;
			uintptr_t GetType2 = 0x0;
			uintptr_t getType = 0x0;
		}

		namespace Array {
			uintptr_t createInstance = 0x0;
		}

		namespace Guid {
			uintptr_t toString = 0x0;
		}
	}

	namespace SystemComponentModel {
		namespace TypeDescriptor {
			uintptr_t getClassName = 0x0;
		}
	}

	namespace SystemText {
		namespace Encoding {
			uintptr_t GetBytes = 0x0;
		}
	}

	namespace ValveVR {
		namespace SteamVR_RenderModel {
			uintptr_t getComponentTransform = 0x0;
		}
	}

	namespace EasyAntiCheatClientHydra {
		namespace Runtime {
			uintptr_t OnIntegrityViolation = 0x0;
		}
	}

	uintptr_t serverTime = 0x0; // Not actually done yet there is no find method added to this

	namespace chai {
		uintptr_t FatalApplicationQuit = 0x0;
		uintptr_t codeStageStartDetectionAdvancedMotion = 0x0;
	}

	namespace dictionary
	{
		uintptr_t get_Keys = 0x0;
		uintptr_t GetEnumerator = 0x0;
		uintptr_t get_Values = 0x0;
		uintptr_t MoveNext = 0x0;
		uintptr_t get_Current = 0x0;
	}

	namespace obfuscated
	{
		uintptr_t IsValid = 0x0;
		uintptr_t get_Health = 0x0;
		uintptr_t get_Health2 = 0x0;
		uintptr_t get_Health3 = 0x0;
		uintptr_t get_Health4 = 0x0;
		uintptr_t get_Health5 = 0x0;
		uintptr_t get_Health6 = 0x0;

		namespace photon {
			uintptr_t Destroy1 = 0x0;
			uintptr_t Destroy2 = 0x0;
			uintptr_t Destroy3 = 0x0;
			uintptr_t Destroy4 = 0x0;
			uintptr_t Destroy5 = 0x0;
			uintptr_t Destroy6 = 0x0;
			uintptr_t getPhotonPlayer = 0x0;
			uintptr_t OpRaiseEvent = 0x0;
			uintptr_t OnEvent = 0x0;
			uintptr_t setMasterClient = 0x0;
			uintptr_t PhotonPlayerToString = 0x0;
			uintptr_t PhotonPlayerToStringFull = 0x0;
			uintptr_t getActorNumber = 0x0;
			uintptr_t photonInstantiate = 0x0;
			uintptr_t photonInstantiateAssets = 0x0;
			uintptr_t photonInstantiate2 = 0x0;
			uintptr_t photonPlayerList = 0x0;
			uintptr_t photonPlayerOthersList = 0x0;
			uintptr_t get_PhotonPlayer = 0x0;
			uintptr_t get_isMasterClient = 0x0;
			uintptr_t joinRoom = 0x0;
			uintptr_t get_CustomProperties = 0x0;
			uintptr_t set_CustomProperties = 0x0;
		}

	}

	struct methodPointerInfo {
		uintptr_t& methodPointer;
		const char* assembly;
		const char* namespaze;
		const char* klass;
		const char* methodName;
		int argsCount;
		const char* actualMethodName;
		const char* actualMethodNamespace;
	};

	struct methodPointerOverloadInfo {
		uintptr_t& methodPointer;
		const char* assembly;
		const char* namespaze;
		const char* klass;
		const char* methodName;
		int argsCount;
		int index;
		const char* actualMethodName;
		const char* actualMethodNamespace;
	};

	struct methodPointerSignatureInfo {
		uintptr_t& methodPointer;
		int index;
		const char* signature;
		const char* actualMethodName;
		const char* actualMethodNamespace;
	};

	std::vector<methodPointerInfo> methodPointerInfoList = {

		{ methods::RecRoomCoreCombat::RangedWeapon::get_IsOnCooldown, "Assembly-CSharp", "RecRoom.Core.Combat", "RangedWeapon", "get_IsOnCooldown", 0, "get_IsOnCooldown", "RecRoomCoreCombat::RangedWeapon"},
		{ methods::RecRoomCoreCombat::RangedWeapon::Fire, "Assembly-CSharp", "RecRoom.Core.Combat", "RangedWeapon", "Fire", 1, "Fire", "RecRoomCoreCombat::RangedWeapon" },
		{ methods::RecRoomCoreCombat::Weapon::get_HasEnoughMagazineAmmunition, "Assembly-CSharp", "RecRoom.Core.Combat", "Weapon", "get_HasEnoughMagazineAmmunition", 0, "get_HasEnoughMagazineAmmunition", "RecRoomCoreCombat::Weapon" },
		{ methods::RecRoomCoreCombat::Weapon::get_TotalAmmunition, "Assembly-CSharp", "RecRoom.Core.Combat", "Weapon", "get_TotalAmmunition", 0, "get_TotalAmmunition", "RecRoomCoreCombat::Weapon" },
			{ methods::RecRoomCoreCombat::Weapon::get_Tool, "Assembly-CSharp", "RecRoom.Core.Combat", "Weapon", "get_Tool", 0, "get_Tool", "RecRoomCoreCombat::Weapon" },
		{ methods::RecRoomCoreCreation::SandboxGunHandle::get_IsOnCooldown, "Assembly-CSharp", "RecRoom.Core.Creation", "SandboxGunHandle", "get_IsOnCooldown", 0, "get_IsOnCooldown", "RecRoomCoreCreation::SandboxGunHandle" },
		{ methods::RecRoomConsumable::ConsumableManager::SpawnConsumableForLocalPlayer, "Assembly-CSharp", "RecRoom.Consumable", "ConsumableManager", "SpawnConsumableForLocalPlayer", 6, "SpawnConsumableForLocalPlayer", "RecRoomConsumable::ConsumableManager" },
		{ methods::RecRoomCoreLocomotion::PlayerMovement::get_IsFlyingEnabled, "Assembly-CSharp", "RecRoom.Core.Locomotion", "PlayerMovement", "get_IsFlyingEnabled", 0, "get_IsFlyingEnabled", "RecRoomCoreLocomotion::PlayerMovement" },
		{ methods::RecRoomCoreLocomotion::PlayerMovement::AddFlyEnabled, "Assembly-CSharp", "RecRoom.Core.Locomotion", "PlayerMovement", "AddFlyEnabled", 3, "AddFlyEnabled", "RecRoomCoreLocomotion::PlayerMovement" },
           { methods::RecRoomCoreLocomotion::PlayerMovement::RemoveFlyEnabled, "Assembly-CSharp", "RecRoom.Core.Locomotion", "PlayerMovement", "RemoveFlyEnabled", 1, "RemoveFlyEnabled", "RecRoomCoreLocomotion::PlayerMovement" },

		{ methods::CodeStageAntiCheatDetectors::RRCheatDetector::StartDetection1, "Assembly-CSharp", "CodeStage.AntiCheat.Detectors", "RRCheatDetector", "StartDetection", 0, "StartDetection1", "CodeStageAntiCheatDetectors::RRCheatDetector" },
		{ methods::CodeStageAntiCheatDetectors::RRCheatDetector::StartDetection2, "Assembly-CSharp", "CodeStage.AntiCheat.Detectors", "RRCheatDetector", "StartDetection", 1, "StartDetection2", "CodeStageAntiCheatDetectors::RRCheatDetector" },
		{ methods::CodeStageAntiCheatDetectors::RRCheatDetector::StartDetection3, "Assembly-CSharp", "CodeStage.AntiCheat.Detectors", "RRCheatDetector", "StartDetection", 2, "StartDetection3", "CodeStageAntiCheatDetectors::RRCheatDetector" },
		{ methods::CodeStageAntiCheatDetectors::RRCheatDetector::StartDetection4, "Assembly-CSharp", "CodeStage.AntiCheat.Detectors", "RRCheatDetector", "StartDetection", 3, "StartDetection4", "CodeStageAntiCheatDetectors::RRCheatDetector" },
		{ methods::CodeStageAntiCheatDetectors::RRCheatDetector::StartDetection5, "Assembly-CSharp", "CodeStage.AntiCheat.Detectors", "RRCheatDetector", "StartDetection", 4, "StartDetection5", "CodeStageAntiCheatDetectors::RRCheatDetector" },
		{ methods::RecRoomSceneManager::get_Instance, "Assembly-CSharp", "", "RecRoomSceneManager", "get_Instance", 0, "get_Instance", "RecRoomSceneManager" },
		{ methods::SessionManager::FatalApplicationQuit, "Assembly-CSharp", "", "SessionManager", "FatalApplicationQuit", 2, "FatalApplicationQuit", "SessionManager" },
		{ methods::RecRoomSystems::InputManager::OnUpdate, "Assembly-CSharp", "RecRoom.Systems", "InputManager", "OnUpdate", 0, "OnUpdate", "RecRoomSystems::InputManager" },
		{ methods::RecRoomSystemsPlayerRoles::PlayerGameRoleManager::get_Instance, "Assembly-CSharp", "RecRoom.Systems.PlayerRoles", "PlayerGameRoleManager", "get_Instance", 0, "get_Instance", "RecRoomSystemsPlayerRoles::PlayerGameRoleManager" },
			{ methods::RecRoomSystemsPlayerRoles::PlayerRoomRoleManager::ctor, "Assembly-CSharp", "RecRoom.Systems.PlayerRoles", "PlayerRoomRoleManager", ".ctor", 0, "ctor", "RecRoomSystemsPlayerRoles::PlayerRoomRoleManager" },
		{ methods::Player::get_PlayerMovement, "Assembly-CSharp", "", "Player", "get_PlayerMovement", 0, "get_PlayerMovement", "Player" },
		{ methods::Player::get_IsInitialized, "Assembly-CSharp", "", "Player", "get_IsInitialized", 0, "get_IsInitialized", "Player" },
		{ methods::Player::SetHeadScale, "Assembly-CSharp", "", "Player", "SetHeadScale", 1, "SetHeadScale", "Player" },
		{ methods::Player::set_AvatarSkeletonIsEnabled, "Assembly-CSharp", "", "Player", "set_AvatarSkeletonIsEnabled", 1, "set_AvatarSkeletonIsEnabled", "Player" },
		{ methods::Player::get_DesiredAvatarSkeletonTrackingSpaceScale, "Assembly-CSharp", "", "Player", "get_DesiredAvatarSkeletonTrackingSpaceScale", 0, "get_DesiredAvatarSkeletonTrackingSpaceScale", "Player" },
		{ methods::Player::get_RightHand, "Assembly-CSharp", "", "Player", "get_RightHand", 0, "get_RightHand", "Player" },
		{ methods::Player::get_LeftHand, "Assembly-CSharp", "", "Player", "get_LeftHand", 0, "get_LeftHand", "Player" },
		{ methods::Player::get_CurrentHeadPosition, "Assembly-CSharp", "", "Player", "get_CurrentHeadPosition", 0, "get_CurrentHeadPosition", "Player" },
		{ methods::Player::get_CurrentBodyPosition, "Assembly-CSharp", "", "Player", "get_CurrentBodyPosition", 0, "get_CurrentBodyPosition", "Player" },
		{ methods::Player::get_Head, "Assembly-CSharp", "", "Player", "get_Head", 0, "get_Head", "Player" },
		{ methods::Player::get_Ping, "Assembly-CSharp", "", "Player", "get_Ping", 0, "get_Ping", "Player" },
		{ methods::Player::get_HardwareType, "Assembly-CSharp", "", "Player", "get_HardwareType", 0, "get_HardwareType", "Player" },
		{ methods::Player::get_RecNetDeviceClass, "Assembly-CSharp", "", "Player", "get_RecNetDeviceClass", 0, "get_RecNetDeviceClass", "Player" },
		{ methods::Player::get_HasVisibleRecRoomPlus, "Assembly-CSharp", "", "Player", "get_HasVisibleRecRoomPlus", 0, "get_HasVisibleRecRoomPlus", "Player" },
		{ methods::Player::get_IsFriend, "Assembly-CSharp", "", "Player", "get_IsFriend", 0, "get_IsFriend", "Player" },
		{ methods::Player::GetFromActorNumber, "Assembly-CSharp", "", "Player", "GetFromActorNumber", 1, "GetFromActorNumber", "Player" },
		{ methods::Player::get_AllToolsOnPlayer, "Assembly-CSharp", "", "Player", "get_AllToolsOnPlayer", 0, "get_AllToolsOnPlayer", "Player" },
		{ methods::Player::getPlayerName, "Assembly-CSharp", "", "Player", "get_PlayerName", 0, "getPlayerName", "Player" },
			{ methods::Player::get_TrackingSpace, "Assembly-CSharp", "", "Player", "get_TrackingSpace", 0, "get_TrackingSpace", "Player" },
			{ methods::Player::GetRotation, "Assembly-CSharp", "", "Player", "GetRotation", 0, "GetRotation", "Player" },
			{ methods::Player::RpcAuthorityCV2EquipObject, "Assembly-CSharp", "", "Player", "RpcAuthorityCV2EquipObject", 4, "RpcAuthorityCV2EquipObject", "Player" },
			{ methods::Player::get_IsInitialLoadFinished, "Assembly-CSharp", "", "Player", "get_IsInitialLoadFinished", 0, "get_IsInitialLoadFinished", "Player" },


			//{ methods::PlayerAvatarDisplay::SetSkinColor, "Assembly-CSharp", "RecRoom.Avatars", "PlayerAvatarDisplay", "SetSkinColor", 1, "SetSkinColor", "PlayerAvatarDisplay" },

			{ methods::CircuitsV2::CircuitsV2Manager::RpcSendMajorNotification, "Assembly-CSharp", "RecRoom.CircuitsV2", "CircuitsV2Manager", "RpcSendMajorNotification", 1, "RpcSendMajorNotification", "CircuitsV2::CircuitsV2Manager::RpcSendMajorNotification" },

			{ methods::QuestManager::get_Instance, "Assembly-CSharp", "RecRoom.Activities.Quest", "QuestManager", "get_Instance", 0, "get_Instance", "QuestManager" },
			{ methods::QuestManager::set_DefaultRoomIndex, "Assembly-CSharp", "RecRoom.Activities.Quest", "QuestManager", "set_DefaultRoomIndex", 1, "set_DefaultRoomIndex", "QuestManager" },

			{ methods::MakerPen::get_Tool, "Assembly-CSharp", "RecRoom.Tools", "MakerPen", "get_Tool", 0, "get_Tool", "MakerPen" },

			{ methods::UnityEngine::Physics::set_gravity, "UnityEngine.PhysicsModule", "UnityEngine", "Physics", "set_gravity", 1, "set_gravity", "UnityEngine::Physics" },
			{ methods::UnityEngine::Physics::get_gravity, "UnityEngine.PhysicsModule", "UnityEngine", "Physics", "get_gravity", 0, "get_gravity", "UnityEngine::Physics" },


		{ methods::CreationObject::Scale, "Assembly-CSharp", "RecRoom.Core.Creation", "CreationObject", "Scale", 1, "Scale", "CreationObject" },
		{ methods::CreationObject::get_IsFrozen, "Assembly-CSharp", "RecRoom.Core.Creation", "CreationObject", "get_IsFrozen", 0, "get_IsFrozen", "CreationObject" },
		{ methods::CreationObject::set_IsFrozen, "Assembly-CSharp", "RecRoom.Core.Creation", "CreationObject", "set_IsFrozen", 1, "set_IsFrozen", "CreationObject" },
		{ methods::CreationObject::get_IsGrabbable, "Assembly-CSharp", "RecRoom.Core.Creation", "CreationObject", "get_IsGrabbable", 0, "get_IsGrabbable", "CreationObject" },
		{ methods::CreationObject::set_IsGrabbable, "Assembly-CSharp", "RecRoom.Core.Creation", "CreationObject", "set_IsGrabbable", 1, "set_IsGrabbable", "CreationObject" },
		{ methods::CreationObject::get_Initialized, "Assembly-CSharp", "RecRoom.Core.Creation", "CreationObject", "get_Initialized", 0, "get_Initialized", "CreationObject" },
			{ methods::CreationObject::set_DynamicCollisionEnabled, "Assembly-CSharp", "RecRoom.Core.Creation", "CreationObject", "set_DynamicCollisionEnabled", 1, "set_DynamicCollisionEnabled", "CreationObject" },

			{ methods::PlayerHand::TryPickupTool, "Assembly-CSharp", "", "PlayerHand", "TryPickupTool", 3, "TryPickupTool", "PlayerHand"},
			{ methods::PlayerHand::TryReleaseTool, "Assembly-CSharp", "", "PlayerHand", "TryReleaseTool", 3, "TryReleaseTool", "PlayerHand"},

		{ methods::RRUIData::StoreItemModel::get_IsBuyButtonInteractable, "Assembly-CSharp", "RRUI.Data", "StoreItemModel", "get_IsBuyButtonInteractable", 0, "get_IsBuyButtonInteractable", "RRUIData::StoreItemModel"},
		{ methods::RRUIData::StoreItemModel::get_IsOwnedButtonVisible, "Assembly-CSharp", "RRUI.Data", "StoreItemModel", "get_IsOwnedButtonVisible", 0, "get_IsOwnedButtonVisible", "RRUIData::StoreItemModel"},
		{ methods::RRUIData::StoreItemModel::get_IsOwnedTextVisible, "Assembly-CSharp", "RRUI.Data", "StoreItemModel", "get_IsOwnedTextVisible", 0, "get_IsOwnedTextVisible", "RRUIData::StoreItemModel"},
		{ methods::ExitGamesClientPhoton::Hashtable::StaticConstructor, "Photon3Unity3D", "ExitGames.Client.Photon", "Hashtable", ".cctor", 0, "StaticConstructor", "ExitGamesClientPhoton::Hashtable"},
		{ methods::ExitGamesClientPhoton::Hashtable::Add, "Photon3Unity3D", "ExitGames.Client.Photon", "Hashtable", "Add", 2, "Add", "ExitGamesClientPhoton::Hashtable"},
		{ methods::ExitGamesClientPhoton::Hashtable::get_Item, "Photon3Unity3D", "ExitGames.Client.Photon", "Hashtable", "get_Item", 1, "get_Item", "ExitGamesClientPhoton::Hashtable"},
		{ methods::ExitGamesClientPhoton::Hashtable::set_Item, "Photon3Unity3D", "ExitGames.Client.Photon", "Hashtable", "set_Item", 2, "set_Item", "ExitGamesClientPhoton::Hashtable"},
		{ methods::ExitGamesClientPhoton::Hashtable::ToString, "Photon3Unity3D", "ExitGames.Client.Photon", "Hashtable", "ToString", 0, "ToString", "ExitGamesClientPhoton::Hashtable"},
		{ methods::ExitGamesClientPhoton::EventData::toStringEvent, "Photon3Unity3D", "ExitGames.Client.Photon", "EventData", "ToString", 0, "toStringEvent", "ExitGamesClientPhoton::EventData"},
		{ methods::ExitGamesClientPhoton::EventData::getCustomDataEvent, "Photon3Unity3D", "ExitGames.Client.Photon", "EventData", "get_CustomData", 0, "getCustomDataEvent", "ExitGamesClientPhoton::EventData"},
		{ methods::ExitGamesClientPhoton::EventData::getSenderEvent, "Photon3Unity3D", "ExitGames.Client.Photon", "EventData", "get_Sender", 0, "getSenderEvent", "ExitGamesClientPhoton::EventData"},
		{ methods::PhotonPun::PhotonView::get_ViewID, "PhotonUnityNetworking", "Photon.Pun", "PhotonView", "get_ViewID", 0, "get_ViewID", "PhotonPun::PhotonView"},
		{ methods::PhotonPun::PhotonView::findPhotonView, "PhotonUnityNetworking", "Photon.Pun", "PhotonView", "Find", 1, "findPhotonView", "PhotonPun::PhotonView"},
		{ methods::PhotonPun::PhotonView::RPC, "PhotonUnityNetworking", "Photon.Pun", "PhotonView", "RPC", 3, "RPC", "PhotonPun::PhotonView"},
			{ methods::PhotonPun::PhotonView::TransferOwnership, "PhotonUnityNetworking", "Photon.Pun", "PhotonView", "TransferOwnership", 1, "TransferOwnership", "PhotonPun::PhotonView"},
		{ methods::PhotonPun::MonoBehaviourPun::get_PhotonView, "PhotonUnityNetworking", "Photon.Pun", "MonoBehaviourPun", "get_photonView", 0, "get_PhotonView", "PhotonPun::MonoBehaviourPun"},
		{ methods::UnityEngine::Cursor::get_lockState, "UnityEngine.CoreModule", "UnityEngine", "Cursor", "get_lockState", 0, "get_lockState", "UnityEngine::Cursor"},
		{ methods::UnityEngine::Cursor::set_lockState, "UnityEngine.CoreModule", "UnityEngine", "Cursor", "set_lockState", 1, "set_lockState", "UnityEngine::Cursor"},
		{ methods::UnityEngine::SystemInfo::get_deviceUniqueIdentifier, "UnityEngine.CoreModule", "UnityEngine", "SystemInfo", "get_deviceUniqueIdentifier", 0, "get_deviceUniqueIdentifier", "UnityEngine::SystemInfo"},
		{ methods::UnityEngine::Application::Quit1, "UnityEngine.CoreModule", "UnityEngine", "Application", "Quit", 1, "Quit1", "UnityEngine::Application"},
		{ methods::UnityEngine::Application::Quit2, "UnityEngine.CoreModule", "UnityEngine", "Application", "Quit", 0, "Quit2", "UnityEngine::Application"},
		{ methods::UnityEngine::Application::Internal_ApplicationQuit, "UnityEngine.CoreModule", "UnityEngine", "Application", "Internal_ApplicationQuit", 0, "Internal_ApplicationQuit", "UnityEngine::Application"},
		{ methods::UnityEngine::Application::Internal_ApplicationWantsToQuit, "UnityEngine.CoreModule", "UnityEngine", "Application", "Internal_ApplicationWantsToQuit", 0, "Internal_ApplicationWantsToQuit", "UnityEngine::Application"},
		{ methods::UnityEngine::Shader::shaderFind, "UnityEngine.CoreModule", "UnityEngine", "Shader", "Find", 1, "shaderFind", "UnityEngine::Shader"},
		{ methods::UnityEngine::Renderer::getMaterial, "UnityEngine.CoreModule", "UnityEngine", "Renderer", "GetMaterial", 0, "getMaterial", "UnityEngine::Renderer"},
		{ methods::UnityEngine::Renderer::setMaterial, "UnityEngine.CoreModule", "UnityEngine", "Renderer", "SetMaterial", 1, "setMaterial", "UnityEngine::Renderer"},
		{ methods::UnityEngine::Material::setColor, "UnityEngine.CoreModule", "UnityEngine", "Material", "set_color", 1, "setColor", "UnityEngine::Material"},
		{ methods::UnityEngine::Material::setShader, "UnityEngine.CoreModule", "UnityEngine", "Material", "set_shader", 1, "setShader", "UnityEngine::Material"},
		{ methods::UnityEngine::Material::getDefaultMaterial, "UnityEngine.CoreModule", "UnityEngine", "Material", "GetDefaultMaterial", 0, "getDefaultMaterial", "UnityEngine::Material"},
		{ methods::UnityEngine::Component::get_gameObject, "UnityEngine.CoreModule", "UnityEngine", "Component", "get_gameObject", 0, "get_gameObject", "UnityEngine::Component"},
		{ methods::UnityEngine::Component::get_transform, "UnityEngine.CoreModule", "UnityEngine", "Component", "get_transform", 0, "get_transform", "UnityEngine::Component"},
		{ methods::UnityEngine::Time::get_Time, "UnityEngine.CoreModule", "UnityEngine", "Time", "get_time", 0, "get_Time", "UnityEngine::Time"},
		{ methods::UnityEngine::Time::get_deltaTime, "UnityEngine.CoreModule", "UnityEngine", "Time", "get_deltaTime", 0, "get_deltaTime", "UnityEngine::Time"},
		{ methods::UnityEngine::Object::GetName, "UnityEngine.CoreModule", "UnityEngine", "Object", "GetName", 1, "GetName", "UnityEngine::Object"},
		{ methods::UnityEngine::Object::FindObjectsOfType, "UnityEngine.CoreModule", "UnityEngine", "Object", "FindObjectsOfType", 1, "FindObjectsOfType", "UnityEngine::Object"},
		{ methods::UnityEngine::Object::set_name, "UnityEngine.CoreModule", "UnityEngine", "Object", "set_name", 1, "set_name", "UnityEngine::Object"},
		{ methods::UnityEngine::Object::Destroy, "UnityEngine.CoreModule", "UnityEngine", "Object", "Destroy", 1, "Destroy", "UnityEngine::Object"},
		{ methods::UnityEngine::Object::ToString, "UnityEngine.CoreModule", "UnityEngine", "Object", "ToString", 1, "ToString", "UnityEngine::Object"},
		{ methods::UnityEngine::GameObject::get_transform, "UnityEngine.CoreModule", "UnityEngine", "GameObject", "get_transform", 0, "get_transform", "UnityEngine::GameObject"},
		{ methods::UnityEngine::GameObject::GetComponents, "UnityEngine.CoreModule", "UnityEngine", "GameObject", "GetComponents", 1, "GetComponents", "UnityEngine::GameObject"},
		//{ methods::UnityEngine::GameObject::GetComponent, "UnityEngine.CoreModule", "UnityEngine", "GameObject", "GetComponent", 1, "GetComponent", "UnityEngine::GameObject"},
		{ methods::UnityEngine::GameObject::CreatePrimitive, "UnityEngine.CoreModule", "UnityEngine", "GameObject", "CreatePrimitive", 1, "CreatePrimitive", "UnityEngine::GameObject"},
		{ methods::UnityEngine::GameObject::get_active, "UnityEngine.CoreModule", "UnityEngine", "GameObject", "get_active", 0, "get_active", "UnityEngine::GameObject"},
		{ methods::UnityEngine::GameObject::set_active, "UnityEngine.CoreModule", "UnityEngine", "GameObject", "set_active", 1, "set_active", "UnityEngine::GameObject"},
		{ methods::UnityEngine::GameObject::AddComponent, "UnityEngine.CoreModule", "UnityEngine", "GameObject", "AddComponent", 1, "AddComponent", "UnityEngine::GameObject"},
		{ methods::UnityEngine::GameObject::Find, "UnityEngine.CoreModule", "UnityEngine", "GameObject", "Find", 1, "Find", "UnityEngine::GameObject"},
			{ methods::UnityEngine::GameObject::ctor, "UnityEngine.CoreModule", "UnityEngine", "GameObject", ".ctor", 1, "ctor", "UnityEngine::GameObject"},
			{ methods::UnityEngine::GameObject::set_layer, "UnityEngine.CoreModule", "UnityEngine", "GameObject", "set_layer", 1, "set_layer", "UnityEngine::GameObject"},
			{ methods::UnityEngine::GameObject::get_layer, "UnityEngine.CoreModule", "UnityEngine", "GameObject", "get_layer", 0, "get_layer", "UnityEngine::GameObject"},
		{ methods::UnityEngine::Transform::get_localRotation, "UnityEngine.CoreModule", "UnityEngine", "Transform", "get_localRotation", 0, "get_localRotation", "UnityEngine::Transform"},
		{ methods::UnityEngine::Transform::set_localRotation, "UnityEngine.CoreModule", "UnityEngine", "Transform", "set_localRotation", 1, "set_localRotation", "UnityEngine::Transform"},
		{ methods::UnityEngine::Transform::get_parent, "UnityEngine.CoreModule", "UnityEngine", "Transform", "get_parent", 0, "get_parent", "UnityEngine::Transform"},
		{ methods::UnityEngine::Transform::Find, "UnityEngine.CoreModule", "UnityEngine", "Transform", "Find", 1, "Find", "UnityEngine::Transform"},
		{ methods::UnityEngine::Transform::set_localScale, "UnityEngine.CoreModule", "UnityEngine", "Transform", "set_localScale", 1, "set_localScale", "UnityEngine::Transform"},
		{ methods::UnityEngine::Transform::get_localScale, "UnityEngine.CoreModule", "UnityEngine", "Transform", "get_localScale", 0, "get_localScale", "UnityEngine::Transform"},
		{ methods::UnityEngine::Transform::SetParent, "UnityEngine.CoreModule", "UnityEngine", "Transform", "SetParent", 1, "SetParent", "UnityEngine::Transform"},
		{ methods::UnityEngine::Transform::get_childCount, "UnityEngine.CoreModule", "UnityEngine", "Transform", "get_childCount", 0, "get_childCount", "UnityEngine::Transform"},
		{ methods::UnityEngine::Transform::GetChild, "UnityEngine.CoreModule", "UnityEngine", "Transform", "GetChild", 1, "GetChild", "UnityEngine::Transform"},
		{ methods::UnityEngine::Transform::get_position, "UnityEngine.CoreModule", "UnityEngine", "Transform", "get_position", 0, "get_position", "UnityEngine::Transform"},
		{ methods::UnityEngine::Transform::set_localPosition, "UnityEngine.CoreModule", "UnityEngine", "Transform", "set_localPosition", 1, "set_localPosition", "UnityEngine::Transform"},
		{ methods::UnityEngine::Transform::get_forward, "UnityEngine.CoreModule", "UnityEngine", "Transform", "get_forward", 0, "get_forward", "UnityEngine::Transform"},
			{ methods::UnityEngine::Transform::get_up, "UnityEngine.CoreModule", "UnityEngine", "Transform", "get_up", 0, "get_up", "UnityEngine::Transform"},
			{ methods::UnityEngine::Transform::get_right, "UnityEngine.CoreModule", "UnityEngine", "Transform", "get_right", 0, "get_right", "UnityEngine::Transform"},
			{ methods::UnityEngine::Transform::set_position, "UnityEngine.CoreModule", "UnityEngine", "Transform", "set_position", 1, "set_position", "UnityEngine::Transform"},
			{ methods::UnityEngine::Transform::get_rotation, "UnityEngine.CoreModule", "UnityEngine", "Transform", "get_rotation", 0, "get_rotation", "UnityEngine::Transform"},
			{ methods::UnityEngine::Transform::set_rotation, "UnityEngine.CoreModule", "UnityEngine", "Transform", "set_rotation", 1, "set_rotation", "UnityEngine::Transform"},
		{ methods::UnityEngine::Camera::set_fieldOfView, "UnityEngine.CoreModule", "UnityEngine", "Camera", "set_fieldOfView", 1, "set_fieldOfView", "UnityEngine::Camera"},
		{ methods::UnityEngine::Camera::get_fieldOfView, "UnityEngine.CoreModule", "UnityEngine", "Camera", "get_fieldOfView", 0, "get_fieldOfView", "UnityEngine::Camera"},
		{ methods::UnityEngine::Camera::get_current, "UnityEngine.CoreModule", "UnityEngine", "Camera", "get_current", 0, "get_current", "UnityEngine::Camera"},
		{ methods::UnityEngine::Behaviour::get_enabled, "UnityEngine.CoreModule", "UnityEngine", "Behaviour", "get_enabled", 0, "get_enabled", "UnityEngine::Behaviour"},
		{ methods::UnityEngine::Behaviour::set_enabled, "UnityEngine.CoreModule", "UnityEngine", "Behaviour", "set_enabled", 1, "set_enabled", "UnityEngine::Behaviour"},
		{ methods::UnityEngine::Behaviour::get_isActiveAndEnabled, "UnityEngine.CoreModule", "UnityEngine", "Behaviour", "get_isActiveAndEnabled", 0, "get_isActiveAndEnabled", "UnityEngine::Behaviour"},
		{ methods::UnityEngineUI::Text::set_Text, "UnityEngine.UI", "UnityEngine.UI", "Text", "set_text", 1, "set_Text", "UnityEngineUI::Text"},
		{ methods::UnityEngineUI::Text::setFontSize, "UnityEngine.UI", "UnityEngine.UI", "Text", "set_fontSize", 1, "setFontSize", "UnityEngineUI::Text"},
		{ methods::UnityEngineUI::Text::getFont, "UnityEngine.UI", "UnityEngine.UI", "Text", "get_font", 0, "getFont", "UnityEngineUI::Text"},
		{ methods::UnityEngineUI::Text::getMainTexture, "UnityEngine.UI", "UnityEngine.UI", "Text", "get_mainTexture", 0, "getMainTexture", "UnityEngineUI::Text"},
		{ methods::UnityEngineUI::Text::getFontStyle, "UnityEngine.UI", "UnityEngine.UI", "Text", "get_fontStyle", 0, "getFontStyle", "UnityEngineUI::Text"},
		{ methods::UnityEngineUI::Text::setFont, "UnityEngine.UI", "UnityEngine.UI", "Text", "set_font", 1, "setFont", "UnityEngineUI::Text"},
		{ methods::UnityEngine::RectTransformUtility::WorldToScreenPoint, "UnityEngine.UIModule", "UnityEngine", "RectTransformUtility", "WorldToScreenPoint", 2, "WorldToScreenPoint", "UnityEngine::RectTransformUtility"},
		{ methods::System::Uri::CreateUri, "System", "System", "Uri", "CreateUri", 3, "CreateUri", "System::Uri"},
		{ methods::System::Uri::TryCreate, "System", "System", "Uri", "TryCreate", 3, "TryCreate", "System::Uri"},
		{ methods::System::Uri::ToString, "System", "System", "Uri", "ToString", 0, "ToString", "System::Uri"},
		{ methods::SystemComponentModel::TypeDescriptor::getClassName, "System", "System.ComponentModel", "TypeDescriptor", "GetClassName", 1, "getClassName", "SystemComponentModel::TypeDescriptor"},
		{ methods::System::String::CreateString, "mscorlib", "System", "String", "CreateString", 3, "CreateString", "System::String"},
		{ methods::SystemText::Encoding::GetBytes, "mscorlib", "System.Text", "Encoding", "GetBytes", 1, "GetBytes", "SystemText::Encoding"},
		{ methods::System::Type::GetType, "mscorlib", "System", "Type", "GetType", 2, "GetType", "System::Type"},
		{ methods::System::Type::GetType2, "mscorlib", "System", "Type", "GetType", 1, "GetType2", "System::Type"},
		{ methods::System::Type::getType, "mscorlib", "System", "Type", "GetType", 1, "getType", "System::Type"},
		{ methods::System::Array::createInstance, "mscorlib", "System", "Array", "CreateInstance", 2, "createInstance", "System::Array"},
		{ methods::ValveVR::SteamVR_RenderModel::getComponentTransform, "SteamVR", "Valve.VR", "SteamVR_RenderModel", "GetComponentTransform", 1, "getComponentTransform", "ValveVR::SteamVR_RenderModel"},
		//{ methods::EasyAntiCheatClientHydra::Runtime::OnIntegrityViolation, "EasyAntiCheat.Client", "EasyAntiCheat.Client.Hydra", "Runtime", "OnIntegrityViolation", 4, "OnIntegrityViolation", "EasyAntiCheatClientHydra::Runtime"},
		{ methods::CodeStageAntiCheatDetectors::InjectionDetector::StartDetection1, "Codestage.Anticheattoolkit.Runtime", "CodeStage.AntiCheat.Detectors", "InjectionDetector", "StartDetection", 0, "StartDetection1", "CodeStageAntiCheatDetectors::InjectionDetector"},
		{ methods::CodeStageAntiCheatDetectors::InjectionDetector::StartDetection2, "Codestage.Anticheattoolkit.Runtime", "CodeStage.AntiCheat.Detectors", "InjectionDetector", "StartDetection", 1, "StartDetection2", "CodeStageAntiCheatDetectors::InjectionDetector"},
		{ methods::CodeStageAntiCheatDetectors::ObscuredCheatingDetector::StartDetection1, "Codestage.Anticheattoolkit.Runtime", "CodeStage.AntiCheat.Detectors", "ObscuredCheatingDetector", "StartDetection", 0, "StartDetection1", "CodeStageAntiCheatDetectors::ObscuredCheatingDetector"},
		{ methods::CodeStageAntiCheatDetectors::ObscuredCheatingDetector::StartDetection2, "Codestage.Anticheattoolkit.Runtime", "CodeStage.AntiCheat.Detectors", "ObscuredCheatingDetector", "StartDetection", 1, "StartDetection2", "CodeStageAntiCheatDetectors::ObscuredCheatingDetector"},
		{ methods::CodeStageAntiCheatDetectors::SpeedHackDetector::StartDetection1, "Codestage.Anticheattoolkit.Runtime", "CodeStage.AntiCheat.Detectors", "SpeedHackDetector", "StartDetection", 0, "StartDetection1", "CodeStageAntiCheatDetectors::SpeedHackDetector"},
		{ methods::CodeStageAntiCheatDetectors::SpeedHackDetector::StartDetection2, "Codestage.Anticheattoolkit.Runtime", "CodeStage.AntiCheat.Detectors", "SpeedHackDetector", "StartDetection", 1, "StartDetection2", "CodeStageAntiCheatDetectors::SpeedHackDetector"},
		{ methods::CodeStageAntiCheatDetectors::SpeedHackDetector::StartDetection3, "Codestage.Anticheattoolkit.Runtime", "CodeStage.AntiCheat.Detectors", "SpeedHackDetector", "StartDetection", 2, "StartDetection3", "CodeStageAntiCheatDetectors::SpeedHackDetector"},
		{ methods::CodeStageAntiCheatDetectors::SpeedHackDetector::StartDetection4, "Codestage.Anticheattoolkit.Runtime", "CodeStage.AntiCheat.Detectors", "SpeedHackDetector", "StartDetection", 3, "StartDetection4", "CodeStageAntiCheatDetectors::SpeedHackDetector"},
		{ methods::CodeStageAntiCheatDetectors::SpeedHackDetector::StartDetection5, "Codestage.Anticheattoolkit.Runtime", "CodeStage.AntiCheat.Detectors", "SpeedHackDetector", "StartDetection", 4, "StartDetection5", "CodeStageAntiCheatDetectors::SpeedHackDetector"},
		{ methods::CodeStageAntiCheatDetectors::TimeCheatingDetector::StartDetection1, "Codestage.Anticheattoolkit.Runtime", "CodeStage.AntiCheat.Detectors", "TimeCheatingDetector", "StartDetection", 1, "StartDetection1", "CodeStageAntiCheatDetectors::TimeCheatingDetector"},
		{ methods::CodeStageAntiCheatDetectors::TimeCheatingDetector::StartDetection2, "Codestage.Anticheattoolkit.Runtime", "CodeStage.AntiCheat.Detectors", "TimeCheatingDetector", "StartDetection", 2, "StartDetection2", "CodeStageAntiCheatDetectors::TimeCheatingDetector"},
		{ methods::CodeStageAntiCheatDetectors::WallHackDetector::StartDetection1, "Codestage.Anticheattoolkit.Runtime", "CodeStage.AntiCheat.Detectors", "WallHackDetector", "StartDetection", 0, "StartDetection1", "CodeStageAntiCheatDetectors::WallHackDetector"},
		{ methods::CodeStageAntiCheatDetectors::WallHackDetector::StartDetection2, "Codestage.Anticheattoolkit.Runtime", "CodeStage.AntiCheat.Detectors", "WallHackDetector", "StartDetection", 1, "StartDetection2", "CodeStageAntiCheatDetectors::WallHackDetector"},
		{ methods::CodeStageAntiCheatDetectors::WallHackDetector::StartDetection3, "Codestage.Anticheattoolkit.Runtime", "CodeStage.AntiCheat.Detectors", "WallHackDetector", "StartDetection", 2, "StartDetection3", "CodeStageAntiCheatDetectors::WallHackDetector"},
		{ methods::CodeStageAntiCheatDetectors::WallHackDetector::StartDetection4, "Codestage.Anticheattoolkit.Runtime", "CodeStage.AntiCheat.Detectors", "WallHackDetector", "StartDetection", 3, "StartDetection4", "CodeStageAntiCheatDetectors::WallHackDetector"},
		{ methods::UnityEngine::Font::getDefaultFont, "UnityEngine.TextRenderingModule", "UnityEngine", "Font", "GetDefault", 0, "getDefaultFont", "UnityEngine::Font"},
		{ methods::System::Guid::toString, "mscorlib", "System", "Guid", "ToString", 0, "toString", "System::Guid" },
		{ methods::UnityEngineUI::Toggle::get_isOn, "UnityEngine.UI", "UnityEngine.UI", "Toggle", "get_isOn", 0, "get_isOn", "UnityEngineUI::Toggle" },
		{ methods::UnityEngineUI::Toggle::set_isOn, "UnityEngine.UI", "UnityEngine.UI", "Toggle", "set_isOn", 1, "set_isOn", "UnityEngineUI::Toggle" },
			{ methods::UnityEngineUI::Selectable::set_colors, "UnityEngine.UI", "UnityEngine.UI", "Selectable", "set_colors", 1, "set_colors", "UnityEngineUI::Selectable" },
			{ methods::UnityEngineUI::Selectable::set_transition, "UnityEngine.UI", "UnityEngine.UI", "Selectable", "set_transition", 1, "set_transition", "UnityEngineUI::Selectable" },
			{ methods::UnityEngineUI::Selectable::set_targetGraphic, "UnityEngine.UI", "UnityEngine.UI", "Selectable", "set_targetGraphic", 1, "set_targetGraphic", "UnityEngineUI::Selectable" },

			{ methods::UnityEngineUI::Canvas::set_renderMode, "UnityEngine.UIModule", "UnityEngine", "Canvas", "set_renderMode", 1, "set_renderMode", "UnityEngineUI::Canvas" },
			{ methods::UnityEngineUI::Canvas::get_sortingOrder, "UnityEngine.UIModule", "UnityEngine", "Canvas", "get_sortingOrder", 0, "get_sortingOrder", "UnityEngineUI::Canvas" },
			{ methods::UnityEngineUI::Canvas::set_sortingOrder, "UnityEngine.UIModule", "UnityEngine", "Canvas", "set_sortingOrder", 1, "set_sortingOrder", "UnityEngineUI::Canvas" },
		
			{ methods::UGCSeatManagement::CV2SetSeatedPlayer, "Assembly-CSharp", "RecRoom.Core", "UGCSeatManagement", "CV2SetSeatedPlayer", 2, "CV2SetSeatedPlayer", "RecRoom.Core::UGCSeatManagement" },
	};

	std::vector<methodPointerOverloadInfo> methodPointerOverloadInfoList = {
		{ methods::SystemText::Encoding::GetBytes, "mscorlib", "System.Text", "Encoding", "GetBytes", 1, 1, "GetBytes", "SystemText::Encoding" },
		{ methods::ExitGamesClientPhoton::Hashtable::get_Item, "Photon3Unity3D", "ExitGames.Client.Photon", "Hashtable", "get_Item", 1, 1, "get_Item", "ExitGamesClientPhoton::Hashtable" },
		{ methods::ExitGamesClientPhoton::Hashtable::set_Item, "Photon3Unity3D", "ExitGames.Client.Photon", "Hashtable", "set_Item", 2, 1, "set_Item", "ExitGamesClientPhoton::Hashtable" },
		{ methods::ExitGamesClientPhoton::Hashtable::get_Item2, "Photon3Unity3D", "ExitGames.Client.Photon", "Hashtable", "get_Item", 1, 0, "get_Item2", "ExitGamesClientPhoton::Hashtable" },
		{ methods::ExitGamesClientPhoton::Hashtable::set_Item2, "Photon3Unity3D", "ExitGames.Client.Photon", "Hashtable", "set_Item", 2, 0, "set_Item2", "ExitGamesClientPhoton::Hashtable"},
		{ methods::UnityEngine::GameObject::GetComponent, "UnityEngine.CoreModule", "UnityEngine", "GameObject", "GetComponent", 1, 1, "GetComponent", "UnityEngine::GameObject"},
		{ methods::PhotonPun::PhotonView::RPC_PP, "PhotonUnityNetworking", "Photon.Pun", "PhotonView", "RPC", 3, 1, "RPC_PP", "PhotonPun::PhotonView"},
		{ methods::Player::getHand, "Assembly-CSharp", "", "Player", "GetHand", 1, 1, "getHand", "Player"},
	};

	std::vector<methodPointerSignatureInfo> methodPointerSignatureInfoList = {
		//{ methods::obfuscated::IsValid, 0, "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 30 4D 8B F0 4C 8B E2 80 3D ? ? ? ? ? 75 73 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8", "IsValid", "obfuscated"},
		//{ methods::obfuscated::get_Health, 0, "48 89 5C 24 ? 55 48 8D 6C 24 ? 48 81 EC ? ? ? ? 80 3D ? ? ? ? ? 48 8B D9 75 2B 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 53 20 48 89 BC 24 ? ? ? ? 0F 29 B4 24 ? ? ? ? 44 0F 29 44 24 ? 48 85 D2 0F 84 ? ? ? ? 4C 8B 05 ? ? ? ? 48 8D 4D 07 E8 ? ? ? ? 48 8B 0D", "get_Health", "obfuscated"},
		//{ methods::obfuscated::get_Health2, 0, "48 89 5C 24 ? 55 48 8D 6C 24 ? 48 81 EC ? ? ? ? 80 3D ? ? ? ? ? 48 8B D9 75 2B 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 53 28 48 89 BC 24 ? ? ? ? 0F 29 B4 24 ? ? ? ? 44 0F 29 44 24 ? 48 85 D2 0F 84 ? ? ? ? 4C 8B 05 ? ? ? ? 48 8D 4D 07 E8 ? ? ? ? 48 8B 0D ? ? ? ? 83 B9", "get_Health2", "obfuscated" },
		//{ methods::obfuscated::get_Health3, 0, "40 53 48 83 EC 60 80 3D ? ? ? ? ? 48 8B D9 75 1F 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 53 30 48 85 D2 74 4A 4C 8B 05 ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 83 B9 ? ? ? ? ? 75 05 E8 ? ? ? ? 0F 10 44 24 ? 8B 44 24 30 48 8D 4C 24 ? 33 D2 89 44 24 50 0F 29 44 24 ? E8 ? ? ? ? 48 83 C4 60", "get_Health3", "obfuscated" },
		//{ methods::obfuscated::get_Health4, 0, "40 53 48 83 EC 60 80 3D ? ? ? ? ? 48 8B D9 75 1F 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 53 38 48 85 D2 74 4A 4C 8B 05 ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 83 B9 ? ? ? ? ? 75 05 E8 ? ? ? ? 0F 10 44 24 ? 8B 44 24 30 48 8D 4C 24 ? 33 D2 89 44 24 50 0F 29 44 24 ? E8 ? ? ? ? 48 83 C4 60", "get_Health4", "obfuscated" },
		//{ methods::obfuscated::get_Health5, 15, "40 53 48 83 EC 20 80 3D ? ? ? ? ? 48 8B D9 75 13 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 4B 48 48 85 C9 74 11 48 8B 15 ? ? ? ? 48 83 C4 20", "get_Health5", "obfuscated" },
		//{ methods::obfuscated::get_Health6, 13, "40 53 48 83 EC 20 80 3D ? ? ? ? ? 48 8B D9 75 13 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 4B 68 48 85 C9 74 11 48 8B 15 ? ? ? ? 48 83 C4 20", "get_Health6", "obfuscated" },
		//{ methods::obfuscated::photon::Destroy1, 0, "40 53 48 83 EC 20 80 3D ? ? ? ? ? 48 8B D9 75 13 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 0D ? ? ? ? 83 B9 ? ? ? ? ? 75 05 E8 ? ? ? ? 33 C9 E8 ? ? ? ? 84 C0 74 24 48 8B 0D ? ? ? ? 83 B9 ? ? ? ? ? 75 05 E8 ? ? ? ? 33 D2 48 8B CB 48 83 C4 20", "Destroy1", "obfuscated::photon"},
		//{ methods::obfuscated::photon::Destroy4, 0, "48 89 4C 24 ? 48 83 EC 28 80 3D ? ? ? ? ? 75 48 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B 4C 24 ? C6 05 ? ? ? ? ? 48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 48 85 C9 0F 84 ? ? ? ? 33 D2 E8 ? ? ? ? 48 8B 15 ? ? ? ? 8B D8 83 BA ? ? ? ? ? 75 0F 48 8B CA E8", "Destroy4", "obfuscated::photon" },
		//{ methods::obfuscated::photon::OpRaiseEvent, 0, "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 30 80 3D ? ? ? ? ? 49 8B F9 49 8B F0 0F B6 EA 48 8B D9 75 13 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 83 7B ? ? 74 5A 4C 8B 0D ? ? ? ? B2 FD 44 8B 43 78 48 8B CB 48 C7 44 24 ? ? ? ? ? E8 ? ? ? ? 84 C0 74 38 48 8B 4B 10 48 85 C9 74 46 48 8B 01 4C 8B CF 4C 8B C6 40 0F B6 D5 4C 8B 90 ? ? ? ? 48 8B 80 ? ? ? ? 48 89 44 24", "OpRaiseEvent", "obfuscated::photon"},
		//{ methods::obfuscated::photon::setMasterClient, 0, "40 53 48 83 EC 20 80 3D ? ? ? ? ? 48 8B D9 75 37 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 0D ? ? ? ? 83 B9 ? ? ? ? ? 75 05 E8 ? ? ? ? 80 3D ? ? ? ? ? 75 13 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 0D ? ? ? ? 83 B9 ? ? ? ? ? 75 05 E8 ? ? ? ? 33 C9 E8", "setMasterClient", "obfuscated::photon"},
		//{ methods::obfuscated::photon::photonInstantiate, 0, "40 55 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 80 3D ? ? ? ? ? 4D 8B F1 4D 8B E8 4C 8B FA 4C 8B E1 75 2B 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 0D ? ? ? ? 83 B9 ? ? ? ? ? 75 05 E8 ? ? ? ? 33 C9 E8 ? ? ? ? 48 85 C0 0F 84 ? ? ? ? 48 8B 0D ? ? ? ? 83 B9 ? ? ? ? ? 75 05 E8 ? ? ? ? 33 C9 E8", "photonInstantiate", "obfuscated::photon"},
		//{ methods::obfuscated::photon::photonInstantiateAssets, 0, "40 55 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 80 3D ? ? ? ? ? 4D 8B F1 4D 8B E8 4C 8B FA 4C 8B E1 75 37 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 0D ? ? ? ? 83 B9 ? ? ? ? ? 75 05 E8 ? ? ? ? 33 C9 48 89 9C 24 ? ? ? ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 85 C0 0F 84", "photonInstantiateAssets", "obfuscated::photon"},
		//{ methods::obfuscated::photon::photonPlayerList, 0, "48 83 EC 28 80 3D ? ? ? ? ? 75 1F 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 0D ? ? ? ? 83 B9 ? ? ? ? ? 75 05 E8 ? ? ? ? 33 C9 E8 ? ? ? ? 48 85 C0 75 12 48 8B 0D ? ? ? ? 33 D2 48 83 C4 28 E9 ? ? ? ?", "photonPlayerList", "obfuscated::photon"},
		//{ methods::obfuscated::photon::photonPlayerOthersList, 1, "48 83 EC 28 80 3D ? ? ? ? ? 75 1F 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8B 0D ? ? ? ? 83 B9 ? ? ? ? ? 75 05 E8 ? ? ? ? 33 C9 E8 ? ? ? ? 48 85 C0 75 12 48 8B 0D ? ? ? ? 33 D2 48 83 C4 28 E9 ? ? ? ?", "photonPlayerOthersList", "obfuscated::photon"},
		//{ methods::obfuscated::photon::OnEvent, 0, "48 8B C4 53 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 0F 29 70 B8 0F 29 78 A8 44 0F 29 40 ? 44 0F 29 48 ? 44 0F 29 90 ? ? ? ? 44 0F 29 98 ? ? ? ? 48 8B D9 80 3D ? ? ? ? ? 0F 85 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D", "OnEvent", "obfuscated::photon"},
		//{ rev_method, 0, "40 53 48 83 EC ? 48 8B D9 48 8B 01 48 8B 15 ? ? ? ? 48 8B 08 E8 ? ? ? ? 48 8B 53 ? 48 89 02 48 8B 43 ? 48 83 38 ? 74 ? 4C 8B 00", "rev_method", ""},
	};

	bool scan(methodPointerSignatureInfo scanStuff)
	{
		if (scanStuff.index > 0) {

			int currentIndex = 0;
			std::vector<uint64_t*> scanResults = PatternScanAll<uint64_t*>(scanStuff.signature, BaseAddress, SizeOfImage);

			if (scanStuff.index > scanResults.size() - 1)
			{
				Log::error("Index out of range: " + std::string(scanStuff.signature));
				return false;
			}

			for (uint64_t* pointer : scanResults) {
				uintptr_t methodAddress = reinterpret_cast<uintptr_t>(pointer);
				if (currentIndex == scanStuff.index)
				{
					scanStuff.methodPointer = methodAddress;
					return true;
				}
				currentIndex++;
			}

			Log::debug("Out of for loop?");
			return false;
		}
		else {
			uint64_t* ScanResult = PatternScan<uint64_t*>(scanStuff.signature, BaseAddress, SizeOfImage);

			scanStuff.methodPointer = (uintptr_t)ScanResult;

			return ScanResult ? true : (Log::error("No Results for: " + std::string(scanStuff.signature)), false);
		}
	}

	bool initialize() {
		// initialize methods' addresses, !!!!CAPITILIAZATION MATTERS!!!!

		ThreadFix();
		
		for (auto method : methodPointerInfoList) {
			//Log::debug("method looking is: " + std::string(method.methodName));
			method.methodPointer = (uintptr_t)FindMethod(method.assembly, method.namespaze, method.klass, method.methodName, method.argsCount, 0);
			//Log::debug("good");
		}

		for (auto method : methodPointerOverloadInfoList) {
			method.methodPointer = (uintptr_t)FindMethodOverload(method.assembly, method.namespaze, method.klass, method.methodName, method.argsCount, method.index);
		}

		for (auto method : methodPointerSignatureInfoList)
		{
			bool result = scan(method);
			if (!result)
				Log::debug("Error in scans.");
		}

		methods::chai::FatalApplicationQuit = 0x1FC9F70 + GameAssembly;
		methods::obfuscated::IsValid = 0xC32480 + GameAssembly;
		// bottom result, ones with same RVAs, REGEX:
		// bool\s+IsValid\s*\(\s*System::Uri\*\s+[A-Z]+[A-Z0-9]*,\s*Array<BestHTTP::SecureProtocol::Org::BouncyCastle::Asn1::X509::X509CertificateStructure\*>\*\s+[A-Z]+[A-Z0-9]*\)

		//methods::obfuscated::photon::Destroy1 = 0x6B38F60 + GameAssembly;
		methods::obfuscated::photon::Destroy2 = 0x74420E0 + GameAssembly;
		methods::obfuscated::photon::Destroy3 = 0x74397D0 + GameAssembly;
		//methods::obfuscated::photon::Destroy4 = 0x6B2E4B0 + GameAssembly;
		methods::obfuscated::photon::Destroy5 = 0x7439B50 + GameAssembly;
		methods::obfuscated::photon::Destroy6 = 0x7435900 + GameAssembly;
		// PhotonDestroy search term -> "METHOD(void, (Photon::Pun::PhotonView*, MethodInfo*), "System.Void "

		methods::obfuscated::photon::photonInstantiateAssets = 0x7130780 + GameAssembly; // bool      the one with double bool (1st result)
		methods::obfuscated::photon::photonInstantiate = 0x80CE790 + GameAssembly; // no bool
		// results without dictionaries, REGEX::
		// \(Il2CppString\* [a-zA-Z_][a-zA-Z0-9_]*, UnityEngine::Vector3 [a-zA-Z_][a-zA-Z0-9_]*, UnityEngine::Quaternion [a-zA-Z_][a-zA-Z0-9_]*, UnityEngine::Vector3 [a-zA-Z_][a-zA-Z0-9_]*, uint8_t [a-zA-Z_][a-zA-Z0-9_]*

		/// RRPhotonPlayer* KPDBONCIMNC     PhotonPlayer* HENKGHFDPIB <- update this every update so it's ez plz
		methods::obfuscated::photon::get_PhotonPlayer = (uintptr_t)FindMethod("Assembly-CSharp", "", "Player", "get_PhotonPlayer", 0, 0);
		methods::obfuscated::photon::PhotonPlayerToString = 0x9F2450 + GameAssembly; // PhotonPlayer.h, first result of search term: "	Il2CppString* "
		methods::obfuscated::photon::PhotonPlayerToStringFull = 0x9F3290 + GameAssembly; // second result of above search term      
		methods::obfuscated::photon::getActorNumber = 0x71150A0 + GameAssembly; // \PhotonRealtime\__NO_NAMESPACE__\, first result of search term -> "METHOD(int32_t, (PhotonPlayer*,"
		methods::obfuscated::photon::get_isMasterClient = 0x7065D50 + GameAssembly; // PhotonPlayer.h, fifth result of search term -> "METHOD(bool, (PhotonPlayer*, MethodInfo*)"

		methods::obfuscated::photon::OpRaiseEvent = 0x710D8B0 + GameAssembly; // bool\s+[A-Z]+[A-Z0-9]*(\s*\(\s*uint8_t\s+[A-Z]+[A-Z0-9]*,\s*Il2CppObject\*\s+[A-Z]+[A-Z0-9]*,\s*[A-Z]+[A-Z0-9]*\*\s+[A-Z]+[A-Z0-9]*,\s*ExitGames::Client::Photon::SendOptions\s+[A-Z]+[A-Z0-9]*\))
		methods::obfuscated::photon::OnEvent = 0x7131140 + GameAssembly; // search term (in PhotonNetwork class) -> "METHOD(void, (UnityEngine::GameObject*, bool, "
		methods::obfuscated::photon::Destroy1 = 0x713D530 + GameAssembly; // PhotonDestroy Search Term -> "METHOD(void, (Photon::Pun::PhotonView*, MethodInfo*), "System.Void " first result
		methods::obfuscated::photon::Destroy4 = 0x7142DF0 + GameAssembly; // PhotonDestroy Search Term -> "METHOD(void, (Photon::Pun::PhotonView*, MethodInfo*), "System.Void " fourth result
		methods::obfuscated::photon::setMasterClient = 0x713B2C0 + GameAssembly; // search term (in PhotonNetwork class) -> "Method(bool, (RRPhotonPlayer*"
		methods::obfuscated::photon::photonPlayerList = 0x7139D70 + GameAssembly; // "*>, (bool, MethodInfo*), "System.Collections.Generic.IReadOnlyList<" <- Search Term first result


		return true;
	}
}