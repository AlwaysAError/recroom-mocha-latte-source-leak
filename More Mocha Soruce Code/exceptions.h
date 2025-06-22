#pragma once
using _QWORD = unsigned __int64;

void __fastcall FakeMethodInvoker(__int64 methodPointer, __int64 methodInfo,
                                  unsigned __int64 function/*actually object*/, __int64 params, _QWORD exception)
{
    //Log::debug("shit success ma nigger");

    const auto* pFunc = (std::function<void(void*)>*)(function);

    (*pFunc)((void*)params);
}

struct DummyKlass
{
    uint8_t padding[232]; // offset 232 must be non-zero
    uint32_t cctor_finished = 1; // ensure *(DWORD*)(klass + 232) != 0
};

struct DummyV6
{
    uint8_t padding[10];
    uint8_t byte_at_10 = 1; // ensure *(BYTE*)(v6 + 10) == 1
};

DummyKlass dummyKlass{};
DummyV6 dummyV6{};

struct RecRoomMethodInfoOld // 
{
    uint64_t invoker = (uint64_t)&FakeMethodInvoker;
    //uint8_t _pad1[8];
    uint64_t methodPointer = 0x01; // arbitrary non-zero value for *(QWORD*)(a1 + 8)
    uint64_t klassPointer = (uint64_t)&dummyKlass; // klass
    uint64_t v6Pointer = (uint64_t)&dummyV6; //  dummy_v6
    uint8_t _pad2[16];
    uint64_t invokerold = (uint64_t)&FakeMethodInvoker; // invoker method pointer
    uint8_t _pad3[18];
    uint64_t flags = 0x01; // flags, i know this isnt offset 74 IDGAF
    uint8_t _pad4[8];
    //uint64_t invokerold = (uint64_t)&FakeMethodInvoker; // invoker method pointer
};

struct RecRoomMethodInfoOldOld
{
    uint64_t invoker = (uint64_t)&FakeMethodInvoker;
    uint8_t _pad1[2];
    uint8_t uhh = 1;
    uint8_t _pad3[19];
    uint8_t flags = 0x01;
    uint8_t _pad2[49];
    uint64_t klassPointer = (uint64_t)&dummyKlass;
    uint64_t v6Pointer = (uint64_t)&dummyV6;
};

struct RecRoomMethodInfo
{
    uint64_t invoker = (uint64_t)&FakeMethodInvoker;
    uint8_t _pad1[8];
    uint64_t methodPointer = 0x01;
    uint8_t _pad2[6];
    uint8_t ok = 1;
    uint8_t _pad3[48];
    uint64_t klassPointer = (uint64_t)&dummyKlass;
    uint64_t v6Pointer = (uint64_t)&dummyV6;
    
    // 80 = dummyKlass
    // 30 = 1
    // 88 = v6Dummy
    // 16 = methodPointer
    // 0 = invoker
};

//static_assert(offsetof(RecRoomMethodInfo, methodPointer) == 8, "Offset mismatch for methodPointer");
//static_assert(offsetof(RecRoomMethodInfo, klassPointer) == 16, "Offset mismatch for klassPointer");
//static_assert(offsetof(RecRoomMethodInfo, v6Pointer) == 24, "Offset mismatch for v6Pointer");
//static_assert(offsetof(CustomA1, flags) == 74, "Offset mismatch for field_at_74");
//static_assert(offsetof(RecRoomMethodInfo, invoker) == 48, "Offset mismatch for invoker");

void RuntimeInvokeExecutionPathRecreation()
{
    Log::debug("debug 1");

    RecRoomMethodInfo a1_instance{};

    //a1_instance.invoker = (uint64_t)&MyFunction;

    Log::debug("Function pointer address1: " + std::to_string(a1_instance.invoker));

    // Simulate the logic
    uint64_t a1 = (uint64_t)&a1_instance;

    Log::debug("Function pointer address2: " + std::to_string(a1 + 96));

    // Simulate the first condition (a1 + 74)
    if ((*reinterpret_cast<uint8_t*>(a1 + 32) & 0x10) != 0 &&
        *reinterpret_cast<uint64_t*>(a1 + 88) &&
        !*reinterpret_cast<uint32_t*>(*reinterpret_cast<uint64_t*>(a1 + 16) + 232))
    {
        // This should NOT be executed based on your requirements

        Log::debug("debug 12");
        MessageBoxA(nullptr, "Condition 1 executed!", "Error", MB_OK);
        return;
    }
    Log::debug("debug 13");
    // Simulate the second condition (a1 + 48)
    uint64_t v6 = *reinterpret_cast<uint64_t*>(a1 + 48);
    if (*reinterpret_cast<uint8_t*>(v6 + 10) == 1)
    {
        // This block will NOT execute because *(v6 + 10) == 0
        MessageBoxA(nullptr, "Condition 2 executed!", "Error", MB_OK);
        Log::debug("debug 14");
        return;
    }
    Log::debug("debug 15");
    uint64_t v7 = 0LL;
    if (*reinterpret_cast<uint64_t*>(a1 + 122))
    {
        v7 = 0x7FFA51828320 ^ *reinterpret_cast<uint64_t*>(a1 + 8);
    }

    Log::debug("Function pointer address3: " + std::to_string(*reinterpret_cast<uint64_t*>(a1 + 96)));

    Log::debug("debug 17");

    (*(void(__fastcall**)(__int64, __int64, unsigned __int64, __int64, _QWORD))(a1 + 96))(v7, a1, 0x1234, 0x5678, 0LL);

    //func(v7, a1, (unsigned __int64)0x1234, (__int64)0x5678, (_QWORD)0LL);
    Log::debug("debug 18");
}

void CallWithExceptionHandling(std::function<void(void*)> function, void* args)
{
    ThreadFix();

    RecRoomMethodInfo fakeMethodInfo{};

    const MethodInfo* pFakeMethodInfo = (MethodInfo*)&fakeMethodInfo;

    void* pFunction = &function;

    //CleanRuntimeInvoke(pFakeMethodInfo, pFunction, static_cast<void**>(args), nullptr);
}
