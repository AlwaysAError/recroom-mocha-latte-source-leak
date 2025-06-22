#pragma once

double cachedVertical = 0.0f;

void packetfly() {

    if (globals::packetfly::toggle) {

        if (localPlayer.loadingStage >= LoadingStage::LOADED) {

            RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);

            if (playerPlayer != nullptr) {

                if (playerPlayer->get_IsInitialized() && playerPlayer->get_IsInitialLoadFinished()) {

                    float verticalSpeed = globals::packetfly::verticalSpeed;
                    float horizontalSpeed = globals::packetfly::horizontalSpeed;

                    if ((GetAsyncKeyState(VK_LSHIFT) & 0x8000) && !globals::Open)
                    {
                        verticalSpeed = globals::packetfly::verticalSpeed * 2;
                        horizontalSpeed = globals::packetfly::horizontalSpeed * 2;
                    }

                    auto playerTrackingSpace = playerPlayer->get_TrackingSpace();
                    auto playerTrackingSpaceTransform = playerTrackingSpace->get_transform();
                    auto playerTrackingSpacePos = playerTrackingSpaceTransform->get_position();

                    auto playerTrackingSpaceForwards = playerTrackingSpaceTransform->get_forward();
                    auto playerTrackingSpaceUp = playerTrackingSpaceTransform->get_up();
                    auto playerTrackingSpaceRight = playerTrackingSpaceTransform->get_right();

                    float deltaTime = Time::get_deltaTime();

                    if (globals::packetfly::lockVertical) {
                        if (cachedVertical == 0.001337) {
                            cachedVertical = playerTrackingSpacePos.y;
                        }
                        playerTrackingSpacePos.y = cachedVertical;
                    }

                    if (globals::packetfly::vertical) {
                        // up
                        if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && !globals::Open)
                        {
                            playerTrackingSpacePos.x += playerTrackingSpaceUp.x * verticalSpeed * deltaTime;
                            playerTrackingSpacePos.y += verticalSpeed * deltaTime;  // Direct vertical speed
                            playerTrackingSpacePos.z += playerTrackingSpaceUp.z * verticalSpeed * deltaTime;

                            playerTrackingSpaceTransform->set_position(playerTrackingSpacePos);
                        }

                        // down
                        if ((GetAsyncKeyState(VK_LCONTROL) & 0x8000) && !globals::Open)
                        {
                            playerTrackingSpacePos.x -= playerTrackingSpaceUp.x * verticalSpeed * deltaTime;
                            playerTrackingSpacePos.y -= verticalSpeed * deltaTime;  // Direct vertical speed
                            playerTrackingSpacePos.z -= playerTrackingSpaceUp.z * verticalSpeed * deltaTime;

                            playerTrackingSpaceTransform->set_position(playerTrackingSpacePos);
                        }
                    }

                    if (globals::packetfly::horizontal) {
                        Vector3 moveDirection = {};

                        // Combine all movement inputs
                        if ((GetAsyncKeyState('W') & 0x8000) && !globals::Open)
                            moveDirection = moveDirection + playerTrackingSpaceForwards;
                        if ((GetAsyncKeyState('S') & 0x8000) && !globals::Open)
                            moveDirection = moveDirection - playerTrackingSpaceForwards;
                        if ((GetAsyncKeyState('D') & 0x8000) && !globals::Open)
                            moveDirection = moveDirection + playerTrackingSpaceRight;
                        if ((GetAsyncKeyState('A') & 0x8000) && !globals::Open)
                            moveDirection = moveDirection - playerTrackingSpaceRight;

                        // Normalize the movement direction if it's not zero
                        if (moveDirection.x != 0 || moveDirection.y != 0 || moveDirection.z != 0) {
                            float length = sqrt(moveDirection.x * moveDirection.x +
                                moveDirection.y * moveDirection.y +
                                moveDirection.z * moveDirection.z);
                            moveDirection.x /= length;
                            moveDirection.y /= length;
                            moveDirection.z /= length;

                            // Apply movement
                            playerTrackingSpacePos.x += moveDirection.x * horizontalSpeed * deltaTime;
                            playerTrackingSpacePos.y += moveDirection.y * horizontalSpeed * deltaTime;
                            playerTrackingSpacePos.z += moveDirection.z * horizontalSpeed * deltaTime;

                            playerTrackingSpaceTransform->set_position(playerTrackingSpacePos);
                        }
                    }

                    if (globals::packetfly::lockVertical) {
                        cachedVertical = playerTrackingSpacePos.y;
                        playerTrackingSpaceTransform->set_position(playerTrackingSpacePos);
                    }
                }
                else {
                    cachedVertical = 0.001337;
                }
            }
            else {
                cachedVertical = 0.001337;
            }
        }
        else {
            cachedVertical = 0.001337;
        }
    }
    else {
        cachedVertical = 0.001337;
    }

}