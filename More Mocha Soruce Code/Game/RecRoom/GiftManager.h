#pragma once

struct GiftManager : MonoBehaviour {

    struct GiftPackageReceivedArgs { // this works BUT this will crash our hook cuz it's not an Il2CppClass* (Il2CppObject*)
        void* GiftPackage; // GHKJMIKCPFE
        bool ShowImmediately;
        bool DismissExisting;
        bool idk;
    };

    typedef void (*OnGiftPackageReceivedEvent_t)(GiftManager* instance, GiftPackageReceivedArgs args);
    void OnGiftPackageReceivedEvent(GiftPackageReceivedArgs args) { // GiftPackageReceivedArgs obfuscated class name -> NPAEHGHLPDF
        const auto func = (OnGiftPackageReceivedEvent_t)(GameAssembly + 0x1EC3140); // find GiftPackageReceivedArgs Struct first, then search for "(GiftPackageReceivedArgs " in GiftManager.h
        return func(this, args);                                            // or below ConsumeGiftBoxImmediately
    }

};