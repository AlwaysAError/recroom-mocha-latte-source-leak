#pragma once

static bool lastFrameChamsRendered = false;

ChamsSettings cachedChamsSettings{
    Vector3(1.0f, 1.0f, 1.0f),
    ImVec4(1.0, 1.0, 1.0, 1.0),
    1.0f,
    0
};

void Chams() {

    if (globals::chams::toggle) {

        std::unique_lock<std::timed_mutex> lock(playerlistMutex, std::defer_lock);

        if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {
            for (auto& [photonPlayer, player] : cachedPlayerlist) {
                if (player.loadingStage >= LoadingStage::LOADED && !player.isLocalPlayer && !player.hasChamsChild) {

                    RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(player.photonActorID);

                    if (playerPlayer != nullptr) {

                        if (playerPlayer->get_IsInitialized() && playerPlayer->get_IsInitialLoadFinished()) {

                            Transform* headTransform = playerPlayer->get_Head()->get_transform();
                            Vector3 zeroPos = { 0, 0, 0 };

                            void* shader = Shader::shaderFind(il2cpp_string_new_spoof("UI/Default-ZTestAlways"));

                            GameObject* gameObject = GameObject::CreatePrimitive((PrimitiveType)globals::chams::settings.shape);

                            if (gameObject == nullptr)
                                continue;

                            Renderer* renderer = (Renderer*)gameObject->GetComponent("Renderer");

                            if (renderer == nullptr)
                                continue;

                            Material* material = Material::getDefaultMaterial();

                            if (material == nullptr)
                                continue;

                            material->setShader(shader);
                            ImVec4 color = ImVec4( // RGBA but 1 is max 0 is min, anything over 1 is glow
                                globals::chams::settings.color.x * globals::chams::settings.glow,
                                globals::chams::settings.color.y * globals::chams::settings.glow,
                                globals::chams::settings.color.z * globals::chams::settings.glow,
                                globals::chams::settings.color.w);


                            material->setColor(color);
                            renderer->setMaterial(material);

                            Transform* transform = gameObject->get_transform();

                            if (transform == nullptr)
                                continue;

                            Vector3 scale = globals::chams::settings.scale;

                            transform->set_localScale(scale);
                            transform->SetParent(headTransform);
                            transform->set_localPosition(zeroPos);

                            player.chamsObject = gameObject;
                            player.hasChamsChild = true;

                            cachedChamsSettings = globals::chams::settings;
                        }
                    }
                }
            }

            if (globals::chams::settings != cachedChamsSettings) {

                for (auto& [photonPlayer, player] : cachedPlayerlist) {
                    if (player.loadingStage >= LoadingStage::LOADED && !player.isLocalPlayer && player.hasChamsChild) {

                        RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(player.photonActorID);

                        if (playerPlayer != nullptr) {

                            if (globals::chams::settings.shape != cachedChamsSettings.shape) {

                                player.chamsObject->Destroy();
                                player.chamsObject = GameObject::CreatePrimitive((PrimitiveType)globals::chams::settings.shape);

                            }

                            void* shader = Shader::shaderFind(il2cpp_string_new_spoof("UI/Default-ZTestAlways"));

                            GameObject* gameObject = player.chamsObject;

                            if (gameObject == nullptr)
                                continue;

                            Renderer* renderer = (Renderer*)gameObject->GetComponent("Renderer");

                            if (renderer == nullptr)
                                continue;

                            Material* material = Material::getDefaultMaterial();

                            if (material == nullptr)
                                continue;

                            material->setShader(shader);
                            ImVec4 color = ImVec4( // RGBA but 1 is max 0 is min, anything over 1 is glow
                                globals::chams::settings.color.x * globals::chams::settings.glow,
                                globals::chams::settings.color.y * globals::chams::settings.glow,
                                globals::chams::settings.color.z * globals::chams::settings.glow,
                                globals::chams::settings.color.w);

                            material->setColor(color);
                            renderer->setMaterial(material);

                            Transform* transform = gameObject->get_transform();

                            if (transform == nullptr)
                                continue;

                            Vector3 scale = globals::chams::settings.scale;

                            transform->set_localScale(scale);

                            if (globals::chams::settings.shape != cachedChamsSettings.shape) {
                                Transform* headTransform = playerPlayer->get_Head()->get_transform();
                                Vector3 zeroPos = { 0, 0, 0 };

                                transform->SetParent(headTransform);
                                transform->set_localPosition(zeroPos);

                                player.chamsObject = gameObject;
                            }
                        }
                    }
                }

                cachedChamsSettings = globals::chams::settings;
            }

            lock.unlock();
            lastFrameChamsRendered = true;
        }
        else {
            Log::error("playerlistMutex timed out in Chams 1!");
        }
    }
    else {
        if (lastFrameChamsRendered) {
            std::unique_lock<std::timed_mutex> lock(playerlistMutex, std::defer_lock);

            if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {
                for (auto& [photonPlayer, player] : cachedPlayerlist) {
                    if (player.loadingStage >= LoadingStage::LOADED && player.hasChamsChild) {

                        player.chamsObject->Destroy();
                        player.chamsObject = nullptr;
                        player.hasChamsChild = false;

                    }
                }

                lock.unlock();

                lastFrameChamsRendered = false;
            }
            else {
                Log::error("playerlistMutex timed out in Chams 2!");
            }
        }
    }
}