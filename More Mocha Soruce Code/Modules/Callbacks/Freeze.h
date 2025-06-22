#pragma once

namespace Callbacks
{
    bool FreezeTest(PhotonPlayer* targetPP) {

        ThreadFix();

        const auto internalCachedInstance = static_cast<Il2CppObject*>(OpRaiseEventCache::instance);
        const auto internalCachedEventOptions = (Il2CppObject*)OpRaiseEventCache::eventOptions;
        const auto internalCachedSendOptions = (Il2CppObject*)OpRaiseEventCache::sendOptions;

        //GameObject* pistolGO = PhotonNetwork::photonInstantiate(WriteIl2CppString("[Arena_Pistol]"), { 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 1, 1 }, 0, nullptr, false);

        if (!cachedPlayerlist.contains(targetPP)) return true;

        if (const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];
            targetPlayer.loadingStage >= LoadingStage::LOADED)
        {
            PhotonView* pv = targetPlayer.photonView; //(PhotonView*)pistolGO->GetComponent("PhotonView");

            int32_t pvid = pv->get_ViewID();

            const auto rpcPayload = Hashtable::ctor();
            rpcPayload->Add(7, (UObject*)il2cpp_value_box_spoof(FindClass("System.Int32"), &pvid));

            // event 207 destroy player
            PhotonNetwork::OpRaiseEvent(internalCachedInstance, 202, rpcPayload, internalCachedEventOptions, internalCachedSendOptions);

            const auto event204Payload = Hashtable::ctor();
            event204Payload->Add(0, (UObject*)il2cpp_value_box_spoof(FindClass("System.Int32"), &pvid));

            // event 204 related to join/leave room
            PhotonNetwork::OpRaiseEvent(internalCachedInstance, 204, event204Payload, internalCachedEventOptions, internalCachedSendOptions);

            const auto ev200payload = Hashtable::ctor();
            ev200payload->Add(0, (UObject*)il2cpp_value_box_spoof(FindClass("System.Int32"), &pvid));

            PhotonNetwork::OpRaiseEvent(internalCachedInstance, 200, event204Payload, internalCachedEventOptions, internalCachedSendOptions);
        }
        return true;
        
        /*
        PlayerInfo& targetPlayer = cachedPlayerlist[(PhotonPlayer*)targetPP];

        RecRoomPlayer* rrppl = RecRoomPlayer::GetFromActorNumber(targetPlayer.photonActorID);

        GameObject* clownGO = rrppl->get_gameObject();

        ScanAllChildren(clownGO->get_transform());

        PhotonNetwork::DestroyPlayerObjects(targetPlayer.photonActorID);
        */

    }
}