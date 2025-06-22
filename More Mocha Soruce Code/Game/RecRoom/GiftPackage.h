#pragma once


enum class AvatarItemType
{
	Outfit = 0,
	HairDye = 1,
	CustomOutfit = 2,
};

enum class CurrencyType
{
	Invalid = 0,
	LaserTagTickets = 1,
	RecCenterTokens = 2,
	LostSkullsGold = 100,
	DraculaSilver = 101,
	RecRoyale_Season1 = 200,
	RoomCurrency = 300,
	RoomInventoryItem = 301,
	ProgressionEvent = 400,
};

enum class GiftContext
{
	None = -1,
	Default = 0,
	First_Activity = 1,
	Game_Drop = 2,
	All_Daily_Challenges_Complete = 3,
	All_Weekly_Challenge_Complete = 4,
	Daily_Challenge_Complete = 5,
	Weekly_Challenge_Complete = 6,
	Unassigned_Equipment = 10, // dont work
	Unassigned_Avatar = 11, // dont work
	Unassigned_Consumable = 12, // dont work
	Reacquisition = 20, // dont work
	Membership = 21, // dont work
	NUX_TokensAndDressUp = 30, 
	NUX_Experiment1 = 31, // dont work
	NUX_Experiment2 = 32, // dont work
	NUX_Experiment3 = 33, // dont work
	NUX_Experiment4 = 34, // dont work
	NUX_Experiment5 = 35, // dont work
	GameRewards = 50, // dont work
	GameRewards_Tokens = 51, // dont work
	GameRewards_Tokens_Experiment_Override = 52, // dont work
	LevelUp = 100,
	Purchased_Gift_A = 500,
	Purchased_Gift_B = 501,
	Purchased_Gift_C = 502,
	Purchased_Gift_D = 503,
	Holiday = 1000, // dont work
	Contest = 1001, // dont work
	Promotion = 1002, // dont work
	LimitedTime = 1003, // dont work
	LimitedTimeEvent = 1004, // dont work
	Deprecated = 1100, // dont work
	RecRoyale = 1200, // dont work
	Friendotron_Gift = 1300,
	DEPRECATED_Paintball_ClearCut = 2000, // dont work
	DEPRECATED_Paintball_Homestead = 2001, // dont work
	DEPRECATED_Paintball_Quarry = 2002, // dont work
	DEPRECATED_Paintball_River = 2003, // dont work
	DEPRECATED_Paintball_Dam = 2004, // dont work
	DEPRECATED_Paintball_DriveIn = 2005, // dont work
	Paintball_ClearCut = 2010,
	Paintball_Homestead = 2011,
	Paintball_Quarry = 2012,
	Paintball_River = 2013,
	Paintball_Dam = 2014,
	Paintball_DriveIn = 2015,
	DEPRECATED_Discgolf_Propulsion = 3000, // dont work
	DEPRECATED_Discgolf_Lake = 3001, // dont work
	Discgolf_Propulsion = 3010,
	Discgolf_Lake = 3011,
	Discgolf_Mode_CoopCatch = 3500,
	Quest_Goblin_A = 4000,
	Quest_Goblin_B = 4001,
	Quest_Goblin_C = 4002,
	Quest_Goblin_S = 4003,
	Quest_Goblin_Consumable = 4004,
	Quest_Cauldron_A = 4010,
	Quest_Cauldron_B = 4011,
	Quest_Cauldron_C = 4012,
	Quest_Cauldron_S = 4013,
	Quest_Cauldron_Consumable = 4014,
	Quest_Pirate1_A = 4100,
	Quest_Pirate1_B = 4101,
	Quest_Pirate1_C = 4102,
	Quest_Pirate1_S = 4103,
	Quest_Pirate1_X = 4104,
	Quest_Pirate1_Consumable = 4105,
	Quest_Dracula1_A = 4200,
	Quest_Dracula1_B = 4201,
	Quest_Dracula1_C = 4202,
	Quest_Dracula1_S = 4203,
	Quest_Dracula1_X = 4204,
	Quest_Dracula1_Consumable = 4205,
	Quest_Dracula1_SS = 4206,
	Quest_SciFi_A = 4500,
	Quest_SciFi_B = 4501,
	Quest_SciFi_C = 4502,
	Quest_SciFi_S = 4503,
	Quest_Scifi_Consumable = 4504,
	DEPRECATED_Charades = 5000,
	Charades = 5001,
	DEPRECATED_Soccer = 6000,
	Soccer = 6001,
	DEPRECATED_Paddleball = 7000,
	Paddleball = 7001,
	DEPRECATED_Dodgeball = 8000,
	Dodgeball = 8001,
	DEPRECATED_Lasertag = 9000,
	Lasertag = 9001,
	DEPRECATED_Bowling = 10000,
	Bowling = 10001,
	StuntRunner_TheMainEvent_A = 11000,
	StuntRunner_TheMainEvent_B = 11001,
	StuntRunner_TheMainEvent_C = 11002,
	StuntRunner_TheMainEvent_D = 11003,
	StuntRunner_TheMainEvent_S = 11004,
	StuntRunner_TheMainEvent_X = 11005,
	StuntRunner_TheMainEvent_Consumable = 11006,
	StuntRunner_TheMainEvent_SS = 11007,
	RecRally = 12000,
	Showdown_A = 12100,
	Showdown_B = 12101,
	Showdown_C = 12102,
	ProgressionEvent = 13000,
	Store_LaserTag = 100000,
	Store_RecCenter = 100010,
	Consumable = 110000,
	Token = 110100,
	Punchcard_Challenge_Complete = 110200,
	All_Punchcard_Challenges_Complete = 110201,
	New_Player_Checklist_Item_Complete = 110300,
	Commerce_Purchase = 200000,
	Gift_Card_Redemption = 210000,
};

