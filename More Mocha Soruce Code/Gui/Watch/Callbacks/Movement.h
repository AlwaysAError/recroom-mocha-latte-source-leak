#pragma once

namespace ButtonCallbacks
{
    // force static fly toggle
    
    void SetGravity(UIButton* instance)
    {
        Physics::set_gravity(globals::gravity);
    }
    
    void RestoreGravity(UIButton* instance)
    {
        Physics::set_gravity({ 0.0f, -9.81f, 0.0f });
    }
}