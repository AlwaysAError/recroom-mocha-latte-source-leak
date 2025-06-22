#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#include <mutex>
#include <chrono>
#include <iostream>

namespace Log {
    void error(const std::string& message);
    void debug(const std::string& message);
}


namespace veh {
    void Hook(void* source, void* destination); // Ensure this is implemented somewhere
}

inline std::timed_mutex rehookMutex;

class HookManager {
public:
    enum class HookType {
        PAGEGUARD,
        INLINE
    };

    struct PageGuardInfo {
        void* source;
        void* destination;

        PageGuardInfo(void* src, void* dst) : source(src), destination(dst) {}
    };

    struct InlineInfo {
        PVOID* ppPointer;
        PVOID pDetour;

        InlineInfo(PVOID* pp, PVOID dt) : ppPointer(pp), pDetour(dt) {}
    };

    using HookInfo = std::variant<PageGuardInfo, InlineInfo>;

    struct InternalHookData {
        bool& enabled;
        HookType type;
        HookInfo info;

        InternalHookData(bool& en, HookType ht, HookInfo hi)
            : enabled(en), type(ht), info(hi) {}
    };

    bool isIHooksInitialized = false;
    std::unordered_map<std::string, std::vector<InternalHookData>> HookMap;

    HookType hookPriority = HookType::PAGEGUARD;
    bool isUpdateHooksInExecution = false;

    void AddPageGuardHook(const std::string& name, bool& toggle, void* source, void* destination);
    void AddInlineHook(const std::string& name, bool& toggle, PVOID* ppPointer, PVOID pDetour);

    bool InitializeInlineHooks();  // Stub, user should define connection logic
    bool UpdateHooks();
};

inline HookManager* pHookManager = nullptr;

// --- Implementation ---

inline void HookManager::AddPageGuardHook(const std::string& name, bool& toggle, void* source, void* destination) {
    HookMap[name].emplace_back(toggle, HookType::PAGEGUARD, PageGuardInfo(source, destination));
}

inline void HookManager::AddInlineHook(const std::string& name, bool& toggle, PVOID* ppPointer, PVOID pDetour) {
    HookMap[name].emplace_back(toggle, HookType::INLINE, InlineInfo(ppPointer, pDetour));
}

inline bool HookManager::InitializeInlineHooks() {
    if (isIHooksInitialized) return false;

    // Add detour setup logic here if needed
    isIHooksInitialized = true;
    Log::debug("HookManager initialized");
    return true;
}

inline bool HookManager::UpdateHooks() {
    if (rehookMutex.try_lock_for(std::chrono::milliseconds(120))) {

        for (auto& [name, hookVector] : HookMap) {
            if (hookVector.size() > 1) {
                for (auto& hook : hookVector) {
                    if (std::holds_alternative<PageGuardInfo>(hook.info)) {
                        PageGuardInfo& Info = std::get<PageGuardInfo>(hook.info);
                        if ((hookPriority == HookType::PAGEGUARD) && hook.enabled)
                            veh::Hook(Info.source, Info.destination);
                        else if (hook.enabled)
                            hook.enabled = false;
                    }
                    if (std::holds_alternative<InlineInfo>(hook.info)) {
                        if ((hookPriority == HookType::PAGEGUARD) && hook.enabled)
                            hook.enabled = false;
                    }
                }
            }
            else {
                for (auto& hook : hookVector) {
                    if (std::holds_alternative<PageGuardInfo>(hook.info)) {
                        PageGuardInfo& Info = std::get<PageGuardInfo>(hook.info);
                        if (hook.enabled)
                            veh::Hook(Info.source, Info.destination);
                    }
                }
            }
        }

        rehookMutex.unlock();
        return true;
    }
    else {
        Log::error("Failed to get rehook mutex!");
    }

    return false;
}
