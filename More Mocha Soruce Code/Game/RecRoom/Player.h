#pragma once

struct PlayerBody;


enum HardwareType
{
    Desktop_Valve = 0,
    Desktop_Oculus = 1,
    PS4 = 2,
    Desktop_MicrosoftVR = 3,
    Desktop_VRMissing = 4,
    OculusQuest = 5,
    iOS = 6,
    XboxOne = 7,
    AndroidMobile = 8,
    PS5 = 9,
    XboxSeries = 10,
    PicoNeo3 = 11,
    PicoPhoenix = 12,
    NintendoSwitch = 13,
};

enum RecNetDeviceClass
{
    Unknown = 0,
    VR = 1,
    Screen = 2,
    Mobile = 3,
    VRLow = 4,
    Quest2 = 5,
};

enum class RoomDoorInviteMode
{
    UnknownMode = 0,
    Normal = 1,
    PartyAutoFollow = 2,
    EveryoneAutoFollow = 3,
};

std::string RecPlayerHardwareTypeToString(HardwareType hardwareType)
{
    switch (hardwareType)
    {
    case Desktop_Valve: return "Desktop Valve";
    case Desktop_Oculus: return "Desktop Oculus";
    case PS4: return "PS4";
    case Desktop_MicrosoftVR: return "Desktop MicrosoftVR";
    case Desktop_VRMissing: return "Desktop VRMissing";
    case OculusQuest: return "OculusQuest";
    case iOS: return "iOS";
    case XboxOne: return "XboxOne";
    case AndroidMobile: return "AndroidMobile";
    case PS5: return "PS5";
    case XboxSeries: return "XboxSeries";
    case PicoNeo3: return "PicoNeo3";
    case PicoPhoenix: return "PicoPhoenix";
    case NintendoSwitch: return "NintendoSwitch";
    default: return "Unsupported Value";
    }
}

std::string RecPlayerRecNetDeviceClassToString(RecNetDeviceClass recNetDeviceClass)
{
    switch (recNetDeviceClass)
    {
    case Unknown: return "Unknown";
    case VR: return "VR";
    case Screen: return "Screen";
    case Mobile: return "Mobile";
    case VRLow: return "VRLow";
    case Quest2: return "Quest2";
    default: return "Unsupported Value";
    }
}

struct RecRoomPlayer : MonoBehaviourPun
{
    using get_Ping_t = int32_t(*)(RecRoomPlayer* player);

    int32_t get_Ping()
    {
        if (this == nullptr) return -1;
        auto func = static_cast<get_Ping_t>(reinterpret_cast<void*>(methods::Player::get_Ping));
        return func(this);
    }

    using get_HardwareType_t = HardwareType(*)(RecRoomPlayer* player);

    HardwareType get_HardwareType()
    {
        if (this == nullptr) return Desktop_Valve;
        auto func = static_cast<get_HardwareType_t>(reinterpret_cast<void*>(methods::Player::get_HardwareType));
        return func(this);
    }

    using get_RecNetDeviceClass_t = RecNetDeviceClass(*)(RecRoomPlayer* player);

    RecNetDeviceClass get_RecNetDeviceClass()
    {
        if (this == nullptr) return Unknown;
        auto func = static_cast<get_RecNetDeviceClass_t>(reinterpret_cast<void*>(
            methods::Player::get_RecNetDeviceClass));
        return func(this);
    }

    using get_HasVisibleRecRoomPlus_t = bool(*)(RecRoomPlayer* player);

    bool get_HasVisibleRecRoomPlus()
    {
        if (this == nullptr) return false;
        auto func = static_cast<get_HasVisibleRecRoomPlus_t>(reinterpret_cast<void*>(
            methods::Player::get_HasVisibleRecRoomPlus));
        return func(this);
    }

    using get_IsFriend_t = bool(*)(RecRoomPlayer* player);

    bool get_IsFriend()
    {
        if (this == nullptr) return false;
        auto func = static_cast<get_IsFriend_t>(reinterpret_cast<void*>(methods::Player::get_IsFriend));
        return func(this);
    }

    using get_AllToolsOnPlayer_t = Il2CppArray* (*)(RecRoomPlayer* player);

    Il2CppArray* get_AllToolsOnPlayer()
    {
        if (this == nullptr) return nullptr;
        auto func = static_cast<get_AllToolsOnPlayer_t>(reinterpret_cast<void*>(methods::Player::get_AllToolsOnPlayer));
        return func(this);
    }

    using GetFromActorNumber_t = RecRoomPlayer* (*)(int id);

    static RecRoomPlayer* GetFromActorNumber(int id)
    {
        auto func = static_cast<GetFromActorNumber_t>(reinterpret_cast<void*>(methods::Player::GetFromActorNumber));
        return func(id);
    }

