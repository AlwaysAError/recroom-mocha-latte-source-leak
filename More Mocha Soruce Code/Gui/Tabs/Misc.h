#pragma once
#include "../../Modules/Callbacks/Jedi.h"

void OrbitThread(void* null);
void SpawnOrbitObject(void* null);

void CGui::MiscTab(ImGuiStyle& style) {

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, style.ItemInnerSpacing);
    ImGui::PushFont(m_Fonts.BigFont);
    {
        ImGui::TextDisabled("Misc Modules");
    }
    ImGui::PopFont();
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4());
    ImGui::BeginChild("Misc Modules", ImVec2(0, (ImGui::GetFontSize() * 2 + style.WindowPadding.y * 4 + style.ItemInnerSpacing.y) + (style.WindowPadding.y * 2 + ImGui::GetFontSize() * 6 + style.ItemInnerSpacing.y * 3) + (ImGui::GetFontSize() + style.WindowPadding.y * 2) * 60), ImGuiChildFlags_Border);
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
    {
        ImAdd::ToggleButtonClassic("FOV Slider", &globals::Ihooks::set_FieldOfView);

        if (globals::Ihooks::set_FieldOfView) {

            ImGui::Indent(10);
            ImAdd::BeginHighlightGroup();

            ImAdd::SliderInt("FOV", &globals::fov::fov, 1, 180); // setting fov beyond 180 bugs the camera out completely, default value is 68, sprint value is 88.4
            ImAdd::ToggleButtonClassic("Zoom Toggle", &globals::fov::zoomToggle);
            ImGui::SetItemTooltip("Optifine Zoom keybind is 'R'");

            if (globals::fov::zoomToggle)
                ImAdd::SliderInt("Zoom FOV", &globals::fov::zoomFov, 1, 180);

            ImAdd::EndHighlightGroup();
            ImGui::Indent(-10);
        }

        ImGui::Separator();
        ImGui::PushItemWidth(50);
        ImGui::InputFloat("Size##22", &globals::headscale);
        ImGui::PopItemWidth();
        if (ImAdd::Button("Change Head Size##22", ImVec2(-0.1f, 0))) {
            if (localPlayer.loadingStage >= LoadingStage::LOADED) {
                RecRoomPlayer* localPlayerPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);
                if (localPlayerPlayer->get_IsInitialized())
                    localPlayerPlayer->SetHeadScale(globals::headscale);
            }
        }
        ImGui::SetItemTooltip("Change your player's head size!");

        ImGui::Separator();

        if (ImAdd::ToggleButton("Object Orbit", &globals::orbit::toggle))
        {
            if (globals::orbit::toggle)
            {
                newThread(&OrbitThread, nullptr); // we dont need mutex here cause we only use localplayer by reference
            }
            else
            {
                globals::orbit::orbitThreadRun = false;
                globals::orbit::orbitObjects.clear();
            }
        }
        ImGui::SetItemTooltip("Turn off orbit when switching rooms or you will crash. \nCustomizable with Assets Spawn.");

        if (globals::orbit::toggle) {

            ImGui::InputFloat("Object Distance", &globals::orbit::objectDistance);
            ImGui::InputFloat("Object Height", &globals::orbit::objectHeight);
            ImGui::InputFloat("Speed", &globals::orbit::speed);

            if (ImAdd::Button("Spawn Orbit Object", ImVec2(-0.1f, 0))) // instantiate must be on one of unity's threads or we crash ywy
            {
                newThread(&SpawnOrbitObject, nullptr);
            }
            ImGui::SetItemTooltip("Do not spam this or you will crash.");
        }

        ImGui::Separator();

        ImGui::InputTextWithHint("##123123355", "coolshit", &globals::chatMessage);
        ImGui::SetItemTooltip("Uncensored, unlogged, unparsed chat message.");
        if (ImGui::Button("Send GYATT"))
        {
            EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::SendChatMessage);
        }
        ImGui::SetItemTooltip("Send chat message. \nSidenote: this doesn't work in vanish.");
        
        ImGui::Separator();

        ImGui::InputTextWithHint("##8911", "put message here", &globals::messageBuffer);

        if (ImAdd::Button("Broadcast Announcement", ImVec2(-0.1f, 0))) {
            EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::ShowNotificationAll);
        }

        ImGui::Separator();

        if (ImGui::CollapsingHeader("Announcement CV2")) {

            ImGui::Indent(10);
            ImAdd::BeginHighlightGroup();

            ImGuiColorEditFlags misc_flags = ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_AlphaPreviewHalf | ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoOptions;

            {
                const char* items[] = { "Upper", "Lower" };
                int current_item = globals::bannerNotif::notificationPosition;

                ImGui::PushItemWidth(200);
                if (ImGui::Combo("Banner Position ##324324", &current_item, items, IM_ARRAYSIZE(items))) {
                    globals::bannerNotif::notificationPosition = current_item;
                }
                ImGui::PopItemWidth();
                ImGui::SetItemTooltip("Banner position.");
            }

            ImGui::PushItemWidth(200);
            ImGui::InputFloat("Duration ##973849", &globals::bannerNotif::notificationDuration);
            ImGui::PopItemWidth();
            ImGui::SetItemTooltip("Duration in seconds.");

            ImGui::InputTextWithHint("##234324", "put title text here", &globals::bannerNotif::titleText);

            ImGui::ColorEdit4("Title Text Color", (float*)&globals::bannerNotif::titleTextColor, ImGuiColorEditFlags_NoInputs | misc_flags);
            ImGui::SetItemTooltip("Title text color.");
            ImGui::ColorEdit4("TitleBg Text Color", (float*)&globals::bannerNotif::titleTextBackgroundColor, ImGuiColorEditFlags_NoInputs | misc_flags);
            ImGui::SetItemTooltip("Title background text color.");

            {
                const char* items[] = { "Small", "Medium", "Large" };
                int current_item = globals::bannerNotif::titleTextSize;

                ImGui::PushItemWidth(200);
                if (ImGui::Combo("Title Text Size ##2342342", &current_item, items, IM_ARRAYSIZE(items))) {
                    globals::bannerNotif::titleTextSize = current_item;
                }
                ImGui::PopItemWidth();
                ImGui::SetItemTooltip("Title text size.");
            }

            ImGui::InputTextWithHint("##234356", "put main text here", &globals::bannerNotif::mainText);

            ImGui::ColorEdit4("Main Text Color", (float*)&globals::bannerNotif::mainTextColor, ImGuiColorEditFlags_NoInputs | misc_flags);
            ImGui::SetItemTooltip("Main text color.");
            ImGui::ColorEdit4("MainBg Text Color", (float*)&globals::bannerNotif::mainTextBackgroundColor, ImGuiColorEditFlags_NoInputs | misc_flags);
            ImGui::SetItemTooltip("Main background text color.");

            {
                const char* items[] = { "Small", "Medium", "Large" };
                int current_item = globals::bannerNotif::mainTextSize;

                ImGui::PushItemWidth(200);
                if (ImGui::Combo("Main Text Size ##345435", &current_item, items, IM_ARRAYSIZE(items))) {
                    globals::bannerNotif::mainTextSize = current_item;
                }
                ImGui::PopItemWidth();
                ImGui::SetItemTooltip("Main text size.");
            }

            ImGui::InputTextWithHint("##123523", "put left text here", &globals::bannerNotif::leftSideText);
            ImGui::SetItemTooltip("Text that shows up left of main text.");
            ImGui::InputTextWithHint("##678678", "put right text here", &globals::bannerNotif::rightSideText);
            ImGui::SetItemTooltip("Text that shows up right of main text.");

            if (ImGui::Button("Broadcast Announcement ##39834")) {
                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::ShowBannerNotificationAll);
            }

            ImAdd::EndHighlightGroup();
            ImGui::Indent(-10);
        }

        ImGui::Separator();

        {
            const char* items[] = { "LevelUp", "Cheer", "BlowOutCandles" };
            int current_item = globals::levelUpFeedback;

            ImGui::PushItemWidth(200);
            if (ImGui::Combo("Level Up Feedback Type ##2342346", &current_item, items, IM_ARRAYSIZE(items))) {
                globals::levelUpFeedback = current_item;
            }
            ImGui::PopItemWidth();
            ImGui::SetItemTooltip("Type of Level Up animation to play. \n(this is for player list \"Level Up\")");
        }

        ImGui::SeparatorText("Fling Config");

        ImAdd::ToggleButtonClassic("Random ##89734", &globals::fling::random);

        if (!globals::fling::random) {

            static float flingVelocity[3] = { 0.0f, 0.5f, 0.0f };

            ImGui::InputFloat3("Velocity", flingVelocity);
            ImGui::SetItemTooltip("Velocity to set.");

            globals::fling::velocity.x = flingVelocity[0];
            globals::fling::velocity.y = flingVelocity[1];
            globals::fling::velocity.z = flingVelocity[2];
        }
        else {

            ImGui::Indent(10);
            ImAdd::BeginHighlightGroup();

            ImGui::InputFloat2("X | Min/Max ##33", globals::fling::randomVelocityX);
            ImGui::InputFloat2("Y | Min/Max ##33", globals::fling::randomVelocityY);
            ImGui::InputFloat2("Z | Min/Max ##33", globals::fling::randomVelocityZ);

            ImAdd::EndHighlightGroup();
            ImGui::Indent(-10);
        }

        ImGui::PushItemWidth(50);
        ImGui::InputFloat("Multiplier ##56565", &globals::fling::multiplier);
        ImGui::PopItemWidth();
        ImGui::SetItemTooltip("Multiplier for the velocity.");

        ImGui::Separator();

        ImAdd::ToggleButtonClassic("Camera TMZ Mode", &globals::CameraTMZMode);

        if (globals::CameraTMZMode) {
            if (ImGui::Button("Select Camera")) {
                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::SelectTMZCamera);
            }
        }
        ImGui::SetItemTooltip("Hold the ShareCamera then press this to select it for TMZ Mode. \nYou will crash if the camera is deleted.");

        if (ImGui::Button("Clear Camera Selection")) {
            shareCameraPV = nullptr;
        }
        ImGui::SetItemTooltip("Clear the selected camera data. \nPress this if your camera has been deleted while TMZ Mode was toggled off.");

        ImGui::Separator();

        if (ImAdd::Button("Jew Royalty##22", ImVec2(-0.1f, 0))) {
            EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::SetMasterClientTarget, localPlayer.photonPlayer);
        }

        if (ImAdd::Button("Delete All Objects##22", ImVec2(-0.1f, 0))) {
            EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::DeleteAll);
        }

        if (ImGui::Button("Shrink-Ray (everthing)")) {

            if (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer)) {
                PhotonNetwork::set_MasterClient(localPlayer.photonPlayer);
                Sleep(500);
            }

            Il2CppArray* objects = UObject::FindObjectsOfType("UnityEngine.GameObject");

            for (int i = 0; i < objects->max_length; i++) {
                GameObject* gameObject = il2cpp_array_get(objects, GameObject*, i);

                if (gameObject != nullptr) {
                    CreationObject* creationObjectComponent = (CreationObject*)gameObject->GetComponent("RecRoom.Core.Creation.CreationObject");

                    if (creationObjectComponent != nullptr) {

                        if (creationObjectComponent->get_Initialized()) {

                            for (int j = 0; j < 3; j++) {
                                while (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer)) {
                                    PhotonNetwork::set_MasterClient(localPlayer.photonPlayer);
                                    Sleep(300);
                                }

                                bool result = creationObjectComponent->Scale(globals::gruWeapons::scale);

                                if (result) break;
                            }
                        }
                    }
                }
            }
        }
        ImGui::SetItemTooltip("If you don't have royalty you will crash!");
        ImGui::SameLine();
        ImGui::PushItemWidth(50);
        ImGui::InputFloat("Size##21", &globals::gruWeapons::scale);
        ImGui::PopItemWidth();

        if (ImGui::Button("Freeze-Gun (everthing)")) {

            if (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer)) {
                PhotonNetwork::set_MasterClient(localPlayer.photonPlayer);
                Sleep(500);
            }

            Il2CppArray* objects = UObject::FindObjectsOfType("UnityEngine.GameObject");

            for (int i = 0; i < objects->max_length; i++) {
                GameObject* gameObject = il2cpp_array_get(objects, GameObject*, i);

                if (gameObject != nullptr) {
                    CreationObject* creationObjectComponent = (CreationObject*)gameObject->GetComponent("RecRoom.Core.Creation.CreationObject");

                    if (creationObjectComponent != nullptr) {

                        if (creationObjectComponent->get_Initialized()) {

                            bool result = creationObjectComponent->get_IsFrozen();

                            if (globals::gruWeapons::frozen != result) {

                                while (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer)) {
                                    PhotonNetwork::set_MasterClient(localPlayer.photonPlayer);
                                    Sleep(300);
                                }

                                creationObjectComponent->set_IsFrozen(globals::gruWeapons::frozen);
                            }
                        }
                    }
                }
            }
        }
        ImGui::SetItemTooltip("If you don't have royalty you will crash!");
        ImGui::SameLine();
        ImAdd::ToggleButtonClassic("Frozen", &globals::gruWeapons::frozen);

        if (ImGui::Button("Sticky-Fingers (everthing)")) {

            if (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer)) {
                PhotonNetwork::set_MasterClient(localPlayer.photonPlayer);
                Sleep(500);
            }

            Il2CppArray* objects = UObject::FindObjectsOfType("UnityEngine.GameObject");

            for (int i = 0; i < objects->max_length; i++) {
                GameObject* gameObject = il2cpp_array_get(objects, GameObject*, i);

                if (gameObject != nullptr) {
                    CreationObject* creationObjectComponent = (CreationObject*)gameObject->GetComponent("RecRoom.Core.Creation.CreationObject");

                    if (creationObjectComponent != nullptr) {

                        if (creationObjectComponent->get_Initialized()) {

                            bool result = creationObjectComponent->get_IsGrabbable();

                            if (globals::gruWeapons::grabbale != result) {

                                while (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer)) {
                                    PhotonNetwork::set_MasterClient(localPlayer.photonPlayer);
                                    Sleep(300);
                                }

                                creationObjectComponent->set_IsGrabbable(globals::gruWeapons::grabbale);
                            }
                        }
                    }
                }
            }
        }
        ImGui::SetItemTooltip("If you don't have royalty you will crash!");

        ImGui::SameLine();
        ImAdd::ToggleButtonClassic("Grabbale", &globals::gruWeapons::grabbale);

        /// recolor
