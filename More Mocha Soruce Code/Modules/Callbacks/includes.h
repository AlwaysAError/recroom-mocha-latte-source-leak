#pragma once

float getRandomScale(const float scaleRange[2])
{
    std::random_device random;
    std::mt19937 generate(random());
    std::uniform_real_distribution<> distribute(scaleRange[0], scaleRange[1]);

    return distribute(generate);
}

namespace PlayerList
{
    void BulletCrashPL(PhotonPlayer*);
    void DestroyGameObject(void*);
};

std::string ToUpperCase(std::string& str);

#include "AudioPlayer.h"
#include "Ban.h"
#include "BannerNotification.h"
#include "BlackFlash.h"
#include "CleanGarbage.h"
#include "Clothing.h"
#include "Death.h"
#include "DisableEACManager.h"
#include "Fling.h"
#include "Freeze.h"
#include "Giftbox.h"
#include "GiveAllTool.h"
#include "GoToRoom.h"
#include "Jedi.h"
#include "KillCv2.h"
#include "Lagger.h"
#include "LevelUp.h"
#include "LocalPlayerScale.h"
#include "Party.h"
#include "QuestGift.h"
#include "RenameText.h"
#include "Sit.h"
#include "SpawnAsset.h"
#include "VoteKickMessage.h"
#include "Tests.h"
#include "BulletCrash.h"
#include "Exterminate.h"
#include "MasterClient.h"
#include "Notification.h"
#include "PhotonExploits.h"
#include "Respawns.h"
#include "SwapPlayers.h"
#include "Teleports.h"
#include "UpdateRoles.h"
#include "BounceBack.h"
#include "DeleteAll.h"