    using get_RightHand_t = Component* (*)(RecRoomPlayer* player);

    Component* get_RightHand()
    {
        if (this == nullptr) return nullptr;
        auto func = static_cast<get_RightHand_t>(reinterpret_cast<void*>(methods::Player::get_RightHand));
        return func(this);
    }

    using get_LeftHand_t = Component* (*)(RecRoomPlayer* player);

    Component* get_LeftHand()
    {
        if (this == nullptr) return nullptr;
        auto func = static_cast<get_LeftHand_t>(reinterpret_cast<void*>(methods::Player::get_LeftHand));
        return func(this);
    }

    using get_CurrentHeadPosition_t = Vector3(*)(RecRoomPlayer* player);

    Vector3 get_CurrentHeadPosition()
    {
        if (this == nullptr) return {0, 0, 0};
        auto func = static_cast<get_CurrentHeadPosition_t>(reinterpret_cast<void*>(
            methods::Player::get_CurrentHeadPosition));
        return func(this);
    }

    using get_CurrentBodyPosition_t = Vector3(*)(RecRoomPlayer* player);

    Vector3 get_CurrentBodyPosition()
    {
        if (this == nullptr) return {0, 0, 0};
        auto func = static_cast<get_CurrentBodyPosition_t>(reinterpret_cast<void*>(
            methods::Player::get_CurrentBodyPosition));
        return func(this);
    }

    using get_PlayerMovement_t = void* (*)(RecRoomPlayer* player);

    void* get_PlayerMovement()
    {
        if (this == nullptr) return nullptr;
        auto func = static_cast<get_PlayerMovement_t>(reinterpret_cast<void*>(methods::Player::get_PlayerMovement));
        return func(this);
    }

    using get_IsInitialized_t = bool(*)(RecRoomPlayer* player);

    bool get_IsInitialized()
    {
        if (this == nullptr) return false;
        auto func = static_cast<get_IsInitialized_t>(reinterpret_cast<void*>(methods::Player::get_IsInitialized));
        return func(this);
    }

    using SetHeadScale_t = bool(*)(RecRoomPlayer* player, float size);

    bool SetHeadScale(float size)
    {
        if (this == nullptr) return false;
        auto func = static_cast<SetHeadScale_t>(reinterpret_cast<void*>(methods::Player::SetHeadScale));
        return func(this, size);
    }

    using set_AvatarSkeletonIsEnabled_t = bool(*)(RecRoomPlayer* player, bool enabled);

    bool set_AvatarSkeletonIsEnabled(bool enabled)
    {
        if (this == nullptr) return false;
        auto func = static_cast<set_AvatarSkeletonIsEnabled_t>(reinterpret_cast<void*>(
            methods::Player::set_AvatarSkeletonIsEnabled));
        return func(this, enabled);
    }

    using getPlayerName_t = Il2CppString* (*)(RecRoomPlayer* player);

    Il2CppString* getPlayerName()
    {
        if (this == nullptr) return nullptr;
        auto func = static_cast<getPlayerName_t>(reinterpret_cast<void*>(methods::Player::getPlayerName));
        return func(this);
    }

    using getPhotonPlayer_t = PhotonPlayer* (*)(RecRoomPlayer* player);

    PhotonPlayer* get_PhotonPlayer()
    {
        if (this == nullptr) return nullptr;
        PhotonView* pView = this->get_PhotonView();
		if (pView == nullptr) return nullptr;
        return pView->get_Owner();
    }

    using get_Head_t = Component* (*)(RecRoomPlayer* player);

    Component* get_Head()
    {
        if (this == nullptr) return nullptr;
        auto func = static_cast<get_Head_t>(reinterpret_cast<void*>(methods::Player::get_Head));
        return func(this);
    }

    using getHand_t = PlayerHand* (*)(RecRoomPlayer* player, int32_t hand);

    PlayerHand* getHand(int32_t hand)
    {
        if (this == nullptr) return nullptr;
        auto func = static_cast<getHand_t>(reinterpret_cast<void*>(methods::Player::getHand));
        return func(this, hand);
    }

    using get_TrackingSpace_t = Component* (*)(RecRoomPlayer* player);

    Component* get_TrackingSpace()
    {
        if (this == nullptr) return nullptr;
        auto func = static_cast<get_TrackingSpace_t>(reinterpret_cast<void*>(methods::Player::get_TrackingSpace));
        return func(this);
    }

    using GetRotation_t = Quaternion(*)(RecRoomPlayer* player);

    Quaternion GetRotation()
    {
        if (this == nullptr) return {0, 0, 0, 0};
        auto func = static_cast<GetRotation_t>(reinterpret_cast<void*>(methods::Player::GetRotation));
        return func(this);
    }