#ifdef lopoksok
        if (ImGui::Button("Recolor (everthing)")) {

            if (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer)) {
                PhotonNetwork::set_MasterClient(localPlayer.photonPlayer);
                Sleep(500);
            }

            Il2CppArray* objects = UObject::FindObjectsOfType("UnityEngine.GameObject");

            for (int i = 0; i < objects->max_length; i++) {
                GameObject* gameObject = il2cpp_array_get(objects, GameObject*, i);

                if (gameObject != nullptr) {
                    CreationObject* creationObjectComponent = (CreationObject*)gameObject->GetComponent("RecRoom.Core.Creation.CreationObject");

                    if (creationObjectComponent != nullptr) {

                        if (creationObjectComponent->get_Initialized()) {

                            bool result = creationObjectComponent->get_SupportsRecoloring();

                            if (result) {

                                while (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer)) {
                                    PhotonNetwork::set_MasterClient(localPlayer.photonPlayer);
                                    Sleep(300);
                                }

                                creationObjectComponent->set_ColorOverride(globals::gruWeapons::color);
                            }
                        }
                    }
                }
            }
        }
        ImGui::SetItemTooltip("If you don't have royalty you will crash!");
        ImGui::SameLine();

        Color internalRecolorColor = globals::gruWeapons::color;

        ImGui::InputFloat("R ##8734", &internalRecolorColor.r);
        ImGui::InputFloat("G ##8734", &internalRecolorColor.g);
        ImGui::InputFloat("B ##8734", &internalRecolorColor.b);
        ImGui::InputFloat("A ##8734", &internalRecolorColor.a);


        globals::gruWeapons::color = internalRecolorColor;

        /// recolor stop
