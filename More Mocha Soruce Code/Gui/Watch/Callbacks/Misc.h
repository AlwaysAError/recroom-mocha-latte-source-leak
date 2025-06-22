#pragma once

namespace ButtonCallbacks
{
    void SendChatMessage(UIButton* instance)
    {
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::SendChatMessage);
    }

    void ShowNotificationAll(UIButton* instance)
    {
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::ShowNotificationAll);
    }

    void ShowBannerNotificationAll(UIButton* instance)
    {
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::ShowBannerNotificationAll);
    }

    // Fling Random Toggle
    
    void SelectTMZCamera(UIButton* instance)
    {
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::SelectTMZCamera);
    }

    void ClearTMZCameraSelection(UIButton* instance)
    {
        shareCameraPV = nullptr;
    }

    // TMZ Camera Toggle

    // SetSelfMasterClient button here

    void DeleteAll(UIButton* instance)
    {
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::DeleteAll);
    }

    void SpawnJediObject(UIButton* instance)
    {
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::SpawnJediObject);
    }

    // Jedi Dominant Hand Toggle

    // Jedi Legacy Mode Toggle

    void QuestSkip(UIButton* instance)
    {
        QuestManager* manager = QuestManager::get_Instance();

        if (manager != nullptr)
            manager->set_DefaultRoomIndex(GetField<int32_t>(manager, 336) - 1); // total room count - 1
    }
    
    void GiveSRank(UIButton* instance)
    {
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

    void GenerateQuestGift(UIButton* instance)
    {
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::GenerateQuestGift);
    }

    void RenameTextObjects(UIButton* instance)
    {
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::RenameAllTexts);
    }

    void DestroySitSeats(UIButton* instance)
    {
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

    // Sit on head loop toggle
    
    void DestroySitOnHeadSeat(UIButton* instance)
    {
        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::DestroySitOnTargetSeat);
    }
}