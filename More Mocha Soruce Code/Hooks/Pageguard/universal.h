#pragma once

// NOP
void __fastcall uNop_hook() {
    return;
}

// bools
bool __fastcall uTrue_hook() {
    return true;
}

bool __fastcall uFalse_hook() {
    return false;
}

// Floats
float __fastcall uFloatBig_hook() {
    return 99.9f;
}

float __fastcall uFloatHuge_hook() {
    return 99999999.9f;
}

float __fastcall uFloatZero_hook() {
    return 0.0f;
}

// INT32
INT32 __fastcall uIntBig_hook() {
    return INT32(999999);
}

INT32 __fastcall uIntOne_hook() {
    return INT32(1);
}

int32_t __fastcall uIntZero_hook() {
    return int32_t(0);
}