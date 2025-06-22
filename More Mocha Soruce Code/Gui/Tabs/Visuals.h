#pragma once

void CGui::VisualsTab(ImGuiStyle& style) {

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, style.ItemInnerSpacing);
    ImGui::PushFont(m_Fonts.BigFont);
    {
        ImGui::TextDisabled("Visuals");
    }
    ImGui::PopFont();
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4());
    ImGui::BeginChild("Visuals", ImVec2(0, (ImGui::GetFontSize() * 2 + style.WindowPadding.y * 4 + style.ItemInnerSpacing.y) + (style.WindowPadding.y * 2 + ImGui::GetFontSize() * 6 + style.ItemInnerSpacing.y * 3) + (ImGui::GetFontSize() + style.WindowPadding.y * 2) * 60), ImGuiChildFlags_Border);
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
    {

        ImGuiColorEditFlags misc_flags = ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_AlphaPreviewHalf | ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoOptions;

        ImAdd::ToggleButton("ESP##22", &globals::ESP::toggle);

        if (globals::ESP::toggle) {

            ImGui::Indent(10);
            ImAdd::BeginHighlightGroup();

            LineConfig skeletonConfig = globals::ESP::skeleton;
            LineConfig tracerConfig = globals::ESP::tracer;
            BoxConfig nametagOutlineConfig = globals::ESP::nametagOutline;
            BoxConfig boxOutlineConfig = globals::ESP::boxOutline;
            BoxConfig boxConfig = globals::ESP::box;
            LineConfig targetedConfig = globals::ESP::targeted;
            NametagConfig nametagConfig = globals::ESP::nametag;

            if (ImGui::CollapsingHeader("Skeleton")) {

                ImGui::Indent(5);
                ImAdd::BeginHighlightGroup();

                ImAdd::ToggleButton("Enabled##211", &skeletonConfig.state);
                ImAdd::ToggleButton("Render Self##211", &skeletonConfig.renderSelf);
                ImAdd::SliderFloat("Line Thickness##211", &skeletonConfig.lineThickness, 0.0f, 50.0f);

                if (ImAdd::ToggleButton("Gradient Color##211", &skeletonConfig.gradientColor))
                {
                    if (skeletonConfig.gradientColor) {
                        skeletonConfig.distanceColor = false;
                    }
                }

                if (skeletonConfig.gradientColor) {
                    ImGui::Indent(5);
                    ImAdd::BeginHighlightGroup();

                    ImAdd::ToggleButton("Rainbow Color##211", &skeletonConfig.rainbowColor);
                    if (!skeletonConfig.rainbowColor) {
                        ImGui::ColorEdit4("Gradient Start Color##211", (float*)&skeletonConfig.gradientStartColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                        ImGui::ColorEdit4("Gradient End Color##211", (float*)&skeletonConfig.gradientEndColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                    }
                    ImAdd::SliderFloat("Speed##211", &skeletonConfig.gradientSpeed, 0.00f, 10.00f);
                    ImAdd::EndHighlightGroup();
                    ImGui::Indent(-5);
                }

                if (ImAdd::ToggleButton("Distance Color##211", &skeletonConfig.distanceColor))
                {
                    if (skeletonConfig.distanceColor) {
                        skeletonConfig.gradientColor = false;
                    }
                }

                if (skeletonConfig.distanceColor) {
                    ImGui::Indent(5);
                    ImAdd::BeginHighlightGroup();
                    ImGui::ColorEdit4("Close Distance Color##211", (float*)&skeletonConfig.closeDistanceColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                    ImGui::ColorEdit4("Far Distance Color##211", (float*)&skeletonConfig.farDistanceColor, ImGuiColorEditFlags_NoInputs | misc_flags);

                    ImGui::InputFloat("Min Distance##211", &skeletonConfig.minDistance);
                    ImGui::InputFloat("Max Distance##211", &skeletonConfig.maxDistance);

                    ImAdd::EndHighlightGroup();
                    ImGui::Indent(-5);
                }

                ImAdd::ToggleButton("Fade##211", &skeletonConfig.fade);
                if (skeletonConfig.fade) {
                    ImGui::Indent(5);
                    ImAdd::BeginHighlightGroup();
                    ImGui::InputFloat("Fade Distance##211", &skeletonConfig.fadeDistance);
                    ImAdd::EndHighlightGroup();
                    ImGui::Indent(-5);
                }

                if (!skeletonConfig.distanceColor && !skeletonConfig.gradientColor && !skeletonConfig.rainbowColor) {
                    ImGui::ColorEdit4("Static Color##211", (float*)&skeletonConfig.staticColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                }

                globals::ESP::skeleton = skeletonConfig;
                ImAdd::EndHighlightGroup();
                ImGui::Indent(-5);
            }
            ImGui::Separator();
            if (ImGui::CollapsingHeader("Tracer")) {
                ImGui::Indent(5);
                ImAdd::BeginHighlightGroup();

                ImAdd::ToggleButton("Enabled##212", &tracerConfig.state);
                ImAdd::ToggleButton("Render Self##212", &tracerConfig.renderSelf);
                ImAdd::SliderFloat("Line Thickness##212", &tracerConfig.lineThickness, 0.0f, 50.0f);

                if (ImAdd::ToggleButton("Gradient Color##212", &tracerConfig.gradientColor))
                {
                    if (tracerConfig.gradientColor) {
                        tracerConfig.distanceColor = false;
                    }
                }

                if (tracerConfig.gradientColor) {
                    ImGui::Indent(5);
                    ImAdd::BeginHighlightGroup();

                    ImAdd::ToggleButton("Rainbow Color##212", &tracerConfig.rainbowColor);
                    if (!tracerConfig.rainbowColor) {
                        ImGui::ColorEdit4("Gradient Start Color##212", (float*)&tracerConfig.gradientStartColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                        ImGui::ColorEdit4("Gradient End Color##212", (float*)&tracerConfig.gradientEndColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                    }
                    ImAdd::SliderFloat("Speed##212", &tracerConfig.gradientSpeed, 0.00f, 10.00f);
                    ImAdd::EndHighlightGroup();
                    ImGui::Indent(-5);
                }

                if (ImAdd::ToggleButton("Distance Color##212", &tracerConfig.distanceColor))
                {
                    if (tracerConfig.distanceColor) {
                        tracerConfig.gradientColor = false;
                    }
                }

                if (tracerConfig.distanceColor) {
                    ImGui::Indent(5);
                    ImAdd::BeginHighlightGroup();
                    ImGui::ColorEdit4("Close Distance Color##212", (float*)&tracerConfig.closeDistanceColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                    ImGui::ColorEdit4("Far Distance Color##212", (float*)&tracerConfig.farDistanceColor, ImGuiColorEditFlags_NoInputs | misc_flags);

                    ImGui::InputFloat("Min Distance##212", &tracerConfig.minDistance);
                    ImGui::InputFloat("Max Distance##212", &tracerConfig.maxDistance);

                    ImAdd::EndHighlightGroup();
                    ImGui::Indent(-5);
                }

                ImAdd::ToggleButton("Fade##212", &tracerConfig.fade);
                if (tracerConfig.fade) {
                    ImGui::Indent(5);
                    ImAdd::BeginHighlightGroup();
                    ImGui::InputFloat("Fade Distance##212", &tracerConfig.fadeDistance);
                    ImAdd::EndHighlightGroup();
                    ImGui::Indent(-5);
                }

                if (!tracerConfig.distanceColor && !tracerConfig.gradientColor && !tracerConfig.rainbowColor) {
                    ImGui::ColorEdit4("Static Color##212", (float*)&tracerConfig.staticColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                }

                globals::ESP::tracer = tracerConfig;
                ImAdd::EndHighlightGroup();
                ImGui::Indent(-5);
            }
            ImGui::Separator();

            if (ImGui::CollapsingHeader("Box")) {

                ImGui::Indent(5);
                ImAdd::BeginHighlightGroup();

                ImAdd::ToggleButton("Enabled##213", &boxConfig.state);
                ImAdd::ToggleButton("Render Self##213", &boxConfig.renderSelf);
                ImAdd::ToggleButton("Dynamic##213", &boxConfig.dynamic);

                ImAdd::SliderFloat("Line Thickness##213", &boxConfig.lineThickness, 0.0f, 50.0f);
                ImAdd::SliderFloat("Rounding##213", &boxConfig.rounding, 0.0f, 100.0f);

                ImAdd::SliderFloat("Padding X##213", &boxConfig.padding.x, 0.0f, 250.0f);
                ImAdd::SliderFloat("Padding Y##213", &boxConfig.padding.y, 0.0f, 250.0f);

                if (ImAdd::ToggleButton("Gradient Color##213", &boxConfig.gradientColor))
                {
                    if (boxConfig.gradientColor) {
                        boxConfig.distanceColor = false;
                    }
                }

                if (boxConfig.gradientColor) {
                    ImGui::Indent(5);
                    ImAdd::BeginHighlightGroup();

                    ImAdd::ToggleButton("Rainbow Color##213", &boxConfig.rainbowColor);

                    ImAdd::ToggleButton("Simple Gradient##213", &boxConfig.simpleGradient);
                    if (!boxConfig.rainbowColor) {
                        ImGui::ColorEdit4("Gradient Start Color##213", (float*)&boxConfig.gradientStartColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                        ImGui::ColorEdit4("Gradient End Color##213", (float*)&boxConfig.gradientEndColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                    }

                    ImAdd::SliderFloat("Speed##213", &boxConfig.gradientSpeed, 0.00f, 10.00f);
                    ImAdd::EndHighlightGroup();
                    ImGui::Indent(-5);
                }


                if (ImAdd::ToggleButton("Distance Color##213", &boxConfig.distanceColor))
                {
                    if (boxConfig.distanceColor) {
                        boxConfig.gradientColor = false;
                    }
                }

                if (boxConfig.distanceColor) {
                    ImGui::Indent(5);
                    ImAdd::BeginHighlightGroup();
                    ImGui::ColorEdit4("Close Distance Color##213", (float*)&boxConfig.closeDistanceColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                    ImGui::ColorEdit4("Far Distance Color##213", (float*)&boxConfig.farDistanceColor, ImGuiColorEditFlags_NoInputs | misc_flags);

                    ImGui::InputFloat("Min Distance##213", &boxConfig.minDistance);
                    ImGui::InputFloat("Max Distance##213", &boxConfig.maxDistance);

                    ImAdd::EndHighlightGroup();
                    ImGui::Indent(-5);
                }

                ImAdd::ToggleButton("Fade##213", &boxConfig.fade);
                if (boxConfig.fade) {

                    ImGui::Indent(5);
                    ImAdd::BeginHighlightGroup();
                    ImGui::InputFloat("Fade Distance##213", &boxConfig.fadeDistance);
                    ImAdd::EndHighlightGroup();
                    ImGui::Indent(-5);
                }

                if (!boxConfig.distanceColor && !boxConfig.gradientColor && !boxConfig.rainbowColor) {
                    ImGui::ColorEdit4("Static Color##213", (float*)&boxConfig.staticColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                }

                ImAdd::ToggleButton("Box Outline##213", &boxOutlineConfig.state);

                if (ImGui::CollapsingHeader("Box Outline")) {

                    ImGui::Indent(5);
                    ImAdd::BeginHighlightGroup();

                    ImAdd::SliderFloat("Line Thickness##214", &boxOutlineConfig.lineThickness, 0.0f, 50.0f);


                    if (ImAdd::ToggleButton("Distance Color##214", &boxOutlineConfig.distanceColor))
                    {
                        if (boxOutlineConfig.distanceColor) {
                            boxOutlineConfig.gradientColor = false;
                        }
                    }

                    if (boxOutlineConfig.distanceColor) {
                        ImGui::Indent(5);
                        ImAdd::BeginHighlightGroup();
                        ImGui::ColorEdit4("Close Distance Color##214", (float*)&boxOutlineConfig.closeDistanceColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                        ImGui::ColorEdit4("Far Distance Color##214", (float*)&boxOutlineConfig.farDistanceColor, ImGuiColorEditFlags_NoInputs | misc_flags);

                        ImGui::InputFloat("Min Distance##214", &boxOutlineConfig.minDistance);
                        ImGui::InputFloat("Max Distance##214", &boxOutlineConfig.maxDistance);

                        ImAdd::EndHighlightGroup();
                        ImGui::Indent(-5);
                    }

                    if (ImAdd::ToggleButton("Gradient Color##214", &boxOutlineConfig.gradientColor))
                    {
                        if (boxOutlineConfig.gradientColor) {
                            boxOutlineConfig.distanceColor = false;
                        }
                    }

                    if (boxOutlineConfig.gradientColor) {
                        ImGui::Indent(5);
                        ImAdd::BeginHighlightGroup();

                        ImAdd::ToggleButton("Rainbow Color##214", &boxOutlineConfig.rainbowColor);

                        if (!boxOutlineConfig.rainbowColor) {
                            ImGui::ColorEdit4("Gradient Start Color##214", (float*)&boxOutlineConfig.gradientStartColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                            ImGui::ColorEdit4("Gradient End Color##214", (float*)&boxOutlineConfig.gradientEndColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                        }

                        ImAdd::EndHighlightGroup();
                        ImGui::Indent(-5);
                    }
                    else if (!boxOutlineConfig.distanceColor) {
                        ImGui::ColorEdit4("Static Color##214", (float*)&boxOutlineConfig.staticColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                    }

                    ImAdd::ToggleButton("Fade##214", &boxOutlineConfig.fade);
                    if (boxOutlineConfig.fade) {

                        ImGui::Indent(5);
                        ImAdd::BeginHighlightGroup();
                        ImGui::InputFloat("Fade Distance##214", &boxOutlineConfig.fadeDistance);
                        ImAdd::EndHighlightGroup();
                        ImGui::Indent(-5);
                    }

                    ImAdd::EndHighlightGroup();
                    ImGui::Indent(-5);
                }

                globals::ESP::box = boxConfig;
                globals::ESP::boxOutline = boxOutlineConfig;

                ImAdd::EndHighlightGroup();
                ImGui::Indent(-5);
            }

            /// end of box
            ImGui::Separator();

            ImGui::BeginDisabled();
            if (ImGui::CollapsingHeader("Targeted")) {
                ImGui::Indent(5);
                ImAdd::BeginHighlightGroup();
                globals::ESP::targeted = targetedConfig;
                ImAdd::EndHighlightGroup();
                ImGui::Indent(-5);
            }
            ImGui::Separator();
            ImGui::EndDisabled();

            if (ImGui::CollapsingHeader("Nametag")) {
                ImGui::Indent(5);
                ImAdd::BeginHighlightGroup();


                ImAdd::ToggleButton("Enabled##216", &nametagConfig.state);
                ImAdd::ToggleButton("Render Self##216", &nametagConfig.renderSelf);

                ImAdd::ToggleButton("Show Ping##216", &nametagConfig.showPing);
                ImAdd::ToggleButton("Show Distance##216", &nametagConfig.showDistance);
                ImAdd::ToggleButton("Show Master Client##216", &nametagConfig.showMasterClient);
                ImAdd::ToggleButton("Show VMOD##216", &nametagConfig.showVMOD);

                if (ImAdd::ToggleButton("Gradient Color##216", &nametagConfig.gradientColor))
                {
                    if (nametagConfig.gradientColor) {
                        nametagConfig.distanceColor = false;
                    }
                }

                if (nametagConfig.gradientColor) {
                    ImGui::Indent(5);
                    ImAdd::BeginHighlightGroup();

                    ImAdd::ToggleButton("Rainbow Color##216", &nametagConfig.rainbowColor);
                    if (!nametagConfig.rainbowColor) {
                        ImGui::ColorEdit4("Gradient Start Color##216", (float*)&nametagConfig.gradientStartColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                        ImGui::ColorEdit4("Gradient End Color##216", (float*)&nametagConfig.gradientEndColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                    }
                    ImAdd::SliderFloat("Speed##216", &nametagConfig.gradientSpeed, 0.00f, 10.00f);
                    ImAdd::EndHighlightGroup();
                    ImGui::Indent(-5);
                }

                if (ImAdd::ToggleButton("Distance Color##216", &nametagConfig.distanceColor))
                {
                    if (nametagConfig.distanceColor) {
                        nametagConfig.gradientColor = false;
                    }
                }

                if (nametagConfig.distanceColor) {
                    ImGui::Indent(5);
                    ImAdd::BeginHighlightGroup();
                    ImGui::ColorEdit4("Close Distance Color##216", (float*)&nametagConfig.closeDistanceColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                    ImGui::ColorEdit4("Far Distance Color##216", (float*)&nametagConfig.farDistanceColor, ImGuiColorEditFlags_NoInputs | misc_flags);

                    ImGui::InputFloat("Min Distance##216", &nametagConfig.minDistance);
                    ImGui::InputFloat("Max Distance##216", &nametagConfig.maxDistance);

                    ImAdd::EndHighlightGroup();
                    ImGui::Indent(-5);
                }

                ImAdd::ToggleButton("Fade##216", &nametagConfig.fade);
                if (nametagConfig.fade) {
                    ImGui::Indent(5);
                    ImAdd::BeginHighlightGroup();
                    ImGui::InputFloat("Fade Distance##216", &nametagConfig.fadeDistance);
                    ImAdd::EndHighlightGroup();
                    ImGui::Indent(-5);
                }

                if (!nametagConfig.distanceColor && !nametagConfig.gradientColor && !nametagConfig.rainbowColor) {
                    ImGui::ColorEdit4("Static Color##216", (float*)&nametagConfig.staticColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                }

                if (ImGui::CollapsingHeader("Background")) {

                    ImGui::Indent(5);
                    ImAdd::BeginHighlightGroup();

                    ImAdd::ToggleButton("Background##216", &nametagConfig.background);

                    if (nametagConfig.background) {

                        ImGui::ColorEdit4("Background Color##217", (float*)&nametagConfig.backgroundColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                        ImAdd::SliderFloat("Outline Thickness##217", &nametagOutlineConfig.lineThickness, 0.0f, 50.0f);
                        ImAdd::SliderFloat("Rounding##217", &nametagOutlineConfig.rounding, 0.0f, 100.0f);

                        if (ImAdd::ToggleButton("Outline Distance Color##217", &nametagOutlineConfig.distanceColor))
                        {
                            if (nametagOutlineConfig.distanceColor) {
                                nametagOutlineConfig.gradientColor = false;
                            }
                        }

                        if (nametagOutlineConfig.distanceColor) {
                            ImGui::Indent(5);
                            ImAdd::BeginHighlightGroup();
                            ImGui::ColorEdit4("Close Distance Color##217", (float*)&nametagOutlineConfig.closeDistanceColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                            ImGui::ColorEdit4("Far Distance Color##217", (float*)&nametagOutlineConfig.farDistanceColor, ImGuiColorEditFlags_NoInputs | misc_flags);

                            ImGui::InputFloat("Min Distance##217", &nametagOutlineConfig.minDistance);
                            ImGui::InputFloat("Max Distance##217", &nametagOutlineConfig.maxDistance);

                            ImAdd::EndHighlightGroup();
                            ImGui::Indent(-5);
                        }

                        if (ImAdd::ToggleButton("Gradient Color##217", &nametagOutlineConfig.gradientColor))
                        {
                            if (nametagOutlineConfig.gradientColor) {
                                nametagOutlineConfig.distanceColor = false;
                            }
                        }

                        if (nametagOutlineConfig.gradientColor) {
                            ImGui::Indent(5);
                            ImAdd::BeginHighlightGroup();

                            ImAdd::ToggleButton("Rainbow Color##217", &nametagOutlineConfig.rainbowColor);

                            if (!nametagOutlineConfig.rainbowColor) {
                                ImGui::ColorEdit4("Gradient Start Color##217", (float*)&nametagOutlineConfig.gradientStartColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                                ImGui::ColorEdit4("Gradient End Color##217", (float*)&nametagOutlineConfig.gradientEndColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                            }

                            ImAdd::EndHighlightGroup();
                            ImGui::Indent(-5);
                        }
                        else if (!nametagOutlineConfig.distanceColor) {
                            ImGui::ColorEdit4("Static Color##217", (float*)&nametagOutlineConfig.staticColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                        }

                        ImAdd::EndHighlightGroup();
                        ImGui::Indent(-5);
                    }
                }

                globals::ESP::nametag = nametagConfig;
                globals::ESP::nametagOutline = nametagOutlineConfig;
                ImAdd::EndHighlightGroup();
                ImGui::Indent(-5);
            }

            ImAdd::EndHighlightGroup();
            ImGui::Indent(-5);
        }


        ImGui::Separator();

        ImAdd::ToggleButtonClassic("Chams", &globals::chams::toggle); // there is a crash bug here related to nullptrs, i cba fixing rn
        ImGui::SetItemTooltip("Q: Why shapes and not player mesh? \nA: Because clothing is obfuscated and it's not worth the time investment.");

        if (globals::chams::toggle) {
            ImGui::Indent(10);
            ImAdd::BeginHighlightGroup();

            ImGuiColorEditFlags misc_flags = ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_AlphaPreviewHalf | ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoOptions;

            float internalScale[3] = { 1.0, 1.0, 1.0 };

            internalScale[0] = globals::chams::settings.scale.x;
            internalScale[1] = globals::chams::settings.scale.y;
            internalScale[2] = globals::chams::settings.scale.z;

            ImGui::InputFloat3("Scale##333", internalScale);
            ImGui::PushItemWidth(50);
            ImGui::InputFloat("Glow##333", &globals::chams::settings.glow);
            ImGui::PopItemWidth();
            ImGui::ColorEdit4("Color##333", (float*)&globals::chams::settings.color, ImGuiColorEditFlags_NoInputs | misc_flags);

            const char* items[] = { "Sphere", "Capsule", "Cylinder", "Cube", "Plane", "Quad" };
            int current_item = static_cast<int>(globals::chams::settings.shape);

            ImGui::PushItemWidth(50);
            if (ImGui::Combo("Shape", &current_item, items, IM_ARRAYSIZE(items))) {
                globals::chams::settings.shape = static_cast<PrimitiveType>(current_item);
            }

            ImGui::PopItemWidth();

            globals::chams::settings.scale.x = internalScale[0];
            globals::chams::settings.scale.y = internalScale[1];
            globals::chams::settings.scale.z = internalScale[2];

            ImAdd::EndHighlightGroup();
            ImGui::Indent(-10);
        }

        #ifndef PROD
        ImGui::Separator();

        {

            ImAdd::ToggleButtonClassic("Shader Chams ##34344", &globals::shaderChams::toggle);
            ImAdd::ToggleButtonClassic("Self Toggle ##34344", &globals::shaderChams::self);

            ImGui::Indent(10);
            ImAdd::BeginHighlightGroup();

            ImGuiColorEditFlags misc_flags = ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_AlphaPreviewHalf | ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoOptions;

            {
                const char* items[] = { "Chams", "ColorChams", "Pulsing", "Wireframe", "Rainbow" };
                int current_item = static_cast<int>(globals::shaderChams::chamsMode);

                ImGui::PushItemWidth(150);
                if (ImGui::Combo("Chams Mode", &current_item, items, IM_ARRAYSIZE(items))) {
                    globals::shaderChams::chamsMode = static_cast<globals::shaderChams::Mode>(current_item);
                }

                ImGui::PopItemWidth();
            }

            switch (globals::shaderChams::chamsMode) {
            case (globals::shaderChams::Mode::Chams): {
                ImGui::ColorEdit4("Color1 ##444", (float*)&globals::shaderChams::_Color1, ImGuiColorEditFlags_NoInputs | misc_flags);
                ImGui::ColorEdit4("Color2 ##444", (float*)&globals::shaderChams::_Color2, ImGuiColorEditFlags_NoInputs | misc_flags);

                ImGui::SliderFloat("Rainbow1 ##444", &globals::shaderChams::_Rainbow1, 0.0f, 1.0f);
                ImGui::SliderFloat("Rainbow2 ##444", &globals::shaderChams::_Rainbow2, 0.0f, 1.0f);
                ImGui::SliderFloat("Wire Frame ##444", &globals::shaderChams::_Wireframe, 0.0f, 1.0f);
                ImGui::SliderFloat("Line Width ##444", &globals::shaderChams::_LineWidth, 0.001f, 0.05f);
                ImGui::SliderFloat("Glow ##444", &globals::shaderChams::_GlowIntensity, 1.0f, 10.0f);
                ImGui::SliderFloat("Speed ##444", &globals::shaderChams::_Speed, 0.0f, 5.0f);
                break;
            }
            case (globals::shaderChams::Mode::ColorChams): {
                ImGui::ColorEdit4("Visible Color ##444", (float*)&globals::shaderChams::_Color1, ImGuiColorEditFlags_NoInputs | misc_flags);
                ImGui::ColorEdit4("Behind Color ##444", (float*)&globals::shaderChams::_Color2, ImGuiColorEditFlags_NoInputs | misc_flags);
                break;
            }
            case (globals::shaderChams::Mode::Pulsing): {
                ImGui::ColorEdit4("Emission Color ##444", (float*)&globals::shaderChams::_Emissioncolour, ImGuiColorEditFlags_NoInputs | misc_flags);
                break;
            }
            case (globals::shaderChams::Mode::Wireframe): {
                ImGui::ColorEdit4("Wire Color ##444", (float*)&globals::shaderChams::_WireColor, ImGuiColorEditFlags_NoInputs | misc_flags);
                break;
            }
            }

            ImAdd::EndHighlightGroup();
            ImGui::Indent(-10);
        }

        #endif
        ImGui::Separator();

#ifndef CHEAP
        ImAdd::ToggleButton("Skin Color Override##33", &globals::colorSkin::toggle);
        ImGui::SetItemTooltip("Changes skin colors locally.");
        if (globals::colorSkin::toggle) {
            ImGui::Indent(10);
            ImAdd::BeginHighlightGroup();

            ImAdd::ToggleButtonClassic("Self##33", &globals::colorSkin::self);
            ImAdd::ToggleButtonClassic("Others##33", &globals::colorSkin::others);
            ImAdd::ToggleButtonClassic("Rainbow##33", &globals::colorSkin::rainbow);

            if (!globals::colorSkin::rainbow) {
                ImAdd::ToggleButtonClassic("Black##33", &globals::colorSkin::black);
                if (!globals::colorSkin::black)
                    ImGui::ColorEdit4("Skin Color##331", (float*)&globals::colorSkin::color, ImGuiColorEditFlags_NoInputs | misc_flags);
            }
            else {
                ImGui::PushItemWidth(50);
                ImGui::InputFloat("Speed##33", &globals::colorSkin::rainbowSpeed);
                ImGui::PopItemWidth();
            }

            ImGui::PushItemWidth(50);
            ImGui::InputFloat("Glow##33", &globals::colorSkin::glow);
            ImGui::PopItemWidth();

            ImAdd::EndHighlightGroup();
            ImGui::Indent(-10);
        }
#endif

    }
    ImGui::EndChild();

}