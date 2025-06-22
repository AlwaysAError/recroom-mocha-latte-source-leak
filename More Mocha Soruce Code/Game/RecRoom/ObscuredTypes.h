#pragma once

struct ObscuredInt : Il2CppObject
{
    
    /*
    CLASS("Codestage.Anticheattoolkit.Runtime", "CodeStage.AntiCheat.ObscuredTypes", "ObscuredInt");

    STATIC_MEMBER(int32_t, cryptoKey, 0);

    union
    {
        MEMBER(int32_t, currentCryptoKey, 16);
        MEMBER(int32_t, hiddenValue, 20);
        MEMBER(bool, inited, 24);
        MEMBER(int32_t, fakeValue, 28);
        MEMBER(bool, fakeValueActive, 32);
    };
    */

    int32_t currentCryptoKey;
    int32_t hiddenValue;
    bool inited;
    int32_t fakeValue;
    bool fakeValueActive;

};
