#pragma once

void BlockedActorsUpdate()
{
    std::vector<uint8_t> tempBlockedActorIds;

    // Collect new blocked actor IDs from cachedPlayerlist
    for (auto& [_, playerInfo] : cachedPlayerlist)
    {
        if (playerInfo.blockEvents)
        {
            tempBlockedActorIds.push_back(playerInfo.photonActorID);
        }
    }

    // Add new IDs to blockedActorIds
    for (uint8_t newId : tempBlockedActorIds)
    {
        if (std::find(blockedActorIds.begin(), blockedActorIds.end(), newId) == blockedActorIds.end())
        {
            blockedActorIds.push_back(newId);
        }
    }

    // Remove IDs from blockedActorIds that are no longer in tempBlockedActorIds
    std::erase_if(blockedActorIds,
                  [&tempBlockedActorIds](uint8_t blockID)
                  {
                      return std::find(tempBlockedActorIds.begin(), tempBlockedActorIds.end(), blockID) ==
                          tempBlockedActorIds.end();
                  });
}

void ActorListUpdate()
{
    // Track current actor numbers
    std::unordered_set<int32_t> currentActorNumbers;
    Log::debug("masterbait1");
    // Update existing or add new actors
    for (PhotonPlayer* player : photonPlayerlist)
    {
        Log::debug("masterbait2");
        const int32_t actorNumber = player->getActorNumber();
        Log::debug("masterbait3");
        currentActorNumbers.insert(actorNumber);
        Log::debug("masterbait4");
        // Only add if not already in map (preserve existing entries)
        if (!actorMap.contains(actorNumber))
        {
            Log::debug("masterbait5");
            actorMap[actorNumber] = player;
        }
        Log::debug("masterbait6");
    }
    Log::debug("masterbait7");

    // Remove old actors not in current list
    auto it = actorMap.begin();
    while (it != actorMap.end())
    {
        Log::debug("masterbait8");
        if (!currentActorNumbers.contains(it->first))
        {
            it = actorMap.erase(it);
        }
        else
        {
            ++it;
        }
    }
    Log::debug("masterbait9");
}

PhotonPlayer* GetPhotonPlayerFromActorNumber(int32_t actorNumber)
{
    auto it = actorMap.find(actorNumber);
    return (it != actorMap.end()) ? it->second : nullptr;
}

int failedLockCount = 0;