#endif

        ImGui::Separator();

        if (ImAdd::Button("Spawn Jedi Object", ImVec2(-0.1f, 0))) {

            EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::SpawnJediObject);
            notify.PushNotification<ImVec4(0, 1, 0.2, 1), 3.0f>(m_pTextures->tStar, "Jedi Object Spawned.");
        }
        ImGui::SetItemTooltip("Spawn a prefab for Jedi.");

        ImAdd::ToggleButtonClassic("Jedi: Dominant Hand", &globals::jedi::dominantHand);
        ImGui::SetItemTooltip("Toggle whether Jedi will place the item in the dominant hand.");

        ImAdd::ToggleButtonClassic("Jedi: Legacy Mode", &globals::jedi::legacyMode);
        ImGui::SetItemTooltip("Toggle whether Jedi will use Legacy Mode.");

        ImGui::Separator();

        ImAdd::ToggleButtonClassic("Promotion: Override Roles", &globals::roomRolePromotion);
        ImGui::SetItemTooltip("Toggle whether Promotion will override role permissions. \nSide-Note: this isn't very stable.");

        ImGui::Separator();

        ImGui::PushItemWidth(150);
        ImGui::InputFloat("Exterminate Velocity", &globals::exterminateVelocity);
        ImGui::PopItemWidth();
        ImGui::SetItemTooltip("Velocity of the exterminate bullet.");

        ImGui::Separator();

        ImAdd::ToggleButtonClassic("Watch Menu Prototype", &globals::watchMenuTest);
        ImGui::SetItemTooltip("Known incompatibility issue with Chams.\n Menu contains alot of bugs with a side of some lag.");

        ImGui::Separator();

        if (pHookManager->hookPriority == HookManager::HookType::PAGEGUARD) {
            if (ImAdd::ToggleButtonClassic("Quest Skip", &globals::veh::questskip))
                pHookManager->UpdateHooks();
        }
        else {
            ImAdd::ToggleButtonClassic("Quest Skip", &globals::Ihooks::GetNextGameplayRoomIndex);
        }
        ImGui::SetItemTooltip("Requires Master Client. \nEnter boss room after first level.");

        if (ImAdd::Button("Skip to Quest Boss Room", ImVec2(-0.1f, 0))) {

            QuestManager* manager = QuestManager::get_Instance();

            if (manager != nullptr)
                manager->set_DefaultRoomIndex(GetField<int32_t>(manager, 336) - 1); // total room count - 1

        }
        ImGui::SetItemTooltip("Requires Master Client. \nEnter boss room when starting quest. \nPress this after quest is started but before you go to first level.");

        if (ImAdd::Button("Give S+ Rank", ImVec2(-0.1f, 0))) {

            QuestManager* manager = QuestManager::get_Instance();

            if (manager != nullptr) {

                for (auto& [photonPlayer, _] : cachedPlayerlist) {

                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> distr(5000000, 10000000);

                    manager->MasterAddPlayerPointsValue(photonPlayer, distr(gen));
                }
            }
        }
        ImGui::SetItemTooltip("Requires Master Client. Gives you alot of combat points.");
        
        if (ImAdd::Button("Generate Quest Gift", ImVec2(-0.1f, 0))) {

            EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::GenerateQuestGift);
        }
        ImGui::SetItemTooltip("Generate a quest gift, game must be started. \nRate Limit: every 60 seconds.");
        
        ImGui::Separator();

        ImGui::InputTextWithHint("##211154", "Put Text Here", &globals::textBuffer);

        if (ImAdd::Button("Rename Text Objects", ImVec2(-0.1f, 0))) {

            EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::RenameAllTexts);

        }

        ImGui::SetItemTooltip("Renames all text objects in the room. \nRequires Master Client. \nKnown crash issue when someone is selecting the text object. \nSidenote: this is very buggy.");

        ImGui::Separator();

        if (ImAdd::Button("Destroy Sit Seats", ImVec2(-0.1f, 0))) {

            if (localPlayer.loadingStage >= LoadingStage::LOADED)
            {
                RecRoomPlayer* localPlayerPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);

                if ((localPlayerPlayer != nullptr) && localPlayerPlayer->get_IsInitialLoadFinished()) {

                    Component* headComponent = localPlayerPlayer->get_Head();
                    int32_t childCount = headComponent->get_transform()->get_ChildCount();
                    for (int i = 0; i < childCount; i++) {

                        GameObject* childGO = headComponent->get_transform()->GetChild(i)->get_gameObject();

                        if ((childGO != nullptr) && (childGO->GetComponent("RecRoom.Core.UGCSeatManagementProxy") != nullptr)) {
                            childGO->Destroy();
                        }
                    }
                }
            }
        }

        ImGui::SetItemTooltip("Destroys the Seats from Sit module client side.");

