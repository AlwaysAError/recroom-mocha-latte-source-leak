#pragma once
#include <cfloat> // Include this at the top of your file

bool IsPlayerInCircle(const ImVec2& circleCenter, float radius, Vector3 playerPos) {
    // Retrieve the camera and convert player position to screen coordinates
    Camera* camera = Camera::get_current();
    if (camera == nullptr) {
        Log::error("camera is nullptr");
        return false; // If camera is not available, cannot determine the position
    }

    // Convert the player's world position to screen coordinates
    Vector2 screenPos = camera->WorldToScreenPoint(playerPos);

    // Retrieve the screen size
    ImGuiIO& io = ImGui::GetIO();
    float screenHeight = io.DisplaySize.y;
    float screenWidth = io.DisplaySize.x;

    // Check if the player is within the circle
    float dx = screenPos.x - circleCenter.x;
    float dy = screenPos.y - circleCenter.y;
    float distanceSquared = dx * dx + dy * dy;

    return distanceSquared <= (radius * radius);
}

float CalculateVerticalOffset(float distance, float bulletSpeed, float gravity) {
    // Calculate time of flight
    float timeOfFlight = distance / bulletSpeed;

    // Calculate vertical offset due to gravity
    float verticalOffset = 0.5f * gravity * (timeOfFlight * timeOfFlight);

    return verticalOffset;
}

void AimAtPos(float x, float y, float distance, float bulletSpeed, bool applyHeightCompensation) {
    if (!globals::aimbot::toggle) return;

    const int STEPS = globals::aimbot::steps;
    const float AimSpeed = globals::aimbot::aimSpeed;

    ImVec2 screenSize = ImGui::GetIO().DisplaySize;
    float ScreenCenterX = screenSize.x / 2.f;
    float ScreenCenterY = screenSize.y / 2.f;

    float TargetX = (x - ScreenCenterX) / AimSpeed;
    float TargetY = (y - ScreenCenterY) / AimSpeed;

    if (applyHeightCompensation) {
        // Adjust the Y position based on the target's distance from the player (compensating for the drop)
        const float distanceFactor = 0.4f;  // Adjust this factor to fine-tune how much you aim above the target.
        const float speedFactor = bulletSpeed /20.0f;  // Bullet speed scaling factor (tune this value)

        TargetY -= distance * distanceFactor * speedFactor;
    }

    // Clamp the target positions to avoid out-of-bound errors
    if (fabs(TargetX) > ScreenCenterX) TargetX = (TargetX > 0) ? ScreenCenterX : -ScreenCenterX;
    if (fabs(TargetY) > ScreenCenterY) TargetY = (TargetY > 0) ? ScreenCenterY : -ScreenCenterY;

    // Calculate step size for X and Y
    float stepX = TargetX / STEPS;
    float stepY = TargetY / STEPS;

    // Loop to move the mouse gradually
    for (int i = 0; i < STEPS; ++i) {
        mouse_event(MOUSEEVENTF_MOVE, (DWORD)(stepX), (DWORD)(stepY), 0, 0);
    }

    // Final adjustment to ensure the mouse reaches the exact target position
    mouse_event(MOUSEEVENTF_MOVE, (DWORD)(TargetX), (DWORD)(TargetY), 0, 0);
}

Vector3 PredictTargetPosition(Vector3 targetPosHead, Vector3 targetVelocity, float distance, float TimeToImpact) {
    // Estimate the target's future position using its velocity and an assumed time step
    Vector3 predictedPosition = targetPosHead + (targetVelocity * TimeToImpact);
    return predictedPosition;
}

