#pragma once

bool hitboxesActiveLastFrame = false;

void HitboxExpander() {
    if (globals::hitboxes::toggle) {

        std::unique_lock<std::timed_mutex> lock(playerlistMutex, std::defer_lock);

        if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {
            for (auto& [photonPlayer, player] : cachedPlayerlist) {
                if (player.loadingStage >= LoadingStage::LOADED && !player.isLocalPlayer && !player.hitboxesExpanded) {

                    RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(player.photonActorID);

                    if (playerPlayer != nullptr) {

                        if (playerPlayer->get_IsInitialized() && playerPlayer->get_IsInitialLoadFinished()) {


                            for (int i = 0; i < player.playerGameObject->get_transform()->get_ChildCount(); i++) {

                                GameObject* childGO = player.playerGameObject->get_transform()->GetChild(i)->get_gameObject();

                                if (childGO != nullptr)
                                {
                                    if ((std::string(ReadIl2CppString(childGO->GetName())).find("(PlayerBodyParts)") != std::string::npos) && childGO->get_active()) {

                                        Transform* bodyCollider = childGO->get_transform()->GetChild(0)->GetChild(0);

                                        Vector3 scale{ 1.0f, 1.0f, 1.0f };

                                        if (globals::hitboxes::yToggle)
                                            scale *= globals::hitboxes::multiplier;
                                        else {
                                            scale = { scale.x * globals::hitboxes::multiplier, 1.0f, scale.z * globals::hitboxes::multiplier };
                                        }

                                        bodyCollider->set_localScale(scale);
                                        player.hitboxesExpanded = true;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            lock.unlock();

            hitboxesActiveLastFrame = true;
        }
        else {
            Log::error("playerlistMutex timed out in HitboxExpander 1!");
        }
    }
    else {
        if (hitboxesActiveLastFrame) {
            std::unique_lock<std::timed_mutex> lock(playerlistMutex, std::defer_lock);

            if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {
                for (auto& [photonPlayer, player] : cachedPlayerlist) {
                    if (player.loadingStage >= LoadingStage::LOADED && player.hitboxesExpanded) {


                        RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(player.photonActorID);

                        if (playerPlayer->get_IsInitialized() && playerPlayer->get_IsInitialLoadFinished()) {

                            for (int i = 0; i < player.playerGameObject->get_transform()->get_ChildCount(); i++) {

                                GameObject* childGO = player.playerGameObject->get_transform()->GetChild(i)->get_gameObject();

                                if (childGO != nullptr)
                                {
                                    if ((std::string(ReadIl2CppString(childGO->GetName())).find("(PlayerBodyParts)") != std::string::npos) && childGO->get_active()) {

                                        Transform* bodyCollider = childGO->get_transform()->GetChild(0)->GetChild(0);

                                        Vector3 scale{ 1.0f, 1.0f, 1.0f };

                                        bodyCollider->set_localScale(scale);
                                        player.hitboxesExpanded = false;
                                        break;

                                    }
                                }
                            }
                        }
                    }
                }

                lock.unlock();

                hitboxesActiveLastFrame = false;
            }
            else {
                Log::error("playerlistMutex timed out in HitboxExpander 2!");
            }
        }
    }
}