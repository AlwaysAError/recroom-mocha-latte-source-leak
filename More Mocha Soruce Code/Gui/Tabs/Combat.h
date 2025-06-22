#pragma once

void CGui::CombatTab(ImGuiStyle& style) {

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, style.ItemInnerSpacing);
    ImGui::PushFont(m_Fonts.BigFont);
    {
        ImGui::TextDisabled("Combat Modules");
    }
    ImGui::PopFont();
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4());
    ImGui::BeginChild("Combat Modules", ImVec2(0, (ImGui::GetFontSize() * 2 + style.WindowPadding.y * 3) + (ImGui::GetFontSize() + style.WindowPadding.y * 2) * 60), ImGuiChildFlags_Border);
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
    {
        ImAdd::ToggleButton("Aimbot##22", &globals::aimbot::toggle);
        ImGui::SetItemTooltip("Aimbot by mouse movement. \nKeybind is 'P'.");
        if (globals::aimbot::toggle) {
            ImGui::Indent(10);
            ImAdd::BeginHighlightGroup();

            ImAdd::SliderInt("Fov##22", &globals::aimbot::radius, 30, 200);
            ImAdd::SliderFloat("Aim Speed##22", &globals::aimbot::aimSpeed, 1, 15);
            ImAdd::SliderInt("Steps##22", &globals::aimbot::steps, 0, 300);

            ImAdd::EndHighlightGroup();
            ImGui::Indent(-10);
        }

        ImGui::Separator();

        ImAdd::ToggleButtonClassic("Fire Rate", &globals::Ihooks::get_IsOnCooldown);
        ImGui::SetItemTooltip("Turn off fire rate.");

        ImGui::Separator();

        ImAdd::ToggleButton("Auto Weapon Mods##22", &globals::autoGun::autoGunToggle);
        ImGui::SetItemTooltip("Apply weapon mods when you pickup a weapon. \nKnown crash issue when this is enabled during loading.");
        if (globals::autoGun::autoGunToggle) {

            ImGui::Indent(10);
            ImAdd::BeginHighlightGroup();

            ImAdd::ToggleButtonClassic("Multiplier Mode", &globals::autoGun::multiplierMode);

            if (globals::autoGun::multiplierMode) {
                ImAdd::ToggleButtonClassic("Fire Rate##22", &globals::autoGun::fireRate);
                if (globals::autoGun::fireRate)
                {
                    ImGui::PushItemWidth(150);
                    ImGui::InputFloat("Fire Rate##21", &globals::autoGun::fireRateMultiplier);
                    ImGui::PopItemWidth();
                }

                ImAdd::ToggleButtonClassic("Bullet Speed##22", &globals::autoGun::bulletSpeed);
                if (globals::autoGun::bulletSpeed)
                {
                    ImGui::PushItemWidth(150);
                    ImGui::InputFloat("Bullet Speed##21", &globals::autoGun::bulletSpeedMultiplier);
                    ImGui::PopItemWidth();
                }

                ImAdd::ToggleButtonClassic("Auto Bullet Speed##22", &globals::autoGun::automaticBulletSpeed);
                if (globals::autoGun::automaticBulletSpeed)
                {
                    ImGui::PushItemWidth(150);
                    ImGui::InputFloat("Auto Bullet Speed##21", &globals::autoGun::automaticBulletSpeedMultiplier);
                    ImGui::PopItemWidth();
                }

                ImAdd::ToggleButtonClassic("Ammo##22", &globals::autoGun::ammo);
                if (globals::autoGun::ammo)
                {
                    ImGui::PushItemWidth(150);
                    ImGui::InputFloat("Ammo##21", &globals::autoGun::ammoMultiplier);
                    ImGui::PopItemWidth();
                }
            }
            else {

                ImAdd::ToggleButtonClassic("Fire Rate##22", &globals::autoGun::fireRate);
                if (globals::autoGun::fireRate)
                {
                    ImGui::PushItemWidth(150);
                    ImGui::InputFloat("Fire Rate##21", &globals::autoGun::fireRateAmount);
                    ImGui::PopItemWidth();
                }

                ImAdd::ToggleButtonClassic("Bullet Speed##22", &globals::autoGun::bulletSpeed);
                if (globals::autoGun::bulletSpeed)
                {
                    ImGui::PushItemWidth(150);
                    ImGui::InputFloat("Bullet Speed##21", &globals::autoGun::bulletSpeedAmount);
                    ImGui::PopItemWidth();
                }

                ImAdd::ToggleButtonClassic("Auto Bullet Speed##22", &globals::autoGun::automaticBulletSpeed);
                if (globals::autoGun::automaticBulletSpeed)
                {
                    ImGui::PushItemWidth(150);
                    ImGui::InputFloat("Auto Bullet Speed##21", &globals::autoGun::automaticBulletSpeedAmount);
                    ImGui::PopItemWidth();
                }

                ImAdd::ToggleButtonClassic("Ammo##22", &globals::autoGun::ammo);
                if (globals::autoGun::ammo)
                {
                    ImGui::PushItemWidth(150);
                    ImGui::InputInt("Ammo##21", &globals::autoGun::ammoAmount);
                    ImGui::PopItemWidth();
                }
            }

            ImAdd::ToggleButtonClassic("Recoil and No Spread##22", &globals::autoGun::recoil);

            ImAdd::ToggleButtonClassic("Beam Gun Mods##22", &globals::autoGun::beamGunMods);
            if (globals::autoGun::beamGunMods)
            {
                ImGui::PushItemWidth(150);
                ImGui::InputInt("Beam Charge Amount##22", &globals::autoGun::beamAmount);
                ImGui::PopItemWidth();
            }

            ImAdd::ToggleButtonClassic("Burst Gun Mods##22", &globals::autoGun::burstGunMods);
            if (globals::autoGun::burstGunMods)
            {
                ImGui::PushItemWidth(150);
                ImGui::InputInt("Burst Amount##22", &globals::autoGun::burstAmount);
                ImGui::PopItemWidth();
            }

            ImAdd::ToggleButtonClassic("Prediction##22", &globals::autoGun::Prediction);

            ImAdd::EndHighlightGroup();
            ImGui::Indent(-10);
        }

        ImGui::Separator();

        ImAdd::ToggleButtonClassic("Hitbox Expander", &globals::hitboxes::toggle);
        if (globals::hitboxes::toggle) {
            ImGui::Indent(15);
            ImAdd::BeginHighlightGroup();

            ImAdd::ToggleButtonClassic("Y-Axis Toggle", &globals::hitboxes::yToggle);

            ImGui::PushItemWidth(100);
            ImGui::InputFloat("Multiplier", &globals::hitboxes::multiplier);
            ImGui::PopItemWidth();

            ImAdd::EndHighlightGroup();
            ImGui::Indent(-15);
        }

        ImGui::Separator();

        ImAdd::ToggleButtonClassic("Health Override", &globals::Ihooks::get_Health);
        ImGui::SetItemTooltip("Override health management. \nYou will always have god mode with this enabled. \nMaster Client is required to apply health for other players.");

        if (globals::Ihooks::get_Health) {
            ImGui::Indent(10);
            ImAdd::BeginHighlightGroup();

            ImAdd::ToggleButtonClassic("God Mode All", &globals::health::godmodeAll);
            ImGui::SetItemTooltip("Give everyone god mode.");

            if (!globals::health::godmodeAll) {
                const char* items[] = { "Static", "Instant Kill", "Normal" };
                int current_item = static_cast<int>(globals::health::healthMode);

                ImGui::PushItemWidth(150);
                if (ImGui::Combo("Health Mode", &current_item, items, IM_ARRAYSIZE(items))) {
                    globals::health::healthMode = static_cast<globals::health::HealthMode>(current_item);
                }
                ImGui::PopItemWidth();
                ImGui::SetItemTooltip("Health mode to apply for others. (requires Master Client) \nStatic: health is static value. \nInstant Kill: 1 health. \nNormal: health is not overridden.");


                if (globals::health::healthMode == globals::health::HealthMode::Static) {
                    ImGui::PushItemWidth(150);
                    ImGui::InputInt("Static Health Value", &globals::health::staticValue);
                    ImGui::PopItemWidth();
                }
            }

            ImAdd::EndHighlightGroup();
            ImGui::Indent(-10);
        }
        
        //if (pHookManager->hookPriority == HookManager::HookType::INLINE) {

            ImGui::Separator();
            ImAdd::ToggleButtonClassic("Rapid Fire", &globals::rapidFireToggle);

            if (globals::rapidFireToggle) {
                ImGui::Indent(10);
                ImAdd::BeginHighlightGroup();

                ImGui::PushItemWidth(150);
                ImGui::InputInt("Rapid Fire Count/Frame", &globals::rapidFireCount);
                ImGui::PopItemWidth();

                ImAdd::EndHighlightGroup();
                ImGui::Indent(-10);
            }

            if (globals::rapidFireToggle) {
                if (ImGui::Button("Select Weapon")) {

                    ThreadFix();

                    RecRoomPlayer* localRecRoomPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);
                    if (localRecRoomPlayer != nullptr) {
                        Il2CppArray* toolsArray = localRecRoomPlayer->get_AllToolsOnPlayer();
                        if (toolsArray != nullptr) {
                            for (int i = 0; i < toolsArray->max_length; i++)
                            {
                                Component* toolComponent = (Component*)il2cpp_array_get(toolsArray, Il2CppObject*, i);
                                GameObject* toolGameObject = toolComponent->get_gameObject();
                                if (toolGameObject != nullptr) {
                                    Component* rangedWeaponComponent = toolGameObject->GetComponent("RecRoom.Core.Combat.RangedWeapon");
                                    rapidFireWeaponComponent = (RangedWeapon*)rangedWeaponComponent;
                                }
                            }


                        }
                    }
                }
            }
            ImGui::SetItemTooltip("Hold weapon then press this to select it for rapid fire. \nYou will crash if the weapon is deleted.");

            if (ImGui::Button("Clear Rapid Fire Selection")) {
                rapidFireWeaponComponent = nullptr;
            }
            ImGui::SetItemTooltip("Clear the selected weapon data. \nPress this if your weapon has been deleted while Rapid Fire was toggled off.");
        //}

