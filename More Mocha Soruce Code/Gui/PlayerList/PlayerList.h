#pragma once
#include "Sections/PlayerInfo.h"

namespace PL
{

    std::string PlatformToString(HardwareType type)
    {
        switch (type)
        {
        case Desktop_Valve:
            return "Valve";
        case Desktop_Oculus:
            return "Oculus";
        case PS4:
            return "PS4";
        case Desktop_MicrosoftVR:
            return "MSVR";
        case Desktop_VRMissing:
            return "Screen";
        case OculusQuest:
            return "Quest";
        case iOS:
            return "iOS";
        case XboxOne:
            return "XboxOne";
        case AndroidMobile:
            return "Android";
        case PS5:
            return "PS5";
        case XboxSeries:
            return "XboxS";
        case PicoNeo3:
            return "PicoN3";
        case PicoPhoenix:
            return "PicoN4";
        case NintendoSwitch:
            return "Switch";
        }
        return "???";
    }
    
    struct suffix
    {
        std::string name;
        std::string descriptor;
        ImVec4 color;
    };

    bool Player(PlayerInfo& player, ImVec4 nameColor, int32_t& ping, std::string& platformString, const std::vector<suffix>& suffixes, const std::vector<std::reference_wrapper<PlayerInfo>>& playerVec)
    {
        using namespace ImGui;

        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_CollapsingHeader;
            
        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const bool display_frame = (flags & ImGuiTreeNodeFlags_Framed) != 0;
        const ImVec2 padding = (display_frame || (flags & ImGuiTreeNodeFlags_FramePadding)) ? 
                               style.FramePadding : ImVec2(style.FramePadding.x, ImMin(window->DC.CurrLineTextBaseOffset, style.FramePadding.y));

        // Compute min and max actorId for gradient
        int minActorId = INT_MAX;
        int maxActorId = INT_MIN;
        for (const auto& p : playerVec)
        {
    #undef max
    #undef min
            int aid = p.get().photonActorID;
            minActorId = std::min(minActorId, aid);
            maxActorId = std::max(maxActorId, aid);
        }

        // Compute actorId color (gradient from #e9977b to #977be9)
        ImVec4 actorIdColor(0.914f, 0.592f, 0.482f, 1.0f); // Default to #e9977b
        if (maxActorId > minActorId)
        {
            float factor = (player.photonActorID - minActorId) / static_cast<float>(maxActorId - minActorId);
            // Interpolate from #e9977b (0.914, 0.592, 0.482) to #977be9 (0.592, 0.482, 0.914)
            float r = 0.914f + (0.592f - 0.914f) * factor; // R: 0.914 -> 0.592
            float g = 0.592f + (0.482f - 0.592f) * factor; // G: 0.592 -> 0.482
            float b = 0.482f + (0.914f - 0.482f) * factor; // B: 0.482 -> 0.914
            actorIdColor = ImVec4(r, g, b, 1.0f);
        }

        // Compute ping color (green -> yellow -> red)
        ImVec4 pingColor;
        if (ping < 0)
            pingColor = ImVec4(0.5f, 0.5f, 0.5f, 1.0f); // Grey
        else if (ping == 0)
            pingColor = ImVec4(0.0f, 1.0f, 0.0f, 1.0f); // Green
        else if (ping >= 500)
            pingColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Red
        else if (ping <= 200)
        {
            float t = ping / 200.0f;
            pingColor = ImVec4(t, 1.0f, 0.0f, 1.0f); // Green to yellow
        }
        else
        {
            float t = (ping - 200.0f) / 300.0f;
            pingColor = ImVec4(1.0f, 1.0f - t, 0.0f, 1.0f); // Yellow to red
        }

        // Define static colors
        constexpr ImVec4 grey(0.5f, 0.5f, 0.5f, 1.0f);
        constexpr ImVec4 darkGrey(0.3f, 0.3f, 0.3f, 1.0f);
        constexpr ImVec4 pink(0.898f, 0.604f, 0.769f, 1.0f);

        // Prepare label parts
        std::string actorIdStr = std::to_string(player.photonActorID);
        const char* displayNameStr = player.DisplayName;
        const char* platformStr = platformString.c_str();
        std::string pingStr = std::to_string(ping) + "ms";

        // Compute total label width
        float total_label_width = 0.0f;
        total_label_width += CalcTextSize("[").x;              // [actorId]
        total_label_width += CalcTextSize(actorIdStr.c_str()).x;
        total_label_width += CalcTextSize("]").x;
        total_label_width += CalcTextSize(" | ").x;            // Separator
        total_label_width += CalcTextSize(displayNameStr).x; // displayName
        total_label_width += CalcTextSize(" (").x;             // [ping]
        total_label_width += CalcTextSize(pingStr.c_str()).x;
        total_label_width += CalcTextSize(") | ").x;           // Separator
        total_label_width += CalcTextSize("[").x;              // [platformStr]
        total_label_width += CalcTextSize(platformStr).x;
        total_label_width += CalcTextSize("]").x;
        total_label_width += CalcTextSize(" | ").x;            // Separator
        for (const auto& suffix : suffixes)                    // [suffix] [suffix] ...
        {
            total_label_width += CalcTextSize(" [").x;
            total_label_width += CalcTextSize(suffix.name.c_str()).x;
            total_label_width += CalcTextSize("]").x;
        }

        const float label_height = g.FontSize;
            
        // Set up frame and sizes
        const float frame_height = ImMax(ImMin(window->DC.CurrLineSize.y, g.FontSize + style.FramePadding.y * 2), 
                                         label_height + padding.y * 2);
        const bool span_all_columns = (flags & ImGuiTreeNodeFlags_SpanAllColumns) != 0 && (g.CurrentTable != NULL);
        ImRect frame_bb;
        frame_bb.Min.x = span_all_columns ? window->ParentWorkRect.Min.x : 
                         (flags & ImGuiTreeNodeFlags_SpanFullWidth) ? window->WorkRect.Min.x : window->DC.CursorPos.x;
        frame_bb.Min.y = window->DC.CursorPos.y;
        frame_bb.Max.x = span_all_columns ? window->ParentWorkRect.Max.x : window->WorkRect.Max.x;
        frame_bb.Max.y = window->DC.CursorPos.y + frame_height;
        if (display_frame)
        {
            frame_bb.Min.x -= IM_TRUNC(window->WindowPadding.x * 0.5f - 1.0f);
            frame_bb.Max.x += IM_TRUNC(window->WindowPadding.x * 0.5f);
        }

        const float text_offset_x = g.FontSize + (display_frame ? padding.x * 3 : padding.x * 2);
        const float text_offset_y = ImMax(padding.y, window->DC.CurrLineTextBaseOffset);
        const float text_width = g.FontSize + total_label_width + padding.x * 2;
        ImVec2 text_pos(window->DC.CursorPos.x + text_offset_x, window->DC.CursorPos.y + text_offset_y);
        ItemSize(ImVec2(text_width, frame_height), padding.y);

        // Interaction setup (unchanged)
        ImRect interact_bb = frame_bb;
        if (!display_frame && (flags & (ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_SpanAllColumns)) == 0)
            interact_bb.Max.x = frame_bb.Min.x + text_width + style.ItemSpacing.x * 2.0f;

        const float backup_clip_rect_min_x = window->ClipRect.Min.x;
        const float backup_clip_rect_max_x = window->ClipRect.Max.x;
        if (span_all_columns)
        {
            window->ClipRect.Min.x = window->ParentWorkRect.Min.x;
            window->ClipRect.Max.x = window->ParentWorkRect.Max.x;
        }

        ImGuiID id = window->GetID(&player); // Unique ID based on player reference
        bool is_open = TreeNodeUpdateNextOpen(id, flags);
        bool item_add = ItemAdd(interact_bb, id);
        g.LastItemData.StatusFlags |= ImGuiItemStatusFlags_HasDisplayRect;
        g.LastItemData.DisplayRect = frame_bb;

        if (span_all_columns)
        {
            window->ClipRect.Min.x = backup_clip_rect_min_x;
            window->ClipRect.Max.x = backup_clip_rect_max_x;
        }

        if (is_open && !g.NavIdIsAlive && (flags & ImGuiTreeNodeFlags_NavLeftJumpsBackHere) && !(flags & ImGuiTreeNodeFlags_NoTreePushOnOpen))
            if (g.NavMoveDir == ImGuiDir_Left && g.NavWindow == window && NavMoveRequestButNoResultYet())
            {
                g.NavTreeNodeStack.resize(g.NavTreeNodeStack.Size + 1);
                ImGuiNavTreeNodeData* nav_tree_node_data = &g.NavTreeNodeStack.back();
                nav_tree_node_data->ID = id;
                nav_tree_node_data->InFlags = g.LastItemData.InFlags;
                nav_tree_node_data->NavRect = g.LastItemData.NavRect;
                window->DC.TreeJumpToParentOnPopMask |= (1 << window->DC.TreeDepth);
            }

        const bool is_leaf = (flags & ImGuiTreeNodeFlags_Leaf) != 0;
        if (!item_add)
        {
            if (is_open && !(flags & ImGuiTreeNodeFlags_NoTreePushOnOpen))
                TreePushOverrideID(id);
            IMGUI_TEST_ENGINE_ITEM_INFO(g.LastItemData.ID, "player", 
                                        g.LastItemData.StatusFlags | (is_leaf ? 0 : ImGuiItemStatusFlags_Openable) | 
                                        (is_open ? ImGuiItemStatusFlags_Opened : 0));
            return is_open;
        }

        if (span_all_columns)
        {
            TablePushBackgroundChannel();
            g.LastItemData.StatusFlags |= ImGuiItemStatusFlags_HasClipRect;
            g.LastItemData.ClipRect = window->ClipRect;
        }

        ImGuiButtonFlags button_flags = ImGuiTreeNodeFlags_None;
        if ((flags & ImGuiTreeNodeFlags_AllowOverlap) || (g.LastItemData.InFlags & ImGuiItemFlags_AllowOverlap))
            button_flags |= ImGuiButtonFlags_AllowOverlap;
        if (!is_leaf)
            button_flags |= ImGuiButtonFlags_PressedOnDragDropHold;

        const float arrow_hit_x1 = (text_pos.x - text_offset_x) - style.TouchExtraPadding.x;
        const float arrow_hit_x2 = (text_pos.x - text_offset_x) + (g.FontSize + padding.x * 2.0f) + style.TouchExtraPadding.x;
        const bool is_mouse_x_over_arrow = (g.IO.MousePos.x >= arrow_hit_x1 && g.IO.MousePos.x < arrow_hit_x2);
        if (window != g.HoveredWindow || !is_mouse_x_over_arrow)
            button_flags |= ImGuiButtonFlags_NoKeyModifiers;

        if (is_mouse_x_over_arrow)
            button_flags |= ImGuiButtonFlags_PressedOnClick;
        else if (flags & ImGuiTreeNodeFlags_OpenOnDoubleClick)
            button_flags |= ImGuiButtonFlags_PressedOnClickRelease | ImGuiButtonFlags_PressedOnDoubleClick;
        else
            button_flags |= ImGuiButtonFlags_PressedOnClickRelease;

        bool selected = (flags & ImGuiTreeNodeFlags_Selected) != 0;
        const bool was_selected = selected;

        bool hovered, held;
        bool pressed = ButtonBehavior(interact_bb, id, &hovered, &held, button_flags);
        bool toggled = false;
        if (!is_leaf)
        {
            if (pressed && g.DragDropHoldJustPressedId != id)
            {
                if ((flags & (ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick)) == 0 || (g.NavActivateId == id))
                    toggled = true;
                if (flags & ImGuiTreeNodeFlags_OpenOnArrow)
                    toggled |= is_mouse_x_over_arrow && !g.NavDisableMouseHover;
                if ((flags & ImGuiTreeNodeFlags_OpenOnDoubleClick) && g.IO.MouseClickedCount[0] == 2)
                    toggled = true;
            }
            else if (pressed && g.DragDropHoldJustPressedId == id)
            {
                IM_ASSERT(button_flags & ImGuiButtonFlags_PressedOnDragDropHold);
                if (!is_open)
                    toggled = true;
            }

            if (g.NavId == id && g.NavMoveDir == ImGuiDir_Left && is_open)
            {
                toggled = true;
                NavClearPreferredPosForAxis(ImGuiAxis_X);
                NavMoveRequestCancel();
            }
            if (g.NavId == id && g.NavMoveDir == ImGuiDir_Right && !is_open)
            {
                toggled = true;
                NavClearPreferredPosForAxis(ImGuiAxis_X);
                NavMoveRequestCancel();
            }

            if (toggled)
            {
                is_open = !is_open;
                window->DC.StateStorage->SetInt(id, is_open);
                g.LastItemData.StatusFlags |= ImGuiItemStatusFlags_ToggledOpen;
            }
        }

        if (selected != was_selected)
            g.LastItemData.StatusFlags |= ImGuiItemStatusFlags_ToggledSelection;

        // Render frame and decorations (unchanged)
        const ImU32 text_col = GetColorU32(ImGuiCol_Text);
        ImGuiNavHighlightFlags nav_highlight_flags = ImGuiNavHighlightFlags_Compact;
        if (display_frame)
        {
            const ImU32 bg_col = GetColorU32((held && hovered) ? ImGuiCol_HeaderActive : hovered ? ImGuiCol_HeaderHovered : ImGuiCol_Header);
            RenderFrame(frame_bb.Min, frame_bb.Max, bg_col, true, style.FrameRounding);
            RenderNavHighlight(frame_bb, id, nav_highlight_flags);
            if (flags & ImGuiTreeNodeFlags_Bullet)
                RenderBullet(window->DrawList, ImVec2(text_pos.x - text_offset_x * 0.60f, text_pos.y + g.FontSize * 0.5f), text_col);
            else if (!is_leaf)
                RenderArrow(window->DrawList, ImVec2(text_pos.x - text_offset_x + padding.x, text_pos.y), text_col, 
                            is_open ? ((flags & ImGuiTreeNodeFlags_UpsideDownArrow) ? ImGuiDir_Up : ImGuiDir_Down) : ImGuiDir_Right, 1.0f);
            else
                text_pos.x -= text_offset_x - padding.x;
            if (flags & ImGuiTreeNodeFlags_ClipLabelForTrailingButton)
                frame_bb.Max.x -= g.FontSize + style.FramePadding.x;
            if (g.LogEnabled)
                LogSetNextTextDecoration("###", "###");
        }
        else
        {
            if (hovered || selected)
            {
                const ImU32 bg_col = GetColorU32((held && hovered) ? ImGuiCol_HeaderActive : hovered ? ImGuiCol_HeaderHovered : ImGuiCol_Header);
                RenderFrame(frame_bb.Min, frame_bb.Max, bg_col, false);
            }
            RenderNavHighlight(frame_bb, id, nav_highlight_flags);
            if (flags & ImGuiTreeNodeFlags_Bullet)
                RenderBullet(window->DrawList, ImVec2(text_pos.x - text_offset_x * 0.5f, text_pos.y + g.FontSize * 0.5f), text_col);
            else if (!is_leaf)
                RenderArrow(window->DrawList, ImVec2(text_pos.x - text_offset_x + padding.x, text_pos.y + g.FontSize * 0.15f), text_col, 
                            is_open ? ((flags & ImGuiTreeNodeFlags_UpsideDownArrow) ? ImGuiDir_Up : ImGuiDir_Down) : ImGuiDir_Right, 0.70f);
            if (g.LogEnabled)
                LogSetNextTextDecoration(">", NULL);
        }

        if (span_all_columns)
            TablePopBackgroundChannel();

        // Custom label rendering
        if (display_frame)
            window->DrawList->PushClipRect(frame_bb.Min, frame_bb.Max, true);

        ImVec2 pos = text_pos;

        // [actorId]
        window->DrawList->AddText(pos, GetColorU32(grey), "[");
        pos.x += CalcTextSize("[").x;
        window->DrawList->AddText(pos, GetColorU32(actorIdColor), actorIdStr.c_str());
        pos.x += CalcTextSize(actorIdStr.c_str()).x;
        window->DrawList->AddText(pos, GetColorU32(grey), "]");
        pos.x += CalcTextSize("]").x;

        // " | "
        window->DrawList->AddText(pos, GetColorU32(darkGrey), " | ");
        pos.x += CalcTextSize(" | ").x;

        // displayName
        window->DrawList->AddText(pos, GetColorU32(nameColor), displayNameStr);
        pos.x += CalcTextSize(displayNameStr).x;

        // " [ping]
        window->DrawList->AddText(pos, GetColorU32(grey), " (");
        pos.x += CalcTextSize(" (").x;
        window->DrawList->AddText(pos, GetColorU32(pingColor), pingStr.c_str());
        pos.x += CalcTextSize(pingStr.c_str()).x;
        window->DrawList->AddText(pos, GetColorU32(grey), ")");
        pos.x += CalcTextSize(")").x;

        // " | "
        window->DrawList->AddText(pos, GetColorU32(darkGrey), " | ");
        pos.x += CalcTextSize(" | ").x;
        
        // [platform]
        window->DrawList->AddText(pos, GetColorU32(grey), "[");
        pos.x += CalcTextSize("[").x;
        window->DrawList->AddText(pos, GetColorU32(pink), platformStr);
        pos.x += CalcTextSize(platformStr).x;
        window->DrawList->AddText(pos, GetColorU32(grey), "]");
        pos.x += CalcTextSize("]").x;
        
        // " | "
        if (!suffixes.empty())
        {
            window->DrawList->AddText(pos, GetColorU32(darkGrey), " | ");
            pos.x += CalcTextSize(" | ").x;
        }

        // [suffix] [suffix] ...
        for (const auto& suffix : suffixes)
        {
            window->DrawList->AddText(pos, GetColorU32(grey), " [");
            pos.x += CalcTextSize(" [").x;
            window->DrawList->AddText(pos, GetColorU32(suffix.color), suffix.name.c_str());
            pos.x += CalcTextSize(suffix.name.c_str()).x;
            window->DrawList->AddText(pos, GetColorU32(grey), "]");
            pos.x += CalcTextSize("]").x;
        }

        if (display_frame)
            window->DrawList->PopClipRect();

        if (is_open && !(flags & ImGuiTreeNodeFlags_NoTreePushOnOpen))
            TreePushOverrideID(id);
        IMGUI_TEST_ENGINE_ITEM_INFO(id, "player", 
                                    g.LastItemData.StatusFlags | (is_leaf ? 0 : ImGuiItemStatusFlags_Openable) | 
                                    (is_open ? ImGuiItemStatusFlags_Opened : 0));
        return is_open;
    }
}