void aimbotCall() {
    if (!globals::aimbot::toggle) return;

    ThreadFix();

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::Begin("Aimbot Window", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoInputs);

    auto draw = ImGui::GetWindowDrawList();

    float screenHeight = io.DisplaySize.y;
    float screenWidth = io.DisplaySize.x;

    ImVec2 screenCenter = ImVec2(screenWidth * 0.5f, screenHeight * 0.5f);
    int radius = globals::aimbot::radius;
    Camera* camera = Camera::get_current();
    if (camera == nullptr) {
        Log::error("camera is nullptr");
    }

    draw->AddCircle(screenCenter, radius, IM_COL32(255, 255, 255, 255), 32);

    static RecRoomPlayer* targetPlayer = nullptr;
    static bool aimKeyPressed = false;
    bool currentAimKeyState = (GetAsyncKeyState(0x50) & 0x8000);

    if (currentAimKeyState) {
        aimKeyPressed = true;
    }
    else {
        aimKeyPressed = false;
        targetPlayer = nullptr; // Reset target when aim key is released
    }

    if (aimKeyPressed) {
        PlayerInfo localPPlayer;
        RecRoomPlayer* localPlayer = nullptr;

        // Find the local player
        for (const auto& [_, player] : cachedPlayerlist) {
            if (player.isLocalPlayer) {
                localPlayer = RecRoomPlayer::GetFromActorNumber(player.photonActorID);
                localPPlayer = player;
                break;
            }
        }
        if (!localPlayer) return; // Ensure localPlayer is valid

        if (targetPlayer == nullptr) {
            // Find the closest valid target within the circle
            float shortestScreenDistance = FLT_MAX;

            for (const auto& [_, player] : cachedPlayerlist) {
                if ((player.loadingStage >= LoadingStage::LOADED) && !player.isLocalPlayer) {
                    RecRoomPlayer* currentPlayer = RecRoomPlayer::GetFromActorNumber(player.photonActorID);
                    if (currentPlayer != nullptr) {
                        Vector3 targetPosHead = currentPlayer->get_CurrentHeadPosition();
                        Vector2 screenPosHead = camera->WorldToScreenPoint(targetPosHead);

                        if (IsPlayerInCircle(screenCenter, radius, targetPosHead)) {
                            float dx = screenPosHead.x - screenCenter.x;
                            float dy = screenPosHead.y - screenCenter.y;
                            float screenDistance = std::sqrt(dx * dx + dy * dy);

                            if (screenDistance < shortestScreenDistance) {
                                shortestScreenDistance = screenDistance;
                                targetPlayer = currentPlayer;
                            }
                        }
                    }
                }
            }
        }

        if (targetPlayer != nullptr) {

            Vector3 localPos = localPlayer->get_CurrentBodyPosition();
            Vector3 targetPosHead = targetPlayer->get_CurrentHeadPosition();
            Vector3 targetVelocity = GetField<Vector3>(targetPlayer->get_Body(), 296);
            float distance = targetPosHead.distanceTo(localPos);
            float BulletSpeed = globals::autoGun::BulletSpeed;

            if (globals::autoGun::BulletDrop) {
                // Get the required game variables
                float gravity = globals::autoGun::Gravity; // Assuming this is stored in your globals
                float BulletSpeed = globals::autoGun::BulletSpeed;

                // Calculate vertical offset using game physics
                float verticalOffset = CalculateVerticalOffset(distance, BulletSpeed, gravity);

                // Predict target position
                float TimeToImpact = distance / BulletSpeed;
                Vector3 predictedPosition = PredictTargetPosition(targetPosHead, targetVelocity, distance, TimeToImpact);
                predictedPosition.y -= verticalOffset; // Adjust for bullet drop

                Vector2 screenPos = camera->WorldToScreenPoint(predictedPosition);
                AimAtPos(screenPos.x, io.DisplaySize.y - screenPos.y, distance, BulletSpeed, true);
            }
            else {
                // Aim directly at the target without compensation
                Vector2 screenPos = camera->WorldToScreenPoint(targetPosHead);
                AimAtPos(screenPos.x, io.DisplaySize.y - screenPos.y, distance, BulletSpeed, false);
            }
        }
    }

    ImGui::End();
}