    using RpcAuthorityCV2EquipObject_t = void(*)(RecRoomPlayer* player, Component* tool, bool dominantHand,
                                                 bool forceEquip, bool steal);

    void RpcAuthorityCV2EquipObject(Component* tool, bool dominantHand, bool forceEquip, bool steal)
    {
        if (this == nullptr) return;
        auto func = static_cast<RpcAuthorityCV2EquipObject_t>(reinterpret_cast<void*>(
            methods::Player::RpcAuthorityCV2EquipObject));
        return func(this, tool, dominantHand, forceEquip, steal);
    }

    using get_IsInitialLoadFinished_t = bool(*)(RecRoomPlayer* player);

    bool get_IsInitialLoadFinished()
    {
        if (this == nullptr) return false;
        auto func = static_cast<get_IsInitialLoadFinished_t>(reinterpret_cast<void*>(
            methods::Player::get_IsInitialLoadFinished));
        return func(this);
    }

    using get_Body_t = PlayerBody* (*)(RecRoomPlayer* player);

    PlayerBody* get_Body()
    {
        if (this == nullptr) return nullptr;
        auto func = static_cast<get_Body_t>(reinterpret_cast<void*>(GameAssembly + 0xAC9540));
        return func(this);
    }
};

using getNetworkPlayer_t = NetworkPlayer * (*)(RecRoomPlayer* player);

NetworkPlayer* PhotonPlayer::get_NetworkPlayer()
{
    if (this == nullptr) return nullptr;
    RecRoomPlayer* rrPlayer = RecRoomPlayer::GetFromActorNumber(this->getActorNumber());

    auto func = static_cast<getNetworkPlayer_t>(reinterpret_cast<void*>(
        methods::obfuscated::photon::get_PhotonPlayer));
    return func(rrPlayer);
}

struct PlayerParty : Component
{
    enum class PartyJoinedSource
    {
        NONE = -1,
        Code = 0,
        PartyGesture = 1,
        ProfileScreen = 2,
        PeopleMenuShortcut = 3,
        InviteToPartyDialog = 4,
        PartyInviteInChat = 5,
        AutoRejoinPartyChat = 6,
        InviteOnlineFriends = 7,
        PartyInviteMessage = 8,
        OpenProfileRadialMenu = 9,
        RemoteCommand = 10,
    };

    using RpcJoinParty_t = void(*)(PlayerParty* instance, PhotonPlayer* otherPlayer, Vector3 feedbackPosition,
                                   PartyJoinedSource source);

    void RpcJoinParty(PhotonPlayer* otherPlayer, Vector3 feedbackPosition, PartyJoinedSource source)
    {
        if (this == nullptr) return;
        auto func = static_cast<RpcJoinParty_t>(reinterpret_cast<void*>(GameAssembly + 0x1E92CC0));
        return func(this, otherPlayer, feedbackPosition, source);
    }

    using get_CurrentPartyId_t = Il2CppString* (*)(PlayerParty* instance);

    Il2CppString* get_CurrentPartyId()
    {
        if (this == nullptr) return WriteIl2CppString("");
        auto func = static_cast<get_CurrentPartyId_t>(reinterpret_cast<void*>(GameAssembly + 0x1E95090));
        return func(this);
    }
};

enum class LoadingStage : int
{
    UNINITIALIZED = -1, // default stage (uninitialized in our code/game code)
    PHOTON = 0, // PhotonPlayer* exists but RecRoomPlayer* & PhotonView* are invalid.
    RECROOM = 1, // RecRoomPlayer* exists but is not initialized
    LOADED = 2 // RecRoomPlayer* exists and is initiailized
};

struct PlayerInfo
{
    // dont touch these ones
    LoadingStage loadingStage = LoadingStage::UNINITIALIZED;
    const char* DisplayName = "";
    const char* playerID = "";
    PhotonPlayer* photonPlayer = nullptr;
    GameObject* playerGameObject = nullptr;
    PhotonView* photonView = nullptr;
    int photonActorID = -1;
    int photonViewID = -1;
    bool isLocalPlayer = false;
    bool isMasterClient = false;
    bool isPlayerInCache = false;

    // extras
    bool hasBeenCrashed = false;
    bool isVanished = false;
    bool isCrashed = false;
    bool hasChamsChild = false;
    bool hitboxesExpanded = false;
    GameObject* chamsObject = nullptr;
    bool hasTriggeredCloak = false;
    bool hasGodmodeWhitelist = false;

    // protection related shit
    bool blockEvents = false;
    int bounceBackAttempts = 0;

    std::chrono::steady_clock::time_point Ev200RateLimitWindowStart;
    int Ev200RateLimitEventCount = 0;

    std::chrono::steady_clock::time_point Ev202RateLimitWindowStart;
    int Ev202RateLimitEventCount = 0;
    int Ev202TotalInstantiations = 0;
};