void PlayerListWindow()
{
    ImGui::Begin("New Player List", nullptr);

    {
        struct ComparePlayerInfo {
            bool operator()(const PlayerInfo& a, const PlayerInfo& b) const {
                return a.photonActorID < b.photonActorID;
            }
        };

        std::vector<std::reference_wrapper<PlayerInfo>> playerVec;
        for (auto& pair : cachedPlayerlist) {
            playerVec.push_back(std::ref(pair.second));
        }
        std::ranges::sort(playerVec.begin(), playerVec.end(), ComparePlayerInfo());

        for (unsigned long long i = 0; i < playerVec.size(); i++) {
            PlayerInfo& player = playerVec[i].get();
            PhotonPlayer*& photonPlayer = player.photonPlayer;
            ImVec4 nameColor = { 1.0, 1.0, 1.0, 1.0 };
            RecRoomPlayer* playerPlayer = nullptr;
            bool isPlayerVMOD = false;
            int32_t playerPing = -1;
            int hardwareType = -1;
            
            if (player.loadingStage >= LoadingStage::LOADED)
                playerPlayer = RecRoomPlayer::GetFromActorNumber(player.photonActorID);
            
            if (IsBlacklistedPlayerID(playerIdBlacklist, std::stoi(player.playerID)))
                isPlayerVMOD = true;

            if (playerPlayer != nullptr && player.loadingStage >= LoadingStage::LOADED)
            {
                playerPing = playerPlayer->get_Ping();
                hardwareType = playerPlayer->get_HardwareType();
            }

            std::string hardwareTypeString = PL::PlatformToString((HardwareType)hardwareType);
            
            if (player.loadingStage < LoadingStage::LOADED)
                nameColor = ImVec4(1.0f, 195.0f / 255.0f, 71.0f / 255.0f, 1.0f);      // yellow
            else if (player.isLocalPlayer)
                nameColor = ImVec4(71.0f / 255.0f, 1.0f, 167.0f / 255.0f, 1.0f);    // green
            else if (playerPlayer != nullptr && playerPlayer->get_IsFriend())
                nameColor = ImVec4(0.0f, 0.7f, 1.0f, 1.0f);                         // blueish
            else if (isPlayerVMOD)
                nameColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);                           // red
            
            std::vector<PL::suffix> suffixes;

            if (player.loadingStage >= LoadingStage::PHOTON && PhotonNetwork::get_isMasterClient(player.photonPlayer))
                suffixes.push_back({"M", "Master Client.", ImVec4(1.0f, 0.0f, 1.0f, 1.0f)});
            if (isPlayerVMOD)
                suffixes.push_back({"VMOD", "Volunteer Mod/Staff.", ImVec4(1.0f, 0.0f, 0.0f, 1.0f)});
            
            if (PL::Player(player, nameColor, playerPing,hardwareTypeString, suffixes, playerVec))
            {
                PlayerInfoSection(player, playerPlayer);
                ExploitsSection(player, photonPlayer);
                TeleportsSection(photonPlayer);
                MiscSection(photonPlayer);
                FunSection(photonPlayer);
#ifndef PROD
                TestSection(photonPlayer);
#endif
            }
            else
            {
                std::string tooltipString = player.DisplayName;

                for (auto& suffix : suffixes)
                {
                    if (!suffix.descriptor.empty())
                        tooltipString += "\n" + suffix.name + ": " + suffix.descriptor;
                }
            
                ImGui::SetItemTooltip(tooltipString.c_str());
            }
        }
    }
    
    ImGui::End();
}