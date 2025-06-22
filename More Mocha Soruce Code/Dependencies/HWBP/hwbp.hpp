#pragma once

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <type_traits>

#include <Windows.h>
#include <tlhelp32.h>


class hook_manager;

class hwbp_hook {
public:
	hwbp_hook(hook_manager* manager);
	~hwbp_hook();

	bool hook(void* target, void* hook, HANDLE thread = nullptr);
	bool unhook(HANDLE thread = nullptr);
	bool rehook();
	bool hooked();

	template <class T, class... Args>
	constexpr T call(Args... args) {
		if constexpr (!std::is_same<T, void>::value) {
			T t;
			if (!_hooked) return T(0);
			if (!unhook(GetCurrentThread())) return T(0);
			t = original<T(*)(Args...)>()(args...);
			if (!rehook()) return T(0);
			return t;
		}
		else {
			if (!_hooked) return;
			if (!unhook(GetCurrentThread())) return;
			original<T(*)(Args...)>()(args...);
			rehook();
		}
	}

	template <class T>
	T original();
	template <class T>
	T hook_addr();

private:
	char _register = 0;
	CONTEXT* _ctx = nullptr;
	hook_manager* _manager = nullptr;
	void* _original = nullptr;
	void* _hook = nullptr;
	bool _hooked = false;
	bool _original_call = false;
};

template<class T>
inline T hwbp_hook::original() {
	return reinterpret_cast<T>(_original);
}

template<class T>
inline T hwbp_hook::hook_addr() {
	return reinterpret_cast<T>(_hook);
}


using _mhooks = std::map<std::string, std::shared_ptr<hwbp_hook>>;

class hook_manager {
public:
	static hook_manager& get();

	bool init(PVECTORED_EXCEPTION_HANDLER handler = nullptr);
	bool deinit();
	_mhooks& all();

	std::vector<HANDLE>* threads();
	std::shared_ptr<hwbp_hook>& operator[](const std::string& hook);

private:
	hook_manager() = default;
	~hook_manager();
	hook_manager(const hook_manager&) = delete;
	hook_manager& operator=(const hook_manager&) = delete;

private:
	static hook_manager _manager;
	bool _initialized = false;
	_mhooks _hooks = {};
	void* _handle = nullptr;
	std::vector<HANDLE> _thread_handles;
	PVECTORED_EXCEPTION_HANDLER _handler = nullptr;
};

#ifdef _WIN64
#define XIP Rip
#else
#define XIP Eip
#endif

hook_manager hook_manager::_manager;

hook_manager& hook_manager::get() {
	return _manager;
}








__forceinline hwbp_hook* get_hook(PEXCEPTION_POINTERS info) {

	if (info == nullptr) return nullptr;

	for (auto& [name, data] : hook_manager::get().all()) {

		if (!data->hooked()) continue;

		if (info->ContextRecord->XIP == data->original<uintptr_t>())
			return data.get();
	}
	return nullptr;
}

#define SINGLE_STEP 0x100

LONG __stdcall _internal_handler(PEXCEPTION_POINTERS info) {

	if (info->ExceptionRecord->ExceptionCode != STATUS_SINGLE_STEP)
		return EXCEPTION_CONTINUE_SEARCH;

	hwbp_hook* hk = get_hook(info);
	if (hk == nullptr)
		return EXCEPTION_CONTINUE_EXECUTION;

	info->ContextRecord->XIP = hk->hook_addr<uintptr_t>();

	return EXCEPTION_CONTINUE_EXECUTION;
}

LONG __stdcall UnifiedExceptionHandler(PEXCEPTION_POINTERS info);

