#pragma once

struct GiftPackage;
struct GiftManager;

namespace Callbacks
{
    bool Giftbox()
    {
            Il2CppArray* objects = UObject::FindObjectsOfType("UnityEngine.GameObject");

            GiftManager* GiftManagerInstance = nullptr;

            for (int i = 0; i < objects->max_length; i++)
            {
                GameObject* gameObject = il2cpp_array_get(objects, GameObject*, i);

                if (gameObject != nullptr)
                {
                    auto GiftManagerComponent = static_cast<GiftManager*>(gameObject->GetComponent("GiftManager"));

                    if (GiftManagerComponent != nullptr)
                    {
                        ThreadFix();

                        Log::debug("Found GiftManager!");

                        GiftManagerInstance = GiftManagerComponent;
                        Log::debug("epic1");
                        void* gift = GiftPackage::ctor();
                        Log::debug("epic2");
                        if (gift != nullptr)
                        {
                            std::cout << "lp id is : " << (localPlayer.playerID) << std::endl;

                            SetField<int64_t>(gift, 16, 1); // nullable this is likely giftbox id
                            SetField<int32_t>(gift, 32, 1); // no idea this is new maybe recipient
                            SetField<int32_t>(gift, 36, 0); // nullable
                            SetField<Il2CppString*>(gift, 48, il2cpp_string_new_spoof(""));
                            /// should be prefab // AvatarItemDescOrHairDyeDesc  ?? // frOMH6WxDEG1fBqC4_83vg // Consumables
                            //SetField<void*>(gift, 56, nullptr); // nullable also AvatarItemType
                            SetField<AvatarItemType>(gift, 56, AvatarItemType::HairDye); // nullable also AvatarItemType
                            SetField<Il2CppString*>(gift, 64, il2cpp_string_new_spoof("76369aef-aeda-46d2-996a-cd00594d0543,8XajS2adOEOqzqnLy6-zcQ,P12CUkIg8EuFihGQsvPlxg"));
                            // ConsumableItemDesc ?? //Avatar GUID
                            //SetField<void*>(gift, 72, nullptr); // MEMBER(System::Nullable<System::Guid>, JEBHHDJLFEH, 72); // probably avatar guid
                            SetField<Il2CppString*>(gift, 96, il2cpp_string_new_spoof("")); // EquipmentPrefabName ??
                            SetField<Il2CppString*>(gift, 104, il2cpp_string_new_spoof("")); // EquipmentModificationGuid ??
                            SetField<CurrencyType>(gift, 112, CurrencyType::Invalid); // CurrencyType
                            SetField<int32_t>(gift, 116, 0); // Amount Currency
                            SetField<int32_t>(gift, 120, 0); // Amount XP
                            SetField<GiftContext>(gift, 124, GiftContext::Purchased_Gift_C); // GiftContext
                            SetField<GiftRarity>(gift, 128, GiftRarity::Legendary); // GiftRarity
                            SetField<Il2CppString*>(gift, 136, il2cpp_string_new_spoof("'We are always one step ahead of our hackers.' -Shawn 22/08/2019"));
                            /// this is name of yelllow message this is custom message
                            SetField<PlatformType>(gift, 144, PlatformType::All); // PlatformType
                            SetField<PlatformMask>(gift, 148, PlatformMask::All); // PlatformMask
                            SetField<StorefrontBalanceType>(gift, 152, StorefrontBalanceType::SteamPurchased);
                            // StorefrontBalanceType nullable
                            SetField<bool>(gift, 160, false); // Consumed
                            SetField<bool>(gift, 161, true); // CanSpawnOnCurrentPlatform ??
                            SetField<Il2CppString*>(gift, 168, il2cpp_string_new_spoof("")); // ErrorMessage
                            SetField<bool>(gift, 176, true); // IsValid ??
                            SetField<bool>(gift, 177, false); // IsGifted ??

                            GiftManager::GiftPackageReceivedArgs giftargs = {gift, true, true};
                            GiftManagerInstance->OnGiftPackageReceivedEvent(giftargs);

                            
                        }

                        break;
                    }
                }
            }

    	return true;
    }
}
