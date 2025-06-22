#pragma once

void ChangelogCreditsWindow() {

    if (globals::Open) {

        // Set the window size and position
        ImGui::SetNextWindowSize(ImVec2(400, 500), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);

        // Set the window to be rounded and transparent
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 12.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 0.75f)); // Transparent background

        // Begin the window with no title bar, no move, and no resize
        ImGui::Begin("Changelog / Credits", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

        // Add a button to switch between Changelog and Credits
        static bool showChangelog = true;
        if (ImGui::Button(showChangelog ? "Show Credits" : "Show Changelog", ImVec2(ImGui::GetWindowWidth() - 20, 30))) {
            showChangelog = !showChangelog;
        }

        ImGui::Separator();

        // Display the content based on the current state
        if (showChangelog) {
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "Changelog");
            ImGui::Separator();
            ImGui::TextWrapped("v2.1.0 - sigma digma update");
            ImGui::TextWrapped(" + Sit On Head");
            ImGui::TextWrapped(" + HEAT");
            ImGui::TextWrapped(" + TMZ Camera");
            ImGui::TextWrapped(" + Audio module");
            ImGui::TextWrapped(" + Anti Exploits");
            ImGui::TextWrapped(" + Fling module");
            ImGui::TextWrapped(" + Party fuckery");
            ImGui::TextWrapped(" + Levelup fuckery");
            ImGui::TextWrapped(" + Banner notification module");
            ImGui::TextWrapped(" + Rewrote most of the client");
            ImGui::TextWrapped(" + Many optimizations");
            ImGui::TextWrapped(" / Fixed crash issue when joining rooms");
            ImGui::TextWrapped(" / Fixed crash issue with ESP");
            ImGui::TextWrapped(" / Fixed crash issue with PlayerList");
            ImGui::TextWrapped(" / Fixed crash issue with network");
        }
        else {
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Credits");
            ImGui::Separator();
            ImGui::TextWrapped("Captain - Joshua Block");
            ImGui::TextWrapped("Dev - Osamason");
            ImGui::TextWrapped("Dev - \"567\"");
            ImGui::TextWrapped("Dev - TheOneTheWorld");
            ImGui::TextWrapped("Dev - Supremium");
            ImGui::TextWrapped("Intern - Rajesh Singh");
            ImGui::TextWrapped("Intern - Muhammad Shwarma");
            ImGui::TextWrapped("Intern - Abdul Sheikh");
            ImGui::TextWrapped("Intern - Rohan Shah");
            ImGui::TextWrapped("Intern - Ali G");
            ImGui::TextWrapped("Lead Designer - Kristine Western Chandler (Chris Chan aka Jesus Sonichu)");
            ImGui::TextWrapped("Designer - Dexter Morgan");
            ImGui::TextWrapped("Designer - Rick Ross");
            ImGui::TextWrapped("Designer - Daniel Larson");
            ImGui::TextWrapped("Designer - Perc60");
        }

        // End the window
        ImGui::End();

        // Pop the style variables and colors
        ImGui::PopStyleVar(3);
        ImGui::PopStyleColor();
    }
}