#ifdef PROD
        if (!clothingEnabled || localPlayerExists)
            ImGui::BeginDisabled();

        ImGui::Separator();
        ImAdd::ToggleButtonClassic("Clothing", &globals::Ihooks::chai);
        ImGui::SetItemTooltip("Enable clothing if you own it.");

        if (!clothingEnabled || localPlayerExists)
            ImGui::EndDisabled();
#endif

        ImGui::Separator();

        {
            const char* items[] = { "Token", "Clothes" };
            int current_item = globals::photon::giftbox::giftType;

            ImGui::PushItemWidth(200);
            if (ImGui::Combo("GiftType ##23423411", &current_item, items, IM_ARRAYSIZE(items))) {
                globals::photon::giftbox::giftType = static_cast<globals::photon::giftbox::GiftType>(current_item);
            }
            ImGui::PopItemWidth();
        }

        ImGui::InputTextWithHint("##0827347", "clothingBuffer", &globals::photon::giftbox::clothingBuffer);
        ImGui::InputTextWithHint("##1234897", "messageBuffer", &globals::photon::giftbox::messageBuffer);
        ImGui::InputInt("tokenAmount", &globals::photon::giftbox::tokenAmount);
        ImGui::InputInt("giftContext", &globals::photon::giftbox::giftContext);
        
        ImGui::Separator();
        
        ImAdd::ToggleButtonClassic("Enable Sit On Head Loop", &globals::enableSitLoop);
        ImGui::SetItemTooltip("Click \"SitOnHead\" in playerlist then toggle this to use. \nYou will crash if the target unloads and loop is still on.");
        
        ImGui::InputFloat("Height offset", &globals::sitLoopOffset);
        ImGui::SetItemTooltip("Height offset from the head of the target player.");

        if (ImGui::Button("Destroy Sit On Head Seat"))
        {
            EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::DestroySitOnTargetSeat);
        }
        ImGui::SetItemTooltip("Destroy the SitOnHeadSeat.");

        

    }
    ImGui::EndChild();

}