enum class GiftRarity
{
	None = -1,
	Common = 0,
	Uncommon = 10,
	Rare = 20,
	Epic = 30,
	Legendary = 50,
};

enum class PlatformType
{
	All = -1,
	Steam = 0,
	Oculus = 1,
	PlayStation = 2,
	Xbox = 3,
	RecNet = 4,
	IOS = 5,
	GooglePlay = 6,
	Standalone = 7,
	Pico = 8,
	Switch = 9,
};

enum class PlatformMask
{
	None = 0,
	Steam = 1,
	Oculus = 2,
	PlayStation = 4,
	Xbox = 8,
	RecNet = 16,
	IOS = 32,
	GooglePlay = 64,
	Standalone = 128,
	Pico = 256,
	Switch = 512,
	All = -1,
};

enum class StorefrontBalanceType
{
	NonPurchasedNotUsableInP2P = -2,
	NonPurchasedDefault = -1,
	SteamPurchased = 0,
	OculusPurchased = 1,
	PlayStationPurchased = 2,
	MicrosoftPurchased = 3,
	IOSPurchased = 5,
	GooglePlayPurchased = 6,
	PicoPurchased = 8,
	RecNetPurchased = 4,
	SwitchPurchased = 9,
	PlayStationNonPurchasedP2P = 100,
	NonPlayStationNonPurchasedP2P = 101,
	NonPurchasedEarnedByP2P = 1000,
	NonPurchasedEarnedByP2Pv2 = 1001,
};

struct GiftPackage : Il2CppObject {

	typedef void (*StaticConstructor_t)(void* hashtable);

	static void* ctor()
	{
		Il2CppClass* klass = FindClass("GHKJMIKCPFE"); // GiftPackage class found from GiftPackageReceivedArgs struct, first field
		Log::debug(std::to_string((uintptr_t)klass));
		void* object = (void*)il2cpp_object_new_spoof(klass);
		Log::debug(std::to_string((uintptr_t)object));

		if (object == nullptr)
			return nullptr;

		const auto func = (StaticConstructor_t)(GameAssembly + 0x9F6BD0); // class ctor
		func(object);
		return object;
	}

};