bool hook_manager::init(PVECTORED_EXCEPTION_HANDLER handler) {

	if (_initialized) return true;

	// Use UnifiedExceptionHandler as the default if no handler is provided
	if (!handler) handler = UnifiedExceptionHandler;

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (snapshot == INVALID_HANDLE_VALUE) return false;

	THREADENTRY32 te32;
	te32.dwSize = sizeof(THREADENTRY32);

	DWORD process_id = GetCurrentProcessId();

	if (!Thread32First(snapshot, &te32)) {
		CloseHandle(snapshot);
		return false;
	}

	do {
		if (te32.th32OwnerProcessID != process_id) continue;
		HANDLE h = OpenThread(THREAD_GET_CONTEXT | THREAD_SET_CONTEXT | THREAD_SUSPEND_RESUME, 0, te32.th32ThreadID);
		if (h != INVALID_HANDLE_VALUE) _thread_handles.push_back(h);
	} while (Thread32Next(snapshot, &te32));

	CloseHandle(snapshot);

	_handle = (PVOID)spoof_call(returnSpoofAddress, RtlpAddVectoredHandler_o, 1, (__int64)handler, (unsigned int)0LL);
	if (_handle != nullptr) {
		_handler = handler;
		_initialized = true;
		return true;
	}
	return false;
	
	#ifdef OLDCODE
	if (_initialized) return true;

	if (!handler) handler = _internal_handler;

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (snapshot == INVALID_HANDLE_VALUE) return false;

	THREADENTRY32 te32;
	te32.dwSize = sizeof(THREADENTRY32);

	DWORD process_id = GetCurrentProcessId();
	DWORD thread_id = GetCurrentThreadId();

	if (!Thread32First(snapshot, &te32)) {
		CloseHandle(snapshot);
		return false;
	}

	do {
		if (te32.th32OwnerProcessID != process_id)
			continue;

		HANDLE h = OpenThread(THREAD_GET_CONTEXT | THREAD_SET_CONTEXT | THREAD_SUSPEND_RESUME, 0, te32.th32ThreadID);
		if (h != INVALID_HANDLE_VALUE)
			_thread_handles.push_back(h);

	} while (Thread32Next(snapshot, &te32));

	CloseHandle(snapshot);

	_handle = (PVOID)spoof_call(returnSpoofAddress, RtlpAddVectoredHandler_o, 1, (__int64)handler, (unsigned int)0LL);
	
	//_handle = AddVectoredExceptionHandler(1, handler);
	if (_handle != nullptr) {
		_handler = handler;
		_initialized = true;
		return true;
	}

	return false;
	#endif
}

bool hook_manager::deinit() {

	if (!_initialized) return true;

	for (auto handle : _thread_handles)
		CloseHandle(handle);

	if (RemoveVectoredExceptionHandler(_handle)) {
		_initialized = false;
		_handle = nullptr;
		return true;
	}
	return false;
}

_mhooks& hook_manager::all() {
	return _hooks;
}

std::vector<HANDLE>* hook_manager::threads() {
	return &_thread_handles;
}

std::shared_ptr<hwbp_hook>& hook_manager::operator[](const std::string& hook) {

	if (_hooks.find(hook) != _hooks.end())
		return _hooks[hook];

	_hooks[hook] = std::make_shared<hwbp_hook>(this);
	return _hooks[hook];

}

hook_manager::~hook_manager() {
	if (_initialized) deinit();
}

hwbp_hook::hwbp_hook(hook_manager* manager) {
	_manager = manager;
}

hwbp_hook::~hwbp_hook() {
	if (_hooked) unhook();
}

bool hwbp_hook::hook(void* target, void* hook, HANDLE thread) {

	if (_hooked) return true;

	_original = target;
	_hook = hook;

	auto set_hook = [this](HANDLE thread, void* _original) -> bool {

		if (thread == INVALID_HANDLE_VALUE || thread == nullptr)
			return false;

		CONTEXT ctx;
		bool	freeReg = false;

		ZeroMemory(&ctx, sizeof(ctx));
		ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
		if (!GetThreadContext(thread, &ctx)) return false;

		for (_register = 0; _register < 4; _register++) {
			if ((ctx.Dr7 & (1ULL << (_register * 2))) == 0) {
				freeReg = true;
				break;
			}
		}

		if (!freeReg) return false;

		switch (_register) {
		case 0: ctx.Dr0 = reinterpret_cast<uintptr_t>(_original); break;
		case 1: ctx.Dr1 = reinterpret_cast<uintptr_t>(_original); break;
		case 2: ctx.Dr2 = reinterpret_cast<uintptr_t>(_original); break;
		case 3: ctx.Dr3 = reinterpret_cast<uintptr_t>(_original); break;
		default: return false;
		}

		ctx.Dr7 &= ~(3ULL << (16 + 4 * _register));
		ctx.Dr7 &= ~(3ULL << (18 + 4 * _register));
		ctx.Dr7 |= 1ULL << (2 * _register);

		if (!SetThreadContext(thread, &ctx)) return false;

		return true;
	};

	if (thread == nullptr) {
		for (auto thread : *_manager->threads()) {
			set_hook(thread, _original);
		}
	}
	else
		set_hook(thread, _original);

	_hooked = true;
	return true;
}