void PlayerlistUpdate()
{
    // block other threads from using the playerlist while we update playerlist using a mutex
    Log::debug("Rigger1");
    std::unique_lock<std::timed_mutex> lock(playerlistMutex, std::defer_lock);
    Log::debug("Rigger2");
    if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout)))
    {
        Log::debug("cuntface1");
        bool foundLocalPlayer = false;

        photonPlayerlist.clear(); // reset vector
        //Log::prod("cleared playerlist.");
        Log::debug("cuntface2");
        Il2CppArray* photonPlayerList = PhotonNetwork::get_photonPlayerList();
        Log::debug("cuntface3");
        for (int i = 0; i < photonPlayerList->max_length; i++) // populate vector with players
        {
            Log::debug("cuntface4");
            PhotonPlayer* actualPhotonPlayer = il2cpp_array_get(photonPlayerList, PhotonPlayer*, i);
            Log::debug("cuntface5");
            photonPlayerlist.push_back(actualPhotonPlayer); // push photonplayer* to vector
            Log::debug("cuntface6");
        }
        Log::debug("Rigger3");
        ActorListUpdate();

        //Log::prod("populated playerlist.");

        // now we have a complete list of photonplayer*s
        // update cached players

        for (PhotonPlayer* photonPlayer : photonPlayerlist)
        {
            // for each entry in vector:

            // populate first data in player var
            if (photonPlayer != nullptr)
            {
                // check that it's not a nullptr

                PlayerInfo player{};

                //Log::prod("populating first.");
                Log::debug("jiggerboo1");
                player.photonPlayer = photonPlayer;
                Log::debug("jiggerboo2");
                player.DisplayName = ReadIl2CppString(player.photonPlayer->toStringUsername());
                Log::debug("jiggerboo3");
                player.playerID = ReadIl2CppString(player.photonPlayer->toStringAccountId());
                Log::debug("jiggerboo4");
                player.photonActorID = player.photonPlayer->getActorNumber();
                Log::debug("jiggerboo5");
                player.isMasterClient = PhotonNetwork::get_isMasterClient(photonPlayer);
                Log::debug("jiggerboo6");

                player.isLocalPlayer = GetField<bool>(photonPlayer, 68); // isLocal field
                Log::debug("jiggerboo7");

                //Log::prod("populated first.");

                player.loadingStage = LoadingStage::PHOTON;

                //Log::prod("populated first.111");
                RecRoomPlayer* recRoomPlayer = RecRoomPlayer::GetFromActorNumber(player.photonActorID);
                //Log::prod("populated first.222");
                if (recRoomPlayer != nullptr) // check that pv isnt nullptr
                {
                    player.loadingStage = LoadingStage::RECROOM;
                    /// photonView math breaks when in Rooms 2.0 and with meep.
                    //player.photonViewID = std::stoi(std::to_string(player.photonActorID) + "00001"); // photon view has a feild for photonviewid also
                    //player.photonView = PhotonView::findPhotonView(player.photonViewID);
                    //Log::prod("populated first.333");
                    player.photonView = recRoomPlayer->get_PhotonView();
                    //Log::prod("populated first.444");
                    if (player.photonView != nullptr)
                    {
                        //Log::prod("populated first.");
                        player.photonViewID = GetField<int32_t>(player.photonView, 104); // viewIDField (viewid)
                        player.loadingStage = LoadingStage::RECROOM;

                        if (recRoomPlayer->get_IsInitialized())
                        {
                            //Log::prod("populating second.");
                            // populate second data
                            player.playerGameObject = player.photonView->get_gameObject();
                            //Log::prod("populated second.");
                            // 
                            // cached data populates player
                            if (player.playerGameObject != nullptr)
                            {
                                if (cachedPlayerlist.contains(photonPlayer))
                                {
                                    // check if player is in cache, if so then populate localdata from cache
                                    ////Log::prod("Player " + std::string(player.DisplayName) + " is in cache");
                                    const PlayerInfo& cachedPlayerInfo = cachedPlayerlist[photonPlayer];

                                    player.isMasterClient = cachedPlayerInfo.isMasterClient;
                                    player.isCrashed = cachedPlayerInfo.isCrashed;
                                    player.hasChamsChild = cachedPlayerInfo.hasChamsChild;
                                    player.loadingStage = cachedPlayerInfo.loadingStage;
                                    player.chamsObject = cachedPlayerInfo.chamsObject;
                                    player.hasBeenCrashed = cachedPlayerInfo.hasBeenCrashed;
                                    player.isVanished = cachedPlayerInfo.isVanished;
                                    player.hasTriggeredCloak = cachedPlayerInfo.hasTriggeredCloak;
                                    player.hitboxesExpanded = cachedPlayerInfo.hitboxesExpanded;
                                    player.hasGodmodeWhitelist = cachedPlayerInfo.hasGodmodeWhitelist;
                                    player.blockEvents = cachedPlayerInfo.blockEvents;
                                    player.bounceBackAttempts = cachedPlayerInfo.bounceBackAttempts;

                                    player.isPlayerInCache = true;
                                }

                                // if player hasn't been cached, cache them, if the player is loading then cache them
                                if (!player.isPlayerInCache || (player.loadingStage < LoadingStage::LOADED) || player.
                                    isLocalPlayer)
                                {
                                    // update if the player is local also to fix desync of isLocalPlayer not being cached as true
                                    //Log::prod("Pushed Cached Player " + std::string(player.DisplayName));

                                    if (player.loadingStage < LoadingStage::LOADED)
                                    {
                                        // set loading to false cuz they're not loading anymore
                                        //Log::prod("test shit vmp complains.111");
                                        //std::thread(&LoadingTimer, photonPlayer, 5).detach(); // start async timer for 3 secs (used in esp to account for game renderer loading the players)
                                        player.loadingStage = LoadingStage::LOADED;
                                        //Log::prod("test shit vmp complains.112");
                                    }
                                    //Log::prod("test shit vmp complains.113");
                                    cachedPlayerlist[photonPlayer] = player; // push player to cachemap
                                    //Log::prod("test shit vmp complains.114");
                                }
                            }
                        }
                        else
                        {
                            //Log::prod("Pushed Cached Loading Player " + std::string(player.DisplayName));
                            cachedPlayerlist[photonPlayer] = player;
                            //Log::prod("player is nullptr.");
                        }
                        //Log::prod("populated player.");
                    }
                }
                else
                {
                    //Log::prod("Pushed Cached Loading Player " + std::string(player.DisplayName));
                    cachedPlayerlist[photonPlayer] = player;
                    //Log::prod("player is nullptr.");
                }

                if (player.isLocalPlayer)
                {
                    //Log::debug("localPlayerPP: " + std::to_string((uintptr_t)photonPlayer));
                    localPlayer = player;
                    foundLocalPlayer = true;
                }
            }
        }
        Log::debug("Rigger4");
        ////Log::prod("Finished.");

        // clean up non existing players

        for (auto& localPhotonPlayer : std::views::keys(cachedPlayerlist))
        {
            const bool playerFound = std::ranges::any_of(photonPlayerlist,
                                                         [&](const auto& livePhotonPlayer)
                                                         {
                                                             return livePhotonPlayer == localPhotonPlayer;
                                                         });

            if (!playerFound)
            {
                cachedPlayerlist.erase(localPhotonPlayer);
            }
        }

        if (cachedPlayerlist.size() > photonPlayerlist.size())
        {
            cachedPlayerlist.clear();
        }

        if (foundLocalPlayer)
        {
            localPlayerExists = true;
        }
        else
        {
            localPlayerExists = false;
        }

        //Log::prod("Finished Garbage Collection.");
        Log::debug("Rigger5");
        ActorListUpdate();
        Log::debug("Rigger6");
        BlockedActorsUpdate();
        Log::debug("Rigger7");

        lock.unlock();
        //Log::prod("Unlocked Lock.");
    }
    else
    {
        Log::error("playerlistMutex timed out in PlayerlistUpdate!");
        failedLockCount++;
        if (globals::unlockPlayerlistMutexOnFails && (failedLockCount >= 3))
        {
            Log::error("failed three or more times, unlocking playerlistMutex!");
            playerlistMutex.unlock();
            failedLockCount = 0;
        }
    }
}