#ifdef CHEAP

        ImGui::SeparatorText("Misc");

        ImAdd::ToggleButtonClassic("FOV Slider", &globals::Ihooks::set_FieldOfView);

        if (globals::Ihooks::set_FieldOfView) {

            ImAdd::SliderInt("FOV", &globals::fov::fov, 1, 180); // setting fov beyond 180 bugs the camera out completely, default value is 68, sprint value is 88.4
            ImAdd::ToggleButtonClassic("Zoom Toggle", &globals::fov::zoomToggle);
            ImGui::SetItemTooltip("Optifine Zoom keybind is 'R'");

            if (globals::fov::zoomToggle)
                ImAdd::SliderInt("Zoom FOV", &globals::fov::zoomFov, 1, 180);
        }

        ImGui::Separator();

        ImAdd::ToggleButtonClassic("Watch Menu Prototype", &globals::watchMenuTest);
        ImGui::SetItemTooltip("Known incompatibility issue with Chams. \nContains bugs.");

        ImGui::SeparatorText("Exploits");

        if (ImGui::Button("Enable MakerPen"))
        {
            EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::UpdateRolesTarget, localPlayer.photonPlayer);
        }

        ImAdd::ToggleButtonClassic("Force MakerPen", &globals::roomRolePromotion);

        ImGui::SetItemTooltip("Whether to force MakerPen when enabling MakerPen. \nSide-Note: this is not stable, you will likely crash yourself.");

        if (!clothingEnabled || localPlayerExists)
            ImGui::BeginDisabled();

        ImGui::Separator();
        ImAdd::ToggleButtonClassic("Clothing", &globals::Ihooks::chai);
        ImGui::SetItemTooltip("Enable clothing if you own it.");

        if (!clothingEnabled || localPlayerExists)
            ImGui::EndDisabled();

#endif

    }
    ImGui::EndChild();

}