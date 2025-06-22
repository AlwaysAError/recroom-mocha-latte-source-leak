#pragma once

enum BodyPart // the first field of PlayerDamageSetting contains this enum
{
    None = -1,
    Head = 0,
    Torso = 1,
    LeftHand = 2,
    RightHand = 3,
    Mouth = 4,
    Legs = 5,
    LeftFoot = 6,
    RightFoot = 7,
    FullBody = 8,
    Nose = 9,
    Face = 10,
};

namespace DamageType {
    enum WeaponDamageType
    {
        DEFAULT = 0,
        NON_COMBAT_COLLISION = 1,
        MELEE = 1000,
        MELEE_SHIELD = 1001,
        THROWABLE = 1002,
        RANGED_GUN = 2000,
        RANGED_BOW = 2001,
        RANGED_SHOTGUN = 2002,
        RANGED_AUTOMATIC = 2003,
        RANGED_RIFLE = 2004,
        EXPLOSIVE = 3000,
        MAGIC = 3001,
        PHYSICS = 3002,
        SELF_ATTACK = 3003,
        VEHICLE_COLLISION = 3004,
        ENEMY_WEAPON = 5000,
    };
}

struct RangedWeaponScreenToolBehaviorConfig : MonoBehaviourPun {};

struct Weapon : MonoBehaviourPun {

    typedef Tool* (*get_Tool_t)(Weapon* instance);
    Tool* get_Tool() {
        const auto func = (get_Tool_t)(methods::RecRoomCoreCombat::Weapon::get_Tool);
        return func(this);
    }

};

struct MakerPen : Component {

    typedef Tool* (*get_Tool_t)(MakerPen* instance);
    Tool* get_Tool() {
        const auto func = (get_Tool_t)(methods::MakerPen::get_Tool);
        return func(this);
    }

};

struct Bullet : Component {

    typedef Vector3 (*get_Velocity_t)(Bullet* instance);
    Vector3 get_Velocity() {
        const auto func = (get_Velocity_t)(GameAssembly + 0xD49E20);
        return func(this);
    }
};


struct RangedWeapon : Weapon {

	typedef void (*Fire_t)(RangedWeapon* instance, float charge);
	void Fire(float charge) {
		const auto func = (Fire_t)(methods::RecRoomCoreCombat::RangedWeapon::Fire);
		return func(this, charge);
	}

	typedef RangedWeaponScreenToolBehaviorConfig*(*get_RangedWeaponScreenToolBehaviorConfig_t)(RangedWeapon* instance);
	RangedWeaponScreenToolBehaviorConfig* get_RangedWeaponScreenToolBehaviorConfig() { // this is obfuscated, search term: "RangedWeaponScreenToolBehaviorConfig* "
		const auto func = (get_RangedWeaponScreenToolBehaviorConfig_t)(GameAssembly + 0x1C1AAE0);
		return func(this);
	}

    typedef bool (*get_HasBulletDrop_t)(RangedWeapon* player);
    bool get_HasBulletDrop() {
        if (this == nullptr) return false;
        return false; //! remove this when offset updated cunt
        const auto func = (get_HasBulletDrop_t)(GameAssembly + 0x0); //! dickhead this shit is obfuscated and idk where tf it came from - top g
        return func(this);
    }

};