bool hwbp_hook::unhook(HANDLE thread) {

	if (!_hooked) return true;

	if (thread != nullptr) {
		CONTEXT context;
		context.ContextFlags = CONTEXT_DEBUG_REGISTERS;

		if (GetThreadContext(thread, &context)) {
			context.Dr7 &= ~(1ULL << (2 * _register));
			SetThreadContext(thread, &context);
		}
	}

	else {
		for (auto thread : *_manager->threads()) {

			if (thread == INVALID_HANDLE_VALUE || thread == nullptr)
				continue;

			CONTEXT context;
			context.ContextFlags = CONTEXT_DEBUG_REGISTERS;

			if (GetThreadContext(thread, &context)) {
				context.Dr0 = 0;

				context.Dr7 &= ~(1ULL << (2 * 0));

				SetThreadContext(thread, &context);
			}

		}
	}

	_hooked = false;
	return true;
}

bool hwbp_hook::rehook() {
	return this->hook(_original, _hook, GetCurrentThread());
}

bool hwbp_hook::hooked() {
	return _hooked;
}






LONG __stdcall UnifiedExceptionHandler(PEXCEPTION_POINTERS info) {
    // Prioritize HWBP single-step exceptions
    if (info->ExceptionRecord->ExceptionCode == STATUS_SINGLE_STEP) {
        hwbp_hook* hk = get_hook(info); // From HWB.hpp
        if (hk != nullptr) {
            // HWBP hook found, redirect to hook address
            info->ContextRecord->XIP = hk->hook_addr<uintptr_t>();
            return EXCEPTION_CONTINUE_EXECUTION;
        }
        // If no HWBP hook matches, it might be a page guard single-step
        // Fall through to page guard single-step handling below
    }

    // Handle EXCEPTION_GUARD_PAGE
    if (info->ExceptionRecord->ExceptionCode == EXCEPTION_GUARD_PAGE) {
        uintptr_t exc_addr = (uintptr_t)info->ExceptionRecord->ExceptionAddress;
        uintptr_t page_addr = exc_addr & ~(veh::system_info.dwPageSize - 1);
        bool handled = false;

        //Log::debug("Guard page exception on page: " + AddrToHex((void*)page_addr));

        // Check all hooks to see if the exception is from a hooked function or just on the same page
        for (const HookInfo_t& hook_info : veh::hooks) {
            uintptr_t hook_page = (uintptr_t)hook_info.source & ~(veh::system_info.dwPageSize - 1);
            if (hook_page == page_addr) {
                // Check if exception is within 16 bytes of the hook's source
                if (exc_addr == (uintptr_t)hook_info.source /*exc_addr >= (uintptr_t)hook_info.source && exc_addr < (uintptr_t)hook_info.source + 16*/) {
                    //Log::debug("Exception within 16 bytes of hook at " + AddrToHex(hook_info.source) + ", redirecting to " + AddrToHex(hook_info.destination));
#ifdef _WIN64
                    info->ContextRecord->Rip = (DWORD64)hook_info.destination;
#else
                    exception_info->ContextRecord->Eip = (DWORD)hook_info.destination;
#endif
                    info->ContextRecord->EFlags |= 0x100; // Set trap flag
                    handled = true;
                    break; // Exit loop once a hook is matched
                }
            }
        }

        // If not handled (i.e., not within a hook's 16 bytes), but on a page with hooks, remove PAGE_GUARD
        if (!handled) {
            //Log::debug("Exception on guarded page " + AddrToHex((void*)page_addr) + " but not within hook range, removing PAGE_GUARD");
            PVOID base = (PVOID)page_addr;
            SIZE_T size = veh::system_info.dwPageSize;
            DWORD oldProtect;
            // Remove PAGE_GUARD, assuming original protection was PAGE_EXECUTE_READ
            NtProtectVirtualMemory(GetCurrentProcess(), &base, (PULONG)&size, PAGE_EXECUTE_READ, &oldProtect);
            /*
            auto status = NtProtectVirtualMemory(GetCurrentProcess(), &base, (PULONG)&size, PAGE_EXECUTE_READ, &oldProtect);
            if (status != 0) {
                Log::debug("Failed to remove PAGE_GUARD from page " + AddrToHex((void*)page_addr) + " with status: " + std::to_string(status));
            } else {
                Log::debug("Successfully removed PAGE_GUARD from page " + AddrToHex((void*)page_addr));
            }
            */
            info->ContextRecord->EFlags |= 0x100; // Set trap flag to restore guard later
            //handled = true;
        }

        return EXCEPTION_CONTINUE_EXECUTION;
    }
    // Handle EXCEPTION_SINGLE_STEP
    else if (info->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP) {
        //Log::debug("Single-step exception triggered, restoring guard pages");
        for (const HookInfo_t& hook_info : veh::hooks) {
            PVOID base = hook_info.source;
            SIZE_T size = veh::system_info.dwPageSize;
            DWORD oldProtect;
            //Log::debug("Restoring guard page for hook at " + AddrToHex(hook_info.source));
            NtProtectVirtualMemory(GetCurrentProcess(), &base, (PULONG)&size, PAGE_EXECUTE_READ | PAGE_GUARD, &oldProtect);
            /*
            auto status = 
            if (status != 0) {
                Log::debug("NtProtectVirtualMemory failed for hook at " + AddrToHex(hook_info.source) +
                           " with status: " + std::to_string(status));
            } else {
                Log::debug("Successfully restored PAGE_GUARD for hook at " + AddrToHex(hook_info.source));
            }
            */
        }
        return EXCEPTION_CONTINUE_EXECUTION;
    }

    // Unhandled exception types
    //Log::debug("Exception not handled by this handler, continuing search");
    return EXCEPTION_CONTINUE_SEARCH;
	
	/*
    // Handle page guard exceptions
    if (info->ExceptionRecord->ExceptionCode == EXCEPTION_GUARD_PAGE) {

		Log::debug("pageguard!");
    	
        uintptr_t exc_addr = (uintptr_t)info->ExceptionRecord->ExceptionAddress;
        uintptr_t page_addr = exc_addr & ~(veh::system_info.dwPageSize - 1);
        bool handled = false;

        for (const HookInfo_t& hook_info : veh::hooks) {
            uintptr_t hook_page = (uintptr_t)hook_info.source & ~(veh::system_info.dwPageSize - 1);
            if (hook_page == page_addr && exc_addr == (uintptr_t)hook_info.source) {
            	Log::debug("pageguard hookaaa!");
                // Direct match with a hooked address
                info->ContextRecord->XIP = (DWORD64)hook_info.destination;
                info->ContextRecord->EFlags |= 0x100; // Set trap flag for single-step
                handled = true;
                break;
            }
        	Log::debug("not pageguard hooka!");
        }

        if (!handled && veh::hook_pages.count(page_addr)) {
            // Exception on a guarded page but not a hook address, remove PAGE_GUARD
            PVOID base = (PVOID)page_addr;
            SIZE_T size = veh::system_info.dwPageSize;
            DWORD oldProtect;
            NtProtectVirtualMemory(GetCurrentProcess(), &base, (PULONG)&size, PAGE_EXECUTE_READ, &oldProtect);
            info->ContextRecord->EFlags |= 0x100; // Set trap flag to restore guard
        }
        return EXCEPTION_CONTINUE_EXECUTION;
    }

    // Handle page guard single-step to restore protections
    if (info->ExceptionRecord->ExceptionCode == STATUS_SINGLE_STEP) {
        for (const HookInfo_t& hook_info : veh::hooks) {
            PVOID base = hook_info.source;
            SIZE_T size = veh::system_info.dwPageSize;
            DWORD oldProtect;
            NtProtectVirtualMemory(GetCurrentProcess(), &base, (PULONG)&size, PAGE_EXECUTE_READ | PAGE_GUARD, &oldProtect);
        }
        return EXCEPTION_CONTINUE_EXECUTION;
    }

    // Unhandled exception, pass to next handler
    return EXCEPTION_CONTINUE_SEARCH;
    */
}



/// gamer shit