#pragma once
#include "Dependencies/imgui/imgui.h"
#include "Dependencies/imgui/imgui_impl_dx11.h"
#include "Dependencies/imgui/imgui_impl_win32.h"
#include "Dependencies/kiero/kiero.h"

#ifndef GLOBALS_HPP
#define GLOBALS_HPP
#endif

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static Present oPresent = nullptr;
static HWND window = nullptr;
static WNDPROC oWndProc = nullptr;
static ID3D11Device* pDevice = nullptr;
static ID3D11DeviceContext* pContext = nullptr;
static ID3D11RenderTargetView* mainRenderTargetView = nullptr;

uintptr_t base = (uintptr_t)GetModuleHandle(nullptr);
uintptr_t GameAssembly = (uintptr_t)GetModuleHandle("GameAssembly.dll");

HMODULE hNtdll = GetModuleHandle("ntdll.dll");
uintptr_t NtProtectVirtualMemory_addr = (uintptr_t)GetProcAddress(hNtdll, "NtProtectVirtualMemory");

HMODULE GameModule = GetModuleHandle("GameAssembly.dll");
const uint64_t BaseAddress = reinterpret_cast<uint64_t>(GameModule);
const IMAGE_DOS_HEADER* DOSHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(GameModule);
const IMAGE_NT_HEADERS* NtHeaders = reinterpret_cast<IMAGE_NT_HEADERS*>(reinterpret_cast<uintptr_t>(GameModule) + DOSHeader->e_lfanew);
const DWORD SizeOfImage = NtHeaders->OptionalHeader.SizeOfImage;

HMODULE GameModuleUnityPlayer = GetModuleHandle("UnityPlayer.dll");
const uint64_t BaseAddressUP = reinterpret_cast<uint64_t>(GameModuleUnityPlayer);
const IMAGE_DOS_HEADER* DOSHeaderUP = reinterpret_cast<IMAGE_DOS_HEADER*>(GameModuleUnityPlayer);
const IMAGE_NT_HEADERS* NtHeadersUP = reinterpret_cast<IMAGE_NT_HEADERS*>(reinterpret_cast<uintptr_t>(GameModuleUnityPlayer) + DOSHeaderUP->e_lfanew);
const DWORD SizeOfImageUP = NtHeadersUP->OptionalHeader.SizeOfImage;

HMODULE GameModuleNtDLL = GetModuleHandle("ntdll.dll");
const uint64_t BaseAddressNtDLL = reinterpret_cast<uint64_t>(GameModuleNtDLL);
const IMAGE_DOS_HEADER* DOSHeaderNtDLL = reinterpret_cast<IMAGE_DOS_HEADER*>(GameModuleNtDLL);
const IMAGE_NT_HEADERS* NtHeadersNtDLL = reinterpret_cast<IMAGE_NT_HEADERS*>(reinterpret_cast<uintptr_t>(GameModuleNtDLL) + DOSHeaderNtDLL->e_lfanew);
const DWORD SizeOfImageNtDLL = NtHeadersNtDLL->OptionalHeader.SizeOfImage;

struct Vector3 {

	float x;
	float y;
	float z;

	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	float distanceTo(const Vector3& other) const {
		return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z));
	}

	float magnitude() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	void normalize() {

		if (const float mag = magnitude(); mag != 0.0f) {
			x /= mag;
			y /= mag;
			z /= mag;
		}
	}

	static float dot(const Vector3& v1, const Vector3& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	static float angle(const Vector3& a, const Vector3& b) {

		const float dotProduct = dot(a, b);
		const float magnitudes = a.magnitude() * b.magnitude();

		if (magnitudes == 0) {
			return 0.0f;
		}

		float cosineAngle = dotProduct / magnitudes;
		cosineAngle = std::fmax(-1.0f, std::fmin(1.0f, cosineAngle));

		return std::acos(cosineAngle) * (180.0f / 3.14159265358979323846f);
	}

	Vector3 operator+(const Vector3& rhs) const {
		return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	Vector3 operator-(const Vector3& rhs) const {
		return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	Vector3 operator*(const float scalar) const {
		return Vector3(x * scalar, y * scalar, z * scalar);
	}

	Vector3 operator/(const float scalar) const {
		if (scalar != 0.0f) {
			return Vector3(x / scalar, y / scalar, z / scalar);
		}
		return *this; // Avoid division by zero
	}

	Vector3& operator+=(const Vector3& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Vector3& operator-=(const Vector3& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	Vector3& operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	Vector3& operator/=(float scalar) {
		if (scalar != 0.0f) {
			x /= scalar;
			y /= scalar;
			z /= scalar;
		}
		return *this;
	}

	bool operator==(const Vector3& other) const {
		return (x == other.x && y == other.y && z == other.z);
	}

	bool operator!=(const Vector3& other) const {
		return !(*this == other);
	}
};

struct Vector2 {
	float x;
	float y;
};

struct Quaternion {
	float x;
	float y;
	float z;
	float w;

	static Quaternion Euler(const float pitch, const float yaw, const float roll) {
		const float cy = cos(yaw * 0.5);
		const float sy = sin(yaw * 0.5);
		const float cp = cos(pitch * 0.5);
		const float sp = sin(pitch * 0.5);
		const float cr = cos(roll * 0.5);
		const float sr = sin(roll * 0.5);

		Quaternion q;
		q.w = cr * cp * cy + sr * sp * sy;
		q.x = sr * cp * cy - cr * sp * sy;
		q.y = cr * sp * cy + sr * cp * sy;
		q.z = cr * cp * sy - sr * sp * cy;

		return q;
	}

	Quaternion operator*(const Quaternion& q) const {
		Quaternion result;
		result.w = w * q.w - x * q.x - y * q.y - z * q.z;
		result.x = w * q.x + x * q.w + y * q.z - z * q.y;
		result.y = w * q.y - x * q.z + y * q.w + z * q.x;
		result.z = w * q.z + x * q.y - y * q.x + z * q.w;
		return result;
	}
};

std::ostream& operator<<(std::ostream& os, const Vector3& v) {
	os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
	return os;
}

std::ostream& operator<<(std::ostream& os, const Vector2& v) {
	os << "[" << v.x << ", " << v.y << "]";
	return os;
}

std::ostream& operator<<(std::ostream& os, const Quaternion& v) {
	os << "[" << v.x << ", " << v.y << ", " << v.z << v.w << "]";
	return os;
}

struct LineConfig {
	bool state = false;
	bool renderSelf = false;
	bool rainbowColor = false;
	bool gradientColor = false;
	bool distanceColor = false;
	bool fade = false;
	float fadeDistance = 0.0f;
	float maxDistance = 0.0f;
	float minDistance = 0.0f;
	float gradientSpeed = 0.0f;
	ImVec4 staticColor = ImVec4(0, 0, 0, 0);
	ImVec4 gradientStartColor = ImVec4(0, 0, 0, 0);
	ImVec4 gradientEndColor = ImVec4(0, 0, 0, 0);
	ImVec4 closeDistanceColor = ImVec4(0, 0, 0, 0);
	ImVec4 farDistanceColor = ImVec4(0, 0, 0, 0);
	float lineThickness = 1.0f;
};

struct BoxConfig : LineConfig {
	bool dynamic = false;
	bool simpleGradient = false;
	float rounding = 0.0f;
	ImVec2 padding = ImVec2(0, 0);
};

struct NametagConfig : LineConfig {
	bool showActorNumber = false;
	bool showPing = false;
	bool showMasterClient = false;
	bool showVMOD = false;
	bool showIRC = false;
	bool showDistance = false;
	ImVec4 backgroundColor = ImVec4(0, 0, 0, 0);
	// remove these later
	bool background = false;
};

struct ChamsSettings {
	Vector3 scale;
	ImVec4 color; // we translate this to Color later
	float glow;
	int shape;

	// Equality operator
	bool operator==(const ChamsSettings& other) const {
		return (scale == other.scale &&
			color.x == other.color.x && color.y == other.color.y &&
			color.z == other.color.z && color.w == other.color.w &&
			glow == other.glow &&
			shape == other.shape);
	}

	// Inequality operator
	bool operator!=(const ChamsSettings& other) const {
		return !(*this == other);
	}
};

namespace globals
{
	static bool IsClosing = false;
	static bool Open = false;
	static bool showCursor = false;
	static bool PopOutPlayerlist = false;
	static bool legacyPlayerlist = false;
	
	static bool watchMenuTest = false;
	static float headscale = 1.0f;
	static float exterminateVelocity = -50.0f;
	static bool autoVanishToggle = false;
	static bool skillGapToggle = false;
	static bool cloakToggle = false;
	static bool inPromotion = false;
	static bool roomRolePromotion = false;
	static bool staticFlyToggle = false;
	static bool rapidFireToggle = false;
	static int slaveID = 1;
	static int rapidFireCount = 1;
	static float bulletCrashRateLimit = 5000.0;
	static bool opRaiseEventCached = false;
	static bool disableCircuits = false;
	static bool destroyCircuitsManager = false;
	static bool enableSitLoop = false;
	static float sitLoopOffset = 0;
	static bool makerPenDropperToggle = false;
	static bool makerPenDropperAnnounceToggle = false;

	static void* cachedPlayerRoomRoleManager = nullptr;
	static Vector3 gravity = { 0, 0, 0 };
	static std::string messageBuffer = "hello from above!";
	static std::string messagePLBuffer = "hello from PL!";
	static std::string roomIdBuffer = "";
	static std::string textBuffer = "Anti-Cheat? Never met her... \nnew line test";
	static std::string roomNameBuffer = "DormRoom";
	static bool forceLeavePartyGas = false;
	static std::timed_mutex opRaiseEventMutex;
	static float timeScale = 1;

	static bool unlockPlayerlistMutexOnFails = true;
	static bool updatePlayerlistOnUpdate = true;
	static int opRaiseEventMutexTimeout = 2; // seconds
	static int playerlistMutexTimeout = 1000; // ms
	static int onUpdateMutexTimeout = 1; // seconds


	std::string chatMessage = "hi";
	
	static int levelUpFeedback = 0;

	static bool CameraTMZMode = false;

	namespace shaderChams {

		enum Mode {
			Chams,
			ColorChams,
			Pulsing,
			Wireframe,
			Rainbow
		};

		bool toggle = false;
		bool self = false;
		Mode chamsMode = Chams;

		std::string GetCurrentModeString() {
			switch (chamsMode) {
			case (Chams):
				return "Mocha/ChamsShader";
			case (ColorChams):
				return "ColorChams";
			case (Pulsing):
				return "Pulsing";
			case (Wireframe):
				return "Wireframe";
			case (Rainbow):
				return "Rainbow";
			default:
				return "";
			}
		}

		ImVec4 _Color1 = { 1.0f, 4.0f, 1.0f, 1.0f };
		ImVec4 _Color2 = { 4.0f, 1.0f, 1.0f, 1.0f };

		float _Rainbow1 = 0.0f;
		float _Rainbow2 = 0.0f;
		float _GlowIntensity = 1.0f;
		float _Speed = 1.0f;
		float _Wireframe = 0.0f;
		float _LineWidth = 0.001f;
		
		
		ImVec4 _Emissioncolour{ 1.5f, 0.0f, 3.0f, 1.0f };
		ImVec4 _WireColor{ 2.1f, 0.7f, 4.7f, 0.3f };

	}

	namespace audio {
		static std::string blobNameAudioBuffer = "9d5kyj2t50xbm2elnzdorid46.htr";
		static float audioLength = 133.160004;
		static float volume = 1.0f;
		static float speed = 1.0f;
		static bool loop = false;
		static int channel = 4;
	}

	namespace fling {

		static Vector3 velocity = { 0, 3, 0 };
		static float multiplier = 1.0f;
		static bool random = false;
		static float randomVelocityX[2] = { -5.0f, 5.0f };
		static float randomVelocityY[2] = { 2.0f, 5.0f };
		static float randomVelocityZ[2] = { -5.0f, 5.0f };

	}

	namespace bannerNotif {

		static int notificationPosition = 0;
		static float notificationDuration = 3.0f; // this is in seconds
		static std::string titleText = "Mocha Announcement";
		ImVec4 titleTextColor = ImVec4{ 1.0f, 1.0f, 1.0f, 1.0f };
		ImVec4 titleTextBackgroundColor = ImVec4{ 0.773f, 0.576f, 1.0f, 0.7f };
		int titleTextSize = 2;
		static std::string mainText = "Hello World!";
		ImVec4 mainTextColor = ImVec4{ 1.0f, 1.0f, 1.0f, 1.0f };
		ImVec4 mainTextBackgroundColor = ImVec4{ 0.773f, 0.576f, 1.0f, 0.7f };
		static int mainTextSize = 2;
		static std::string leftSideText = "MOCHA";
		static std::string rightSideText = "BETTER";

	}

	namespace xrnsig {

		std::string urlBuffer = "sigma ligma";

	}

	namespace chai {

		static bool swapsToggle = true;
		static bool debugToggle = false;
		static bool debugAllToggle = false;
		static std::vector<std::pair<std::string, std::string>> swaps;

	}

	namespace health {
		static bool godmodeAll = false;
		static int staticValue = 100;

		enum class HealthMode {
			Static,
			OneShot,
			Normal
		};

		static HealthMode healthMode = HealthMode::Normal;


	}

	namespace fov {
		static int fov = 90;
		static int zoomFov = 30;
		static bool zoomToggle = false;
		static bool zoomState = false;
	}

	namespace particles {

		static bool toggle = false;
		static int maxParticles = 100;
		static float circleSize = 5.0f;
		static float connectionRadius = 250.0f;
		static float mouseRepelRadius = 150.0f;
		static float mouseRepelStrength = 1000.0f;
		static float particleSpeed = 100.0f;
		static bool rainbow = false;
		static ImVec4 particleColor = { 1.0f, 1.0f, 1.0f, 1.0f };
		static ImVec4 lineColor = { 1.0f, 1.0f, 1.0f, 1.0f };

	}

	namespace CPPExplorer
	{
		static bool open = false;
	}

	namespace dialRewrite {

		static bool toggle = false;

	}

	namespace colorSkin {

		static bool toggle = false;
		static float glow = 0.0f;
		static ImVec4 color = { 0.0f, 1.0f, 0.0f, 1.0f };
		static bool rainbow = false;
		static float rainbowSpeed = 1.0f;
		static bool self = false;
		static bool others = false;
		static bool black = false;

	}

	namespace chams {

		static bool toggle = false;

		static ChamsSettings settings = {
			Vector3(1.0f, 1.0f, 1.0f),
			ImVec4(1.0, 1.0, 1.0, 1.0),
			1.0f,
			0
		};

	}

	namespace hitboxes {

		static bool toggle = false;
		static bool yToggle = false;
		static float multiplier = 1.0f;

	}

	namespace orbit {
		static bool toggle;
		static bool orbitThreadRun = false;
		static float objectDistance = 1;
		static float objectHeight = 1;
		static float speed = 1;
		std::vector<void*> orbitObjects = {};

	}

	namespace images {

		static std::vector<void*> images;
		static uint32_t currentIndex = 0;

	}

	namespace onUpdate {

		enum class ExecutionCondition {
			ExecInstant, // execute immediately
			ExecLoaded	 // execute when localPlayer has loaded
		};
			
		struct QueuedCallback {
			std::function<bool()> function;						// false will requeue the callback, true to stop execution
			std::chrono::steady_clock::time_point enqueue_time; // time when queued
			std::chrono::milliseconds timeout;					// how long callback should be requeued for
			ExecutionCondition condition;						// conditional execution
		};
			
		std::timed_mutex queueMutex;
		std::vector<QueuedCallback> callbackQueue;
	}

	namespace jedi {
		static bool legacyMode = false;
		static void* prefabGameObject = nullptr;
		static bool dominantHand = true;
		static bool forceEquip = true;
		static bool steal = true;
	}

	namespace gruWeapons {
		static float scale = 1.0f;
		static bool frozen = false;
		static bool grabbale = false;
		static ImVec4 color = ImVec4{1.0f, 1.0f, 1.0f, 1.0f};
	}

	namespace Ihooks {

		static bool OnUpdate = true; /// required true by default because of OnUpdate ExecQueue (delaying this can cause crashes from free'd pointers)
		static bool Instantiate = false;
		static bool InstantiateAssets = false;
		static bool get_IsFlyingEnabled = false;
		static bool get_Health = false;
		static bool OpRaiseEvent = true;
		static bool set_FieldOfView = false;
		static bool OnEvent = true;
		static bool get_deviceUniqueIdentifier = true; /// fuck data collection ong they trying to drown me in this hoe
		static bool setMasterClient = false;
		static bool OnMasterClientSwitched = false;
		static bool AddFlyEnabled = false;
		static bool GetNextGameplayRoomIndex = false;

		/// beta
		static bool RequestDropBeacon = true;

		/// chai
		static bool chai = false;

		/// tests
		static bool joinOrCreateRoom = false;
		static bool RaiseCircuitTick60Hz = false;
		static bool onJoinRoomFailed = false;
		static bool OpSetPropertiesOfRoom = false;
		static bool OpJoinRoom = false;
		static bool GenerateRequestSignature = false;
		static bool SetAccessToken = true;

		static bool RpcPlaySample = false;
		static bool CV2GoToRoom = false;
		static bool RpcLocalGoToRoom = false;

		static bool CreationObjectInventions = false;
		static bool get_IsOnCooldown = false;

		static bool DoesLocalPlayerOwnKey = true;

		static bool get_IsDeveloper = false;
		static bool get_HasActiveRRPlusSubscription = false;
		static bool get_LocalAccountIsModerator = false;

		static bool DisableToxMod = false;
		static bool get_ActiveCameraScale = false;
	}

	namespace veh {
		static bool fly = true;
		static bool itemspawn = false;
		static bool assetspawn = false;
		static bool onUpdate = false;
		static bool opRaiseEvent = false;
		static bool questskip = false;
		static bool chai = false;
	}

	namespace packetfly {
		static bool toggle = false;
		static bool lockVertical = true;
		static double verticalFactor = 0.0f;
		static bool vertical = true;
		static bool horizontal = true;
		static float verticalSpeed = 1.0f;
		static float horizontalSpeed = 1.0f;
	}

	namespace aimbot {

		static bool toggle = false;
		static int radius = 100;
		static float aimSpeed = 1.350;
		static int steps = 100;

	}

	namespace autoGun {

		static bool multiplierMode = false;

		static bool bulletSpeed = false;
		static float bulletSpeedAmount = 1.0f;
		static float bulletSpeedMultiplier = 1.0f;

		static bool automaticBulletSpeed = false;
		static float automaticBulletSpeedAmount = 1.0f;
		static float automaticBulletSpeedMultiplier = 1.0f;

		static bool fireRate = false;
		static float fireRateAmount = 99999999.0f;
		static float fireRateMultiplier = 1.0f;

		static bool ammo = false;
		static int ammoAmount = 1;
		static float ammoMultiplier = 1.0f;

		static bool burstGunMods = false;
		static int burstAmount = 0;
		static float burstMultiplier = 1.0f;

		static bool beamGunMods = false;
		static int beamAmount = 0;
		static float beamMultiplier = 1.0f;

		static bool recoil = false;
		static bool autoGunToggle = false;

		static bool Prediction = false;
		static float BulletSpeed;
		static bool BulletDrop = false;
		static float Gravity = 0.00;


		struct autoGun {
			void* Weapon;
			bool isModded;
		};

		static std::vector<autoGun> autoGunRangedWeapons = {};
	}

	namespace ESP {

		static bool toggle;

		static LineConfig skeleton = {
			true,  // state
			false, // render self
			false, // rainbow color
			true,  // gradient color
			false, // distance color
			false, // fade
			0.0f,  // fade distance
			0.0f,  // max distance
			0.0f,  // min distance
			0.6f,  // gradient speed
			ImVec4(0.0f, 1.0f, 0.0f, 1.0f), // static color (green)
			ImVec4(1.0f, 0.0f, 0.0f, 1.0f), // gradient start color (red)
			ImVec4(0.0f, 0.0f, 1.0f, 1.0f), // gradient end color (blue)
			ImVec4(1.0f, 0.0f, 0.0f, 1.0f),	// close distance color (red)
			ImVec4(0.0f, 1.0f, 0.0f, 1.0f), // far distance color (green)
			1.0f  // line thickness
		};

		static LineConfig tracer = {
			true,  // state
			false, // render self
			false, // rainbow color
			true,  // gradient color
			false, // distance color
			false, // fade
			0.0f,  // fade distance
			0.0f,  // max distance
			0.0f,  // min distance
			1.0f,  // gradient speed
			ImVec4(0.0f, 1.0f, 0.0f, 1.0f), // static color (green)
			ImVec4(1.0f, 0.0f, 0.0f, 1.0f), // gradient start color (red)
			ImVec4(0.0f, 0.0f, 1.0f, 1.0f), // gradient end color (blue)
			ImVec4(1.0f, 0.0f, 0.0f, 1.0f),	// close distance color (red)
			ImVec4(0.0f, 1.0f, 0.0f, 1.0f), // far distance color (green)
			1.0f  // line thickness
		};

		static BoxConfig box = {
			true,  // state
			false, // render self
			false, // rainbow color
			true,  // gradient color
			false, // distance color
			false, // fade
			0.0f,  // fade distance
			0.0f,  // max distance
			0.0f,  // min distance
			0.6f,  // gradient speed
			ImVec4(0.0f, 1.0f, 0.0f, 1.0f), // static color (green)
			ImVec4(1.0f, 0.0f, 0.0f, 1.0f), // gradient start color (red)
			ImVec4(0.0f, 0.0f, 1.0f, 1.0f), // gradient end color (blue)
			ImVec4(1.0f, 0.0f, 0.0f, 1.0f),	// close distance color (red)
			ImVec4(0.0f, 1.0f, 0.0f, 1.0f), // far distance color (green)
			1.0f,  // line thickness
			true,  // dynamic
			false, // simpleGradient
			1.0f,  // rounding
			ImVec2(0.5f, 0.5f) // padding
		};

		static BoxConfig boxOutline = {
			true,  // state
			false, /// render self - unused, uses box config
			false, // rainbow color
			true,  // gradient color
			false, // distance color
			false, /// fade - unused, uses box config
			0.0f,  /// fade distance - unused, uses box config
			0.0f,  /// max distance - unused, uses box config
			0.0f,  /// min distance - unused, uses box config
			0.6f,  /// gradient speed - unused, uses box config
			ImVec4(0.0f, 1.0f, 0.0f, 1.0f), // static color (green)
			ImVec4(1.0f, 0.0f, 0.0f, 1.0f), // gradient start color (red)
			ImVec4(0.0f, 0.0f, 1.0f, 1.0f), // gradient end color (blue)
			ImVec4(1.0f, 0.0f, 0.0f, 1.0f),	// close distance color (red)
			ImVec4(0.0f, 1.0f, 0.0f, 1.0f), // far distance color (green)
			1.0f,  // line thickness
			true,  /// dynamic - unused, uses box config
			false, // simpleGradient - this is forced for simple/static color if gradient is enabled
			1.0f,  /// rounding - unused, uses box config
			ImVec2(0.5f, 0.5f) /// padding - unused, uses box config
		};

		static BoxConfig nametagOutline = {
			true,  // state
			false, /// render self - unused, uses box config
			false, // rainbow color
			true,  // gradient color
			false, // distance color
			false, /// fade - unused, uses box config
			0.0f,  /// fade distance - unused, uses box config
			0.0f,  /// max distance - unused, uses box config
			0.0f,  /// min distance - unused, uses box config
			0.6f,  /// gradient speed - unused, uses box config
			ImVec4(0.0f, 1.0f, 0.0f, 1.0f), // static color (green)
			ImVec4(1.0f, 0.0f, 0.0f, 1.0f), // gradient start color (red)
			ImVec4(0.0f, 0.0f, 1.0f, 1.0f), // gradient end color (blue)
			ImVec4(1.0f, 0.0f, 0.0f, 1.0f),	// close distance color (red)
			ImVec4(0.0f, 1.0f, 0.0f, 1.0f), // far distance color (green)
			1.0f,  // line thickness
			true,  /// dynamic - unused, uses box config
			false, // simpleGradient - this is forced for simple/static color if gradient is enabled
			1.0f,  /// rounding - unused, uses box config
			ImVec2(0.5f, 0.5f) /// padding - unused, uses box config
		};

		static LineConfig targeted = {
			true,  // state
			false, // render self
			false, // rainbow color
			true,  // gradient color
			false, // distance color
			false, // fade
			0.0f,  // fade distance
			0.0f,  // max distance
			0.0f,  // min distance
			0.6f,  // gradient speed
			ImVec4(0.0f, 1.0f, 0.0f, 1.0f), // static color (green)
			ImVec4(1.0f, 0.0f, 0.0f, 1.0f), // gradient start color (red)
			ImVec4(0.0f, 0.0f, 1.0f, 1.0f), // gradient end color (blue)
			ImVec4(1.0f, 0.0f, 0.0f, 1.0f),	// close distance color (red)
			ImVec4(0.0f, 1.0f, 0.0f, 1.0f), // far distance color (green)
			1.0f  // line thickness
		};

		static NametagConfig nametag = {
			true,  // state
			true,  // render self
			false, // rainbow color
			false, // gradient color
			false, // distance color
			true,  // fade
			100.0f, // fade distance
			500.0f, // max distance
			50.0f,  // min distance
			1.0f,   // gradient speed
			ImVec4(0.0f, 1.0f, 0.0f, 1.0f), // static color (green)
			ImVec4(1.0f, 0.0f, 0.0f, 1.0f), // gradient start color (red)
			ImVec4(0.0f, 0.0f, 1.0f, 1.0f), // gradient end color (blue)
			ImVec4(1.0f, 0.0f, 0.0f, 1.0f),	// close distance color (red)
			ImVec4(0.0f, 1.0f, 0.0f, 1.0f), // far distance color (green)
			1.0f,  // line thickness
			true,  // showActorNumber
			true,  // showPing
			true,  // showMasterClient
			true,  // showVMOD
			true,  // showIRC
			true,  // isMochaUser
			ImVec4(0.0f, 0.0f, 0.0f, 0.5f), // background color (black)
			true   // background
		};

	}

	namespace crashes {
		namespace bulletCrash {
			int wandCount = 2000;
			int blunderBussCount = 2000;
		}
		namespace death {

			int numberOfDirections = 8;
			int stepz = 500;
			int countz = 1;
			bool extraz = false;
			float minYz = -5000.0f;
			float maxYz = 1000.0f;
			float minScalez = 1.0f;
			float maxScalez = 1000.0f;
			float decayFactorz = 0.1f;

		}
	}

	namespace photon
	{

		namespace giftbox
		{
			enum GiftType
			{
				Token,
				Clothes,
			};
			static GiftType giftType = Token;
			static std::string clothingBuffer = "76369aef-aeda-46d2-996a-cd00594d0543,8XajS2adOEOqzqnLy6-zcQ,P12CUkIg8EuFihGQsvPlxg";
			static std::string messageBuffer = "LOVE <3 - Mocha User";
			static int32_t tokenAmount = 0;
			static int32_t giftContext = 500;

			// internals
			static bool enableDataSwap = false;
			static int32_t targetActorID = -1;
			static int32_t GBPhotonViewId = 0;
		}
		
		namespace protections
		{
			namespace master
			{

				namespace request
				{
					// toggle for this is just IHook one
					bool duringLoading = false;
					bool loadingFix = false;
				}
				
				namespace callback 
				{
					// toggle for this is just IHook one
					bool duringLoading = false;
					bool loadingFix = false;
					bool restrictOffender = false;
					bool bounceBack = false;
				}
				
				namespace force 
				{
					bool toggle = false;
					bool duringLoading = false;
					bool loadingFix = false;
					bool spam = false;
					bool restrictOffender = false;
					bool bounceBack = false;
				}
			}
		
			namespace inbound
			{
				static bool dropInvalidActorEvents = false;
				
				namespace Ev1
				{
					static bool toggle = false;
					static bool dropAllEvents = false;
					static bool dropServerEvents = false;
					static bool dropSelfEvents = false;
					static bool destroyAllObjects = false;
					static bool filterHashtables = false;
					static bool bounceBack = false;
					static bool restrictActor = false;
				}
				namespace Ev200
				{
					static bool toggle = false;
					static bool dropAllEvents = false;
					static bool dropServerEvents = false;
					static bool dropSelfEvents = false;
					static bool filterWhileLoading = false;
					static bool filterVectorsLimit = false;
					static bool filterServerEvents = false;
					static bool filterSelfEvents = false;
					static float vectorsMinimumLimit = -5000.0f;
					static float vectorsMaximumLimit = 5000.0f;
					static bool filterOwnedPhotonView = false;
					static bool rateLimit = false;
					static bool rateLimitDuringLoading = false;
					static int rateLimitMS = 1000;
					static int rateLimitLimit = 800;
					static bool bounceBack = false;
					static bool restrictActor = false;
				}
				namespace Ev201
				{
					static bool toggle = false;
					static bool dropAllEvents = false;
					static bool dropServerEvents = false;
					static bool dropSelfEvents = false;
					static bool dropDuringLoading = false;
					static bool dropDuringLoadingStrict = false;
				}
				namespace Ev202
				{
					struct BlacklistPrefabPreset
					{
						bool enabled;
						std::string description;
						std::vector<std::string> prefabList;
					};
					
					enum class ScaleFilterMode : int {
						Unusual,
						Limits,
						Both
					};
					
					static bool toggle = false;
					static bool dropAllEvents = false;
					static bool dropServerEvents = false;
					static bool dropSelfEvents = false;
					static bool dropMalformedPayload = false;
					static bool filterToggle = false;
					static bool filterWhileLoading = false;
					static bool filterServerEvents = false;
					static bool filterSelfEvents = false;
					static bool dropDetectedEvent = false;
					static bool filterScale = false;
					static auto scaleFilterMode = ScaleFilterMode::Unusual;
					static float scaleMinimumLimit = 0.3f;
					static float scaleMaximumLimit = 10.0f;
					static bool filterPrefab = false;
					static bool dropBackpacks = false;
					static std::unordered_map<std::string, BlacklistPrefabPreset> blacklistedPrefabPresets = {
						{"bosses",       {true, "Bosses.", {"BOSS", "BOGMONSTER"}}},
						#ifndef PROD
						{"common",       {true, "Common prefabs spawned by cheaters. \nTurn off in #RROs", {"ARENA", "QUEST", "PAINTBALL", "VEHICLE", "[SANDBOX_", "CHARADES", "MICROPHONE"}}},
						#endif
						{"developer",    {true, "Prefabs reversed for developers.", {"SANDBOX_LADDER_HOOK", "SANDBOX_FRIENDOTRON", "GREENSCREEN_TOOL", "STUNTRUNNER", "GLIDER"}}},
						{"managers",     {true, "Any \"Manager\" prefab.", {"MANAGER]"}}},
						{"enemies",      {true, "Enemy prefabs.", {"ENEMY"}}}
					};
					static bool filterVectors = false;
					static bool vectorsFilterData = false;
					static float vectorsMinimumLimit = -5000.0f;
					static float vectorsMaximumLimit = 5000.0f;
					static bool rateLimit = false;
					static bool rateLimitDuringLoading = false;
					static int rateLimitMS = 500;
					static int rateLimitLimit = 20;
					static bool totalActorLimit = false;
					static int totalActorLimitAmount = 20;
					static bool destroyDetectedPrefab = false;
					static bool announceOffender = false;
					static bool bounceBack = false;
					static bool restrictActor = false;
				}
				namespace Ev204
				{
					static bool toggle = false;
					static bool dropAllEvents = false;
					static bool dropServerEvents = false;
					static bool dropSelfEvents = false;
					static bool filterOwnedPhotonView = false;
					static bool bounceBack = false;
					static bool restrictActor = false;
				}
				namespace Ev207
				{
					static bool toggle = false;
					static bool dropAllEvents = false;
					static bool dropServerEvents = false;
					static bool dropSelfEvents = false;
					static bool bounceBack = false;
					static bool restrictActor = false;
				}

				namespace BounceBack
				{
					static bool duringLoading = false;
					static int maxAttempts = 1;
					static bool goToRoom = false;
					static bool respawnAtInfinity = false;
					static bool bulletCrash = false;
					static bool death = false;
				}
			}
			namespace outbound
			{
				
			}
		}
		
		namespace antis {

			enum class BounceBackMode {
				BulletCrash,
				Death
			};

			namespace inbound {

				enum class SanitizeEv200Mode {
					Owned,
					Limits,
					Both
				};

				static bool debugToggle = false;
				static bool debugAntiCheatToggle = false;

				static bool blockFreezeToggle = false;
				static bool blockByeByeToggle = false;
				static bool blockEv207Toggle = false;
				static bool blockMovementToggle = false;
				static bool blockAllToggle = false;
				static bool blockAntiCheatToggle = false;
				static bool blockHeartbeatToggle = false;
				static bool blockEv204Toggle = false;
				static bool sanitizeEv200Toggle = false;
				static SanitizeEv200Mode sanitizeEv200Mode = SanitizeEv200Mode::Owned;
				static bool sanitizeEv200BounceBack = false;
				static BounceBackMode sanitizeEv200BounceBackMode = BounceBackMode::BulletCrash;
				static float maxVectors = 4999.9f;
				static float minVectors = -4999.9f;

				static bool blockAllRPCs = false;

				static bool blockMovementDuringLoad = false;
				static bool blockMovementDuringLoadStrict = false;

				static bool blockRpcsDuringLoad = false;
				static bool blockRpcsDuringLoadStrict = false;
				static bool blockRpcsDuringLoadBlockServer = false;

				static bool masterClientRequest = false;
				static bool masterClientSwitched = false;
				static bool masterClientDebug = false;
				static bool masterClientBounceBack = false;
				static bool masterClientForceMode = false;
				static bool masterClientBlockOffender = false;
				static BounceBackMode masterClientBounceBackMode = BounceBackMode::BulletCrash;

				namespace antiCheat {

					enum class BadScaleMode {
						Unusual,
						Limits,
						Both
					};

					static bool toggle = false;
					static bool blockEvent = false;
					static bool developerPrefabs = false;
					static bool commonPrefabs = false;
					static bool bossPrefabs = false;
					static bool managerPrefabs = false;
					static bool enemyPrefabs = false;
					static bool scaleCheck = false;
					static BadScaleMode scaleMode = BadScaleMode::Unusual;
					static float maxScale = 50.0f;
					static float minScale = 0.09f;
					static bool vectorsCheck = false;
					static bool vectorsCheckStrict = false;
					static float maxVectors = 10000.0f;
					static float minVectors = -10000.0f;
					static bool bounceBack = false;
					static BounceBackMode bounceBackMode = BounceBackMode::BulletCrash;
					static bool destroyPrefab = false;
					static bool destroyPrefabLocally = false;
					static bool excludeServerEvents = false;
					static bool pauseOnLoading = false;
					static bool announceOffender = false;
					static bool blockOffenderEvents = false;
				}

				void* cachedEv24 = nullptr;
			}

			namespace outbound {
				static bool blockAllToggle = false;
				static bool blockAntiCheatToggle = false;
				static bool blockHeartbeatToggle = false;
				static bool blockMovementToggle = false;
				static bool blockPlayerInstantiation = false;
				static bool blockAllPlayerInstantiation = false;

				static bool debugToggle = false;
				static bool debugAntiCheatToggle = false;

				static bool squishPlayer = false;
				static Vector3 playerScale = { 1.0f, 1.0f, 1.0f };
			}
		}
	}

	namespace opRaiseEventEdit {

		std::timed_mutex opRaiseEventEditMutex;

		static bool inExecution = false;
		const std::string magicPrefab = "[QueSt_dRACuLa1_coLlectAblepUMpKin_sMalL]"; // prefab capitilization used to confirm dummy instantiate request
		struct EditInfo {

			enum class CustomType {
				None,
				Die,
			};

			enum class ActorIDsPreset {
				Others,
				Target
			};

			std::string prefabToSwap;
			std::vector<uint32_t> targetActorIDs;
			Vector3 scale;
			Vector3 position;
			int count;
			CustomType customType = CustomType::None;

			void SetActorIDs(ActorIDsPreset preset, uint32_t targetID = 0);
		};

		std::vector<EditInfo> opRaiseEventEditQueue;

	}

	namespace energy
	{
		static bool towerModuleToggle = false;
	}

	namespace instantiate
	{
		static bool debugToggle = false;
		static bool Toggle = false;
		static bool configToggle = false;
		static bool vectorsToggle = false;
		static bool prefabTypeToggle = false;
		static bool randomScaleToggle = false;
		static bool polaroidWhitelistToggle = false;
		static bool playerSpawnWhitelistToggle = false;
		static bool infinityToggle = false;
		static bool infinityScaleToggle = false;
		static bool infinityScaleType = false;
		static bool returnTypeFixToggle = false;
		static bool returnTypeNULLToggle = false;
		static bool blackFlashToggle = false;

		static int Count = 1;

		static std::string prefab = { "[Arena_Pistol]" };

		static Vector3 scale = { 1.0, 1.0, 1.0 };
		static Vector3 position = { 0.0, 0.0, 0.0 };
		static Quaternion rotation = { 0.0, 0.0, 0.0, 0.0 };

		static float randomScaleX[2] = { 0, 0 };
		static float randomScaleY[2] = { 0, 0 };
		static float randomScaleZ[2] = { 0, 0 };
	}

	namespace instantiateAssets
	{
		static bool debugToggle = false;
		static bool Toggle = false;
		static bool configToggle = false;
		static bool vectorsToggle = false;
		static bool prefabTypeToggle = false;
		static bool randomScaleToggle = false;
		static bool polaroidWhitelistToggle = false; // unused
		static bool playerSpawnWhitelistToggle = false; // unused
		static bool infinityToggle = false;
		static bool infinityScaleToggle = false;
		static bool infinityScaleType = false;
		static bool returnTypeFixToggle = false;
		static bool returnTypeNULLToggle = false;
		static bool advancedConfigToggle = false;
		static bool despawnToggle = false;
		static bool blackFlashToggle = false;

		static int Count = 0;

		static std::string prefab = { "[Arena_Pistol]" };

		const char* prefabShareCamera = { "[Arena_Pistol]" };
		const char* prefabFeedbackTool = { "[Arena_Pistol]" };
		const char* prefabStreamerCam = { "[Arena_Pistol]" };
		static Vector3 scaleShareCamera = { 1.0, 1.0, 1.0 };
		static Vector3 scaleFeedbackTool = { 1.0, 1.0, 1.0 };
		static Vector3 scaleStreamerCam = { 1.0, 1.0, 1.0 };

		static Vector3 scale = { 1.0, 1.0, 1.0 };
		static Vector3 position = { 0.0, 0.0, 0.0 };
		static Quaternion rotation = { 0.0, 0.0, 0.0, 0.0 };

		static float randomScaleX[2] = { 0, 0 };
		static float randomScaleY[2] = { 0, 0 };
		static float randomScaleZ[2] = { 0, 0 };
	}

}

#define MUSIC

std::unordered_map<std::string, std::string> audioConfig = {

#ifdef MUSIC
	 // so many corny songs 
    // tyler the creator
    {"Sticky - Tyler The Creator",												"9b5yx9toqmiuwcfhpwum38j22.htr"},
    {"Thought i was dead - album - Tyler The Creator",							"cqmejq1smdo1b7hgwe5quy81h.htr"},
    {"St.Chroma - Tyler The Creator",											"5rjlph4lrgy8n9se9vjrxytgw.htr"},
    {"Noid - Tyler The Creator",												"6lzytf8lwev039qc7gdgzvs59.htr"},
    {"NEW MAGIC WAND - Tyler The Creator",										"4n4ghmalffz1v2cmn1u8u163i.htr"},
    {"EARFQUAKE - Tyler The Creator",											"1wlxb0128g636v63o2hvkh8gd.htr"},
    {"See You Again - Tyler The Creator",										"03mr4pig9x6p1cqvggn4z89rh.htr"},
    {"Yonkers - Tyler The Creator",												"4h4yst7mfqy8kqc90nrqbtc88.htr"},
	{"Thought I Was Dead - Tyler The Creator (ft Playboi Carti)",				"1zlxdhxg8lvhsyxasayjim675.htr"},

    // XXX TENTACION
    {"Moonlight - XXX TENTACION",												"44rkg1krsrlrnxd34sqtzxpxo.htr"},
    {"Look At Me! - XXX TENTACION",												"b2hqmm674b7q73bvingh3kgar.htr"},
    {"SAD! - XXX TENTACION",													"8cgkbqvwewx65xfgf8z6llljn.htr"},
    {"Riot - XXX TENTACION",													"4e4r5f2liyo6asb4hudgk55gx.htr"},
    {"Fuck Love - XXX TENTACION",												"f20z4j7pgftv9ez2c94k9l4lw.htr"},
    {"revenge - XXX TENTACION",													"f01mn3pcdy7cpc8tok45l0yya.htr"},

    // Juice WRLD
    {"Lucid Dreams - Juice WRLD",												"4xc8bvai01z7wn452hdnybx94.htr"},
    {"All Girls Are The Same - Juice WRLD",										"8zxjictf11rcpfncvdl38004y.htr"},
    {"Robbery - Juice WRLD",													"aqcxjw8rl1hjquhgvvgg0l0vp.htr"},
    {"Wishing Well - Juice WRLD",												"6ov3dc0083z9fb0zsqljhdga3.htr"},
    {"Lean Wit Me - Juice WRLD",												"bic6nxlx43uc5b37cgun6z6oc.htr"},

    // Eminem
    {"rap god first 5 mins - Eminem",											"ctogcg8rtnm1r1fnvi8tugue7.htr"},
    {"the real slim shady - Eminem",											"a9i6pns3mxkianej30zsp0okg.htr"},
    {"Till I Collapse - Eminem",												"4hugflmf0d71jgybpq8b3txa0.htr"},
    {"Without Me - Eminem",														"9zfb313leapcoiavdo6r5joey.htr"},
    {"My Name Is - Eminem",														"1qulbvl4z0cvigo1rsu58bjl5.htr"},
    {"Houdini - Eminem",														"dncq8ng6ua20xpaw6nngnqbft.htr"},
    {"Godzilla - Eminem",														"0rll9j64saql74n3skvhutvo0.htr"},

    // Kendrick
    {"Wacced Out Murals - Kendrick",											"ex51afhcajqr0fqo4b2fc1b4r.htr"},
    {"Squabble Up - Kendrick",													"4oq3i8u1b2f8bvbpphegrckby.htr"},
    {"Man At The Garden - Kendrick",											"7p8gso0pda3dlyvro2ak6cmj5.htr"},
    {"TV Off - Kendrick",														"clmu5f1jvi2818huw3d4rss1m.htr"},
    {"Peekaboo - Kendrick",														"e8wvg1yp6n4wqeaywqe5wx7y4.htr"},
    {"Heart pt.6 - Kendrick",													"4sfd0kb8ipw3thkv3n1upwnz4.htr"},
    {"GNX - Kendrick",															"c5m5mxd57p4uwbq5wq6kflph5.htr"},
    {"Crew - Kendrick",															"0nkyvdiv96b01uqcwnt8ybdfi.htr"},

    // the weeknd
    {"Popular - The Weeknd",													"a353jzm3ufbosmu01kp307dvg.htr"},
    {"Starboy - the weeknd",													"4u73q9h2c3ug6whe76l08qnn9.htr"},
    {"Heartless - the weeknd",													"1e81i0juxnk976r8i2nshihrp.htr"},
    {"Timeless ft Playboi Carti - the weeknd",									"be93iol8m537riap40vf5ydr8.htr"},

    // carti
    {"Magnolia - Playboi Carti",												"8lk5ho3pk56aikygemk3u3ct8.htr"},
    {"ILoveUIHateU - Playboi Carti",											"as1ior5wfsl5v3aty5irp9erf.htr"},
    {"Shoota - Playboi Carti",													"2dopz6zpad8x4nnfehzykp7xt.htr"},
    {"Sky - Playboi Carti",														"0v6bi8huibdlo4sf7cuqpp5c2.htr"},
    {"Location - Playboi Carti",												"c26djwjnm7y86dqnrxstuf88s.htr"},
    {"Vamp Anthem - Playboi Carti",                                             "82qnnpkywtrutm9gzishw0nd4.htr"},
    {"CARNIVAL - Playboi Carti",                                                "1rormu8aothowrf8jpz9vkay6.htr"},
    {"R.I.P - Playboi Carti",                                                   "c6gl9c3ijv5zp0fjhkg0m04i2.htr"},
    {"Fell In Luv - Playboi Carti",                                             "6fsax6p60iisvdudnyjvs4x29.htr"},
    {"New Tank - Playboi Carti",                                                "9xu3lt6vwzqiicis66nlg4mlp.htr"},
    {"Miss The Rage - Playboi Carti",                                           "br9qs4gexeevp4ojw0wrfic8a.htr"},
    {"wokeuplikethis - Playboi Carti",                                          "9nopvojjobz3duwzpzqsr04gh.htr"},
    {"Over - Playboi Carti",                                                    "9vvsn1cuflrtag6acz95v6n67.htr"},
    {"Long Time - Playboi Carti",                                               "0zq9egeeu5l5lqelivo3c6emb.htr"},
    {"Yah Mean - Playboi Carti",                                                "3z9f9pzuu2h1194zwnaf4joo3.htr"},
    {"On That time - Playboi Carti",                                            "c8826h9bpzorzi4jd5x1nufy5.htr"},
    {"Foreign - Playboi Carti",                                                 "7qgnc87rzxaeq4k9v1h5i38gq.htr"},
    {"Skeleton [Leak] - Playboi Carti",                                         "7852c46boxrpvprpynui6smlk.htr"},
    {"Bando [Leak] [Remix] - Playboi Carti",                                    "a5tj7e8x3ejh7qwc72rt4b6y0.htr"},
    {"UrTheMoon (Different Day) - Playboi Carti",                               "djcsxjx6f8kyfbgvj25n4lcfg.htr"},
    {"Kid Cudi (Pissy Pamper) [Leak] - Playboi Carti",                          "78gjivkwfk1ep4k0p8rc3rcpy.htr"},
    {"Stop Breathing - Playboi Carti",                                          "2zcdtsbfdopi20oreuwbnnuez.htr"},
    {"KETAMINE - Playboi Carti",                                                "eg75w85xiim450kbtxr1ipv7f.htr"},
    {"2024 (#IAMLIAR) - Playboi Carti",                                         "f04cf524l3ptyplbvj6hu5p18.htr"},
    {"BACKR00MS - Playboi Carti",                                               "d5ingt9wn7a10wk7ehgpyyisa.htr"},
    {"EVIL J0RDAN - Playboi Carti",                                             "5y8j0bjtn2it6sgxu57q6fc81.htr"},
    {"Made it this far (24 Songs) [Leak] - Playboi Carti",                      "e8c0gyj5i7546h7gi1tpgyqyr.htr"},
    {"Evil J0RDAN (popular intro) [Remix] - Playboi Carti",                     "d0lwzdo9m1fiej3qdb1phm7g0.htr"},
    {"Menage [Leak] - Playboi Carti",                                           "dqn0e1ljt5zrc0ycs15tvbtxk.htr"},
    {"WOK [Leak] - Playboi Carti",												"0xkqh87rt6ejcyy3rhdjzup7v.htr"},
	{"Money v1 (Cheetah) [Mix A] [Leak] - Playboi Carti",						"dbabi24i63vs74l7bscroegd4.htr"},
    {"Money v2 (Cheetah) [Mix B] [Leak] - Playboi Carti",                       "3w2exj5l5wcpbofnk7yc95ire.htr"},
    {"Not Real (Molly) [Leak] - Playboi Carti",                                 "6knfweoi40tavtkvvv2bm92xo.htr"},
    {"Wicked (Killers) [Leak] - Playboi Carti",                                 "9afhd1fhv03l35bw17xc4rlb3.htr"},
    {"I LUV IT - Playboi Carti",                                                "7ijy29f6hlc8f7z3pd5ottfgu.htr"},
    {"Type Shit - Future (ft Playboi Carti)",                                   "d670wod4q54l1zw6tj4snz4zx.htr"},
	{"H00D By Air (Different Day) - Playboi Carti",								"25sh6zgks5iimhwe70ecf3cyo.htr"},
	{"Play This - Playboi Carti",												"85zwc60jdu9wjb5uccszz2was.htr"},
	{"Walk [LQ] - Playboi Carti",												"4yhwa53z7wkhxm5hqprlsx3na.htr"},
	{"Omerta [LQ] - Playboi Carti",												"2wvtjooiaijgtb8ewv9zlo47o.htr"},
	{"Lose You [LQ] - Playboi Carti (ft The Weeknd)",							"ct7duwx9en7edo1l4bgdjnm88.htr"},
	{"Crush [LQ] - Playboi Carti (ft Travis Scott)",							"9rea9r6opoq1zpcizm7x5jkl8.htr"},
	{"Cocaine Nose [LQ] - Playboi Carti",										"96p3xek6iojx4gk3pagtnygpf.htr"},
	{"Blick Sum [Leak] [Mix A] - latto (ft Playboi Carti)",						"7ow614ii2zog1rhqoe58hwloi.htr"},
	{"Cartier [Leak] - Playboi Carti (ft Lil Uzi Vert)",						"9tr2hb0aw3jqd6qtxtfgpbs9c.htr"},
	{"Cash Shit [Leak] - Playboi Carti",										"84kqa0m8m6s1of80a5xuopzbe.htr"},
	{"Dick Pleaser [Remix] [Leak] - Playboi Carti",								"0eiwbb5anflkrb5eexdc9u1eo.htr"},
	{"Fein [OG Mix] - Travis Scott (ft Playboi Carti & Sheck Wes)",				"24das254lpvo13do3qxppb99n.htr"},
	{"00Cactus - Playboi Carti (ft Travis Scott)",								"8pkmuqu1ljxa7ozrmuxpy54e6.htr"},
	{"Over [Tour Mix] - Playboi Carti",											"aep464w5ugk4spc2kl3cl6u1p.htr"},
	{"Solo Dolo pt4  - Playboi Carti (ft Kid Cudi)",							"3rr6weg9eofr7vngr5t0aqw12.htr"},
	{"All Red - Playboi Carti",													"2jhlmyu7fwx54dzuuxjzk2ilw.htr"},

	// IAMUSIC
#endif
	{"[IAMMUSIC] POP OUT - Playboi Carti",													"9a05y7wuv5bi1klqzwoqel9pu.htr"},
	{"[IAMMUSIC] CRUSH - Playboi Carti",													"bpaursitetteime45c8nypcuv.htr"},
	{"[IAMMUSIC] K POP - Playboi Carti",													"ct8bmgwuvsq6ft4n7co336i52.htr"},
	{"[IAMMUSIC] EVIL J0RDAN - Playboi Carti",												"3smdrya1ixvnna7q569hqiue5.htr"},
	{"[IAMMUSIC] MOJO JOJO - Playboi Carti",												"cnb9uewzfcui0ok1ybp35m3zc.htr"},
	{"[IAMMUSIC] PHILLY - Playboi Carti",													"5a6oj669elz9ezcj3e32q011q.htr"},
	{"[IAMMUSIC] RADAR - Playboi Carti",													"d1ythwwv9pwmw2e1ptmfeuf70.htr"},
	{"[IAMMUSIC] RATHER LIE - Playboi Carti",												"4fcmkaqqqxha6al97qs2or2lc.htr"},
	{"[IAMMUSIC] FINE SHYT - Playboi Carti",												"1ljtxfsuqv05o2v7ctaacva0u.htr"},
	{"[IAMMUSIC] BACKD00R - Playboi Carti",													"au0oov4mkn5p9c1h8yjpeafsq.htr"},
	{"[IAMMUSIC] TOXIC - Playboi Carti",													"c4m338hlphzpq3mnghh53ukci.htr"},
	{"[IAMMUSIC] MUNYUN - Playboi Carti",													"8vigoz2k6dqkob9km2qecbqbl.htr"},
	{"[IAMMUSIC] CRANK - Playboi Carti",													"2gcs0dff63qyzib89wm1a6a9i.htr"},
	{"[IAMMUSIC] CHARGE DEM HOES A FEE - Playboi Carti",									"4lzakkchavw940505mwl63e8y.htr"},
	{"[IAMMUSIC] CHARGE DEM HOES A FEE - Playboi Carti",									"4lzakkchavw940505mwl63e8y.htr"},
	{"[IAMMUSIC] GOOD CREDIT - Playboi Carti",												"281601x4um0vl2lcwddaxfixi.htr"},
	{"[IAMMUSIC] I SEEEEEE YOU BABY BOI - Playboi Carti",									"2kjvo28rxta5jle44ztybkb7p.htr"},
	{"[IAMMUSIC] WAKE UP F1LTHY - Playboi Carti",											"70bnn5viog5u75jqdhydw80jm.htr"},
	{"[IAMMUSIC] JUMPIN - Playboi Carti",													"4bf7zlgslc5la3t7ymqo0zw50.htr"},
	{"[IAMMUSIC] TRIM - Playboi Carti",														"9vpj9cy7ubyutw94igdcx47co.htr"},
	{"[IAMMUSIC] COCAINE NOSE - Playboi Carti",												"4qo5uzjttnevh9q2xtzlgymet.htr"},
	{"[IAMMUSIC] WE NEED ALL DA VIBES - Playboi Carti",										"940kqw1b34j5zkg94rtjtym3r.htr"},
	{"[IAMMUSIC] OPM BABI - Playboi Carti",													"8e9gdvusc71j43w777hd2whes.htr"},
	{"[IAMMUSIC] TWIN TRIM - Playboi Carti",												"5jgytnszk32fk0b3zrzonfn29.htr"},
	{"[IAMMUSIC] LIKE WHEEZY - Playboi Carti",												"ce8usg7vjigg7ko0yie2ybxnz.htr"},
	{"[IAMMUSIC] DIS 1 GOT IT - Playboi Carti",												"0wcktz8k8ocum5lg3zkzx9xxj.htr"},
	{"[IAMMUSIC] WALK - Playboi Carti",														"dagmvnrxgfae2ogw54vcqkq44.htr"},
	{"[IAMMUSIC] HBA - Playboi Carti",														"19lksj2b7e4tu6506yhhmv5at.htr"},
	{"[IAMMUSIC] OVERLY - Playboi Carti",													"8ab9gt0ayzrhhd90dmvmg8o5k.htr"},
	{"[IAMMUSIC] SOUTH ATLANTA BABY - Playboi Carti",										"4umqj0m5v9hjgwiiul48fqomo.htr"},
	{"[IAMMUSIC] DIFFERENT DAY - Playboi Carti",											"214tgesk63o68w3rr5f9qmtih.htr"},
	{"[IAMMUSIC] 2024 - Playboi Carti",														"0fto4i1l8c0c96wxf1lhv1wml.htr"},
	{"[IAMMUSIC] BACKR00MS - Playboi Carti",												"9yoh5ca04c7d6jhncy92hzqmt.htr"},
	{"[IAMMUSIC] FOMDJ - Playboi Carti",													"4aghm49zeuzv27c5046hrsbhu.htr"},
	
	{"[ROADTOMUSIC] PROBLEM CHILD [LEAK] - Playboi Carti (ft Travis Scott)",				"7fjiu4neq77ns2f1qs62m8qs8.htr"},
	{"[ROADTOMUSIC] VETEMENTS JEANS [LEAK] - Playboi Carti (ft Lil Uzi Vert)",			"2g7lbgilek19ut0ihnxosm1w9.htr"},
	{"[ROADTOMUSIC] GETTNG MONEY [LEAK] - Playboi Carti",								"9iyrk1izemosjr2sf1cv7lh12.htr"},
	{"[ROADTOMUSIC] INTO YOU [LEAK] - Playboi Carti (ft Cash Cobain)",					"bn5wxuqebuncr0ln37bfab1h0.htr"},
	{"[ROADTOMUSIC] KILLERS [LEAK] - Playboi Carti",										"66ux8an677y7anblh21wlbw24.htr"},
	{"[ROADTOMUSIC] HOLLA [LEAK] - Playboi Carti",										"5jxhuskj6eg23133zx01ng7yn.htr"},

	{"[ROADTOMUSIC] DOCTOR [LEAK] - Playboi Carti",										"83q59k6x6hkuqfbnxl1nlvryo.htr"},
	{"[ROADTOMUSIC] SURVIVOR [LEAK] - Playboi Carti",									"341xofplfa7kug98z2mjifbe9.htr"},
	{"[ROADTOMUSIC] FAKE LOVE [LEAK] - Playboi Carti",									"6tc996omgfcwhercst07qml4z.htr"},

	{"TWO OUT [LEAK] - Playboi Carti (ft Lil Uzi Vert)",									"60vlm1dwx6gm86acd82fnxa6b.htr"},
	{"MEDUSA [LEAK] - Playboi Carti",													"9zgfq7ouvc1hqzbi138zrz09v.htr"},
	
	{"CAN U BE [LEAK] - Kanye West (ft Travis Scott)",									"8mya6tcznxn382rmbkg09gyd7.htr"},
	
	{"Reality Surf - Bladee",															"a0gfydzzi8w72255ti7e2on4a.htr"},
	{"Walk in the park - Feng",															"9lg9s2e97cgqzxekv4b2zm4hm.htr"},
       {"Fake ID - kizaru",																"08koj6tkebc7md5g1mn7dfpea.htr"},
	
	// Yeat
	{"Codiene (Vibing) [Leak] - Yeat",											"8ky7q0ea4wbeem0y8qhu64uvi.htr"},
	{"Go Again [OG Mix] - Yeat",													"4ct15znekc1g4xjynd0uyvd6z.htr"},
	{"Marching [OG Mix] - Yeat",													"eufs7kruyi9q0nqkdrz5m7yfb.htr"},
	{"War 1 - Yeat",																"enldl5mu7a51isz9fad3pi325.htr"},
	{"IDGAF - Drake (ft Yeat)",													"e5r9hq1mzp3pxlrtbb7rzac1r.htr"},

		// 2Alive
	{"[2Alive] poppin - Yeat",													"84fuguqzxllepl2ffp1n3zhog.htr"},
	{"[2Alive] Nvr again - Yeat",												"bcu56fm709jhhzzyp33dyb8rs.htr"},
	{"[2Alive] Rackz got me (ft Gunna) - Yeat",									"763vfx2gq1tx12hkkroe7uxgf.htr"},
	{"[2Alive] Double - Yeat",													"5iw8h8smanbnhunyus64jjpla.htr"},
	{"[2Alive] On tha line - Yeat",												"6ps0xtevki2m96dhs4uaskzc0.htr"},
	{"[2Alive] Jus better - Yeat",												"egnsovfhepndep77ajbgobtl3.htr"},
	{"[2Alive] Taliban - Yeat",													"827p1lldt4xeycsd852gejvvf.htr"},
	{"[2Alive] Big tonka (ft Lil Uzi Vert) - Yeat",								"2gwrc69bmmwciowqit97ovegy.htr"},
	{"[2Alive] Kant relax - Yeat",												"0gqcpio8paa3fd9cw0yzdvqtq.htr"},
	{"[2Alive] Hater - Yeat",													"ebf9vdz4ttyxraj3fl3x0u3t3.htr"},
	
		// Lyfe
	{"[Lyfe] Flawless (ft Lil Uzi Vert) - Yeat",								"edm3jl4xpouuufqnscgom0gn6.htr"},
	{"[Lyfe] Up off X - Yeat",													"9rpjcf4itmfs6x7rgno9mc8ht.htr"},
	{"[Lyfe] Out the way - Yeat",												"0ku8gidan17ps6m84aje89hxj.htr"},
	{"[Lyfe] Wat it feel lyke - Yeat",											"9ny9mfmy01q3vggdapy7s1vs2.htr"},
	{"[Lyfe] Got it all - Yeat",												"9ao4y4yk9gf505t2p40bllsfj.htr"},
	{"[Lyfe] Can't stop it - Yeat",												"7ence5tqgetzz5g88xfin4cd9.htr"},
	{"[Lyfe] Krank - Yeat",														"04ga8jk5nf7px3181mub1zqic.htr"},
	{"[Lyfe] Talk - Yeat",														"d43p9wa0shp4xnfzel5rt2cwb.htr"},
	{"[Lyfe] Come on - Yeat",													"7cxkv23nizkhtfsigoihjehwn.htr"},
	{"[Lyfe] System - Yeat",													"al5opvrg7ndraadoux5iwkb12.htr"},
	{"[Lyfe] Holy 1 - Yeat",													"8funwkf04uzdx3l9e60t0gy09.htr"},
	{"[Lyfe] Killin em - Yeat",													"93v7tzhf6bx86s6c0m9zjn07q.htr"},
	
		// AfterLyfe
	{"[AfterLyfe] No more talk - Yeat",											"0omual0be2otg7v3x651d2oi2.htr"},
	{"[AfterLyfe] Shmunk (ft NBA YoungBoy) - Yeat",								"8i409exmm16qm6p9z48ec5oy8.htr"},
	{"[AfterLyfe] Bettr 0ff - Yeat",											"1yya1rjg8uackk6wu0aaomesg.htr"},
	{"[AfterLyfe] Rav3 p4rty - Yeat",											"dd69qizxyverdonrmyl9h59is.htr"},
	{"[AfterLyfe] Nun id change - Yeat",										"8kj80qhit14zya3f0heidwcq6.htr"},
	{"[AfterLyfe] Woa....! - Yeat",												"6kxmudd2fy0mqzidkg6woxlyj.htr"},
	{"[AfterLyfe] Now - Yeat",													"a2glr7v2z4048rvdjcpt5aa4p.htr"},
	{"[AfterLyfe] Slamm - Yeat",												"6b34phr2ls6qbfq5c1g3uzw2h.htr"},
	{"[AfterLyfe] 7 nightz - Yeat",												"0r1m7nb3g038c2nwa6d4fxhcl.htr"},
	{"[AfterLyfe] Mean feen - Yeat",											"4vlvx45qofhyj9h4mg6fsp94h.htr"},
	{"[AfterLyfe] How it go - Yeat",											"104qfoqxxdukm1f1j867hurca.htr"},
	{"[AfterLyfe] Sum 2 do - Yeat",												"5urr3s4h6oulb424b78r7njte.htr"},
	{"[AfterLyfe] Back up - Yeat",												"751qsrha6bfa748z3dej4r4uv.htr"},
	{"[AfterLyfe] Split - Yeat",												"cdzkw7nxi33cwsm85txm05aou.htr"},
	{"[AfterLyfe] Bad bend / DeMON - Yeat",										"9ptee1me4zlrm6rcgy2b6le14.htr"},
	{"[AfterLyfe] Heavyweight - Yeat",											"euujhnp8lw8v4xea2i5ekvghn.htr"},
	{"[AfterLyfe] Watch - Yeat",												"38ph91qsfyee1xthxg066kyjr.htr"},
	{"[AfterLyfe] Shhhh - Yeat",												"5vb7d0p4gv5ci2qfx5mr2ecv5.htr"},
	{"[AfterLyfe] Back home - Yeat",											"bg4wt0u81g4rkjjwqse4f3zwy.htr"},
	{"[AfterLyfe] Type money - Yeat",											"dt5qjd8gribr1dut776577eoo.htr"},
	{"[AfterLyfe] Demon tied - Yeat",											"3pbs65yw6zel5tjsdygxps6u6.htr"},
	{"[AfterLyfe] Myself - Yeat",												"3ky2s3znmc35akryw25l1tww9.htr"},
	
		// 2093
	{"[2093] Pshyco CEO - Yeat",												"53fet783mc0jrcppd9tkuz12i.htr"},
	{"[2093] Power Trip - Yeat",												"8hyqacc8bxg23zmcs8nh2ltlz.htr"},
	{"[2093] Breathe - Yeat",													"8uybfu3l0ohez350drem95li7.htr"},
	{"[2093] More - Yeat",														"6goru6e9ozdrixzmgi94or285.htr"},
	{"[2093] Bought The Earth - Yeat",											"ctm336robhi3rn4289ctwm0a4.htr"},
	{"[2093] U Should Know - Yeat",												"625gq0x6zjnbfageq566exlg3.htr"},
	{"[2093] Lyfestyle (ft. Lil Wayne) - Yeat",									"ebykc5l0hihvino75lxibmsmu.htr"},
	{"[2093] ILUV - Yeat",														"ejowzxbd1evy38lnnfi920tna.htr"},
	{"[2093] Tell me - Yeat",													"doutxlzey6cxhminic6cd9u8b.htr"},
	{"[2093] Shade - Yeat",														"38ngk995zzv88auvo0fuhprzi.htr"},
	{"[2093] Keep Pushin - Yeat",												"1dx3u51oom3nnggryycrk6ryk.htr"},
	{"[2093] Riot & Set it off - Yeat",											"1mwfx0v3vbl42jsnuvdro5vaf.htr"},
	{"[2093] Team ceo - Yeat",													"ar5qeq4h0r37kw5ms1fd68kx0.htr"},
	{"[2093] 2093 - Yeat",														"89g5darmyna2j9uobrefjme3x.htr"},
	{"[2093] Stand On It (ft. Future) - Yeat",									"2hgqj34d4pqp2w6ek5zwuom8p.htr"},
	{"[2093] Familia - Yeat",													"1wicfd6gi6pwga3u2217xste2.htr"},
	{"[2093] Mr. Inbetweenit - Yeat",											"16dgg90o5lz59r46ienqie2ux.htr"},
	{"[2093] Pshycocaine - Yeat",												"1su8mqfks4ed5x2xytbjnniuc.htr"},
	{"[2093] Run They Mouth - Yeat",											"30kfc9fwosaaa49dehvcc87yo.htr"},
	{"[2093] Nothing Change - Yeat",											"8eke1mteeur66vxeyvo6x8qj6.htr"},
	{"[2093] If We Being Real - Yeat",											"6p1d6r5yno444n37rqaxj5nae.htr"},
	{"[2093] 1093 - Yeat",														"0inunsn02nbtz6oq1eeprv727.htr"},

		// LyfeStyle
	{"[LyfeStyle] GEEK TIME - Yeat",											"dm8t80mqmxcrbdrvr5ibs5t9m.htr"},
	{"[LyfeStyle] STFU - Yeat",													"2rhs2z9wtt45t5t99zjqkfnjf.htr"},
	{"[LyfeStyle] THEY TELL ME - Yeat",											"704k9zuu3jtn11atppjeczif6.htr"},
	{"[LyfeStyle] HEARD OF ME - Yeat",											"enj7fia43c7jyytg6qmvdvkm5.htr"},
	{"[LyfeStyle] SPEEDBALL - Yeat",											"b9x2y2wk8vprk9o53s1j5d4bo.htr"},
	{"[LyfeStyle] U DONT KNOW LYFE - Yeat",										"2e3oowwt8avbno2po54mbu5dp.htr"},
	{"[LyfeStyle] ORCHESTRATE - Yeat",											"3sc9a4hpego1mpwtat2j2ztco.htr"},
	{"[LyfeStyle] BE QUIET - Yeat",												"2egtxrav5vf6vze27wqqdlqio.htr"},
	{"[LyfeStyle] THE COSTES - Yeat",											"24u68fya6bzrxs72nti23cyi6.htr"},
	{"[LyfeStyle] GO2WORK - Yeat",												"2bxsfxlrg1d3zfyqmqgqu05j8.htr"},
	{"[LyfeStyle] GONE 4 A MIN - Yeat",											"6rqcsgh0ets4lub7cutv6l292.htr"},
	{"[LyfeStyle] FOREVER AGAIN - Yeat",										"76pyfzkpxrd4j5d9vyqjde4mf.htr"},
	{"[LyfeStyle] ON 1 - Yeat",													"2hsyaqdaebv129pm595wr6f3h.htr"},
	{"[LyfeStyle] FLYTROOP - Yeat",												"8lkd9g21mud149eu42rq7o4bk.htr"},
	{"[LyfeStyle] ELIMINATE - Yeat",											"cww8sc6jaw2g2q3gk772htmxu.htr"},
	{"[LyfeStyle] LYING 5 FUN - Yeat",											"2ukhtw80gqgpzwxhfr39nvb89.htr"},
	{"[LyfeStyle] NEW HIGH - Yeat",												"epvdwta7efms03svonzoyiwub.htr"},
	{"[LyfeStyle] SO WHAT - Yeat",												"b4zird8sud7tfx9e58a0rz2g6.htr"},
	{"[LyfeStyle] LYFESTYLE - Yeat",											"esrpc9uimyqxf7qjbin17ooxe.htr"},
	{"[LyfeStyle] GOD TALKIN SHHH - Yeat",										"3kaa5yiukcl2sruy496il1d8w.htr"},
	{"[LyfeStyle] LYFE PARTY - Yeat",											"216u1nhsytkmwdxo6lt8m8a8k.htr"},
	{"[LyfeStyle] FATE - Yeat",													"amobbdlp8s580uttfwbshq1ri.htr"},
	
    // Uzi
	{"Blow Da Whistle [Leak] - Lil Uzi Vert",									"8ndhqu88dmoczvc4ua2g4gcpi.htr"},
	{"Balenciaga [Leak] - Lil Uzi Vert",										"bkvgx6ndifrfyejen67104htg.htr"},
    {"20 min - Lil Uzi Vert",													"8i5np91f3qkn2uu4tuke6wpp3.htr"},
    {"XO Tour Lif3 - Lil Uzi Vert",                                             "96ie3qjeop4xytj6a4ciibu2y.htr"},
    {"The Way Life Goes - Lil Uzi Vert",                                        "6rwl2phym1yy983qqz6qli7e9.htr"},
    {"Just Wanna Rock [Remix] - Lil Uzi Vert",                                  "0c4m62gkjo97iwandahw7av2g.htr"},
    {"Money Longer - Lil Uzi Vert",                                             "dg5vumxomenxmnvoe5va3atl4.htr"},
    {"Everybody - Lil Uzi Vert",                                                "2npucvueu7o9ruaamxobyu4wy.htr"},
    {"Flooded The Face - Lil Uzi Vert",                                         "eloympwsmd0oqx3ftl7370pdt.htr"},
    {"Neon Guts - Lil Uzi Vert",                                                "8ea2de775mkeyqyv4e22vfzgo.htr"},
    {"Sauce It Up - Lil Uzi Vert",                                              "ctqjwwq9cp52nhdhlh0ive06x.htr"},
    {"You Was Right - Lil Uzi Vert",                                            "alpwfn5zeic0niwhwr64uoktd.htr"},
    {"Myron - Lil Uzi Vert",                                                    "bvbnerblvvzn4lw56l57c464l.htr"},
    {"Homecoming - Lil Uzi Vert",                                               "f26f6wmqk5696paaohig4tajc.htr"},
    {"Do What I Want - Lil Uzi Vert",                                           "di0j84uedoezb1th8immcvmij.htr"},
    {"Erase your social - Lil Uzi Vert",                                        "3qvcum1t608hcwca0c1b98kz9.htr"},
    {"Two - Lil Uzi Vert",                                                      "en7rhohqympbldpjn9imxo06j.htr"},

    // 50 cent
    {"In Da Club - 50 cent",													"be71g2eb2izm81nk9uj62238f.htr"},
    {"Many Men - 50 cent",														"5w9jl0squfidmwyn55491m4h5.htr"},

    // polo g
    {"RAPSTAR - Polo G",														"3pgn154788tch5b2z1mqd40kj.htr"},
    {"Go Stupid - Polo G",														"0zf4ip1vvpr1m9x22znfo05r0.htr"},
    {"Flex - Polo G",															"1qxva5yavsazjn6d0416v7ujl.htr"},

    // von
    {"Took Her To The O - King Von",											"0x2s9lzaib7dnlkic1t3gseb5.htr"},

    // kanye
    {"Cant Tell Me Nothing - Kanye",											"amo3klll7taxe9so8yjpt4pww.htr"},
	{"Melrose [Mix A] - Kanye (ft Playboi Carti)",								"3i6y7l6tj9r6gnv6q1xkhhfz4.htr"},
	{"Fuck Sumn [Remix] - Kanye (ft Playboi Carti & Quavo)",					"9q33v8u0ynjm6csbeyz31cmlm.htr"},

	// Ken Carson
	{"Singapore55555 [Leak] - Ken Carson (ft Playboi Carti)",					"e9ac4ybxvigklxsr0qa9usdiu.htr"},
	{"Me N My Kup - Ken Carson",												"1w1ns6c2nczrorqhc4o5cp9ii.htr"},
	{"ss - Ken Carson",															"3lvush574aixngp3ky9dw2ya4.htr"},
	{"Overseas - Ken Carson",													"dm7fklxpbzu17xqgqs95w9m1o.htr"},
	{"[MORECHAOS] VMP EARRAPE [LEAK]",											"en4acnlkoy823r7q03pgvrhja.htr"},
	{"[MORECHAOS] VMP [LEAK]",													"0dz9h1923t70d0xwwq429wht7.htr"},
	{"[MORECHAOS] LiveLeak [LEAK]",												"bj02kksm4tiujgh5k1cu3qq6q.htr"},
	{"[MORECHAOS] Lord of Chaos [LEAK]",										"byp0dfzp7vvt8to28ur3q2t6i.htr"},
	{"[MORECHAOS] Pyscho [LEAK]",												"0b4bjdj0n3kinvf8yk8mb093z.htr"},
	{"[MORECHAOS] Thx [LEAK]",													"e0ad3ykie3ia09ay7l4umyhsp.htr"},
	
	// widwxst
	{"223s - Midwxst",															"9d5kyj2t50xbm2elnzdorid46.htr"},
	
	// russians
	{"Sigma Boy - Maria",														"c5bwlq6yq88sqipvjmydoslea.htr"},
	{"Balance - Instasamka",													"ahoy726s75t33tyzbv5o2qw50.htr"},
	{"Jara (Heat) - Instasamka",												"88zktvb83hd9gus892nd2tqo1.htr"},
	{"Your Eyes - Leytink",														"c0jg6u5rhqbjflde9aoubo0s0.htr"},

	// babytron
	{"#Certified - Babytron",													"a0hpcdd8upk59ynlfcqndc65x.htr"},
	{"Stutter Flow - Babytron",													"47tubtwg4pgi3ag3ecscbqlv5.htr"},
	{"Streetball [remix] - Babytron",											"6texo3ngkn0df299wp7p8yqca.htr"},

	// tiktoks
	{"Jewish - TikTok",															"dgr0mlpacdxoaoe7ve59vnb6m.htr"},
	{"Layer Two George Droyd - TikTok",											"5s68osetcwu0k0le5ckw432vw.htr"},
	{"Nigga Chain - TikTok",													"36va7p5xwaftdedbdjlnx9762.htr"},
	{"Diddytron - TikTok",														"8cr2ggzmnflsvt9n82nj99xsz.htr"},
	{"George Droyd Comercial - TikTok",											"cz0x31mmexucxwnz0c0i1vgv7.htr"},
	{"Fent Reactor - TikTok",													"aty35vibvc6nhenyv4y5vpwj9.htr"},
	{"George Droyd Old Heads - TikTok",											"auhtbgo0rn8c9vf7nfihfafun.htr"},
	{"China Rap - TikTok",														"7dl7l6qv2sr58ncgbdi4b2emm.htr"},
	{"Low Taper Fade Locked In - TikTok",										"86y7hy0yuojq8wjwxc9a6ovk9.htr"},
	{"Low Taper Fade - TikTok",													"8kqjge39z7bfg3489sx3oo2qz.htr"},
	{"KFC EARRAPE - TikTok",													"e57vi8mur51a30f8im4dx97i0.htr"},
	{"KFC - TikTok",															"70jkelx0feviuwqmi8grdrqol.htr"},

	// uploaded by Energy
	{"Blueberry Gaygo - Energy",												"5fogedza8mnkilxezy7b5fg9m.htr"},
	{"Glow Up Sketchers [Gay Remix] - Energy",									"aa62ontfz40oi9oisgkecwydk.htr"},
	{"Take Back The Night [Cpt. Sparkles Remix] - Energy",						"8pu8pqst4vem4hzqapitp3f7m.htr"},
	{"NCS Banger - Energy",														"e2nmp3i3bh2gukuwijanzbdm0.htr"},
	{"EAR RAPE - Energy",														"dvijypsyf6dwi7ng1woc1iwbq.htr"},

    // Nicki Minaj
    {"FTCU [YN Remix] - Nicki Minaj",          "avv7u9sqvyef5smyj7abkugiy.htr"},
    {"FTCU - Nicki Minaj",                     "3j8no1r20iba2mfcwwe7w6zfy.htr"},

    // King Von
    {"Took Her To The O - King Von",           "04ym6vinflm8zrzx9siacocr2.htr"},
    {"Crazy Story, pt 3 - King Von",           "dbh0laft71kfzzhuijy3mnj4g.htr"},
    {"Crazy Story - King Von",                 "b4fkkpgup33rq3cfapnr2brnc.htr"},
    {"Armed and Dangerous - King Von",         "6x1m96ry1oqbrbs0d89k0lvjq.htr"},

    // Travis Scott
    {"Goosebumps - Travis Scott",              "dodjk2tz0ezmxw9dchjfdyra6.htr"},
    {"Sicko Mode - Travis Scott",              "7lcuan8bwaks67ku1pvzjebnj.htr"},
    {"Highest In The Room - Travis Scott",     "cri9ojz7y6t9s0faykueczsva.htr"},
    {"Butterfly Effect - Travis Scott",        "cs5gcz9s9103e2uzwpgvm50zf.htr"},
    {"ZEZE - Travis Scott",                   "09o1cgd815xefl2hgai1r8u13.htr"},
    {"The Scotts - Travis Scott",              "17cit6i0roaygk69kqmnxsqv6.htr"},
    {"Star Gazing - Travis Scott",             "1eui5pviu50xd4h890b7b1yoo.htr"},
    {"Fair Trade - Travis Scott",              "1w7d1qeyxezi1i8xkxediy4gb.htr"},

    // NBA Youngboy
    {"Bandit - NBA Youngboy (ft Juice WRLD)",  "e1la43wlxczu1y39zm6i0olwh.htr"},
    {"Right Foot Creep - NBA Youngboy",        "etiu33xfazih45pzmigg2nlxa.htr"},
    {"Need It - NBA Youngboy",                 "0pd4t7wzleykg3ab8wl0dinrn.htr"},
    {"Tragic - NBA Youngboy",                  "c06jsyv4nb8cqjto0hc105r57.htr"},
    {"NBA Youngboat - NBA Youngboy",           "enx9kps6ervpeec0ekq1me5kh.htr"},
    {"Make No Sense - NBA Youngboy",           "3hgs6gbe7wml6x1maurvgeayw.htr"},
    {"Make No Sense - NBA Youngboy",	       "3hgs6gbe7wml6x1maurvgeayw.htr"},
    {"Ryte Night - NBA Youngboy",			   "6cpb494m17k2tv5xmu6rkqshu.htr"},

    // 2Pac
    {"California Love - 2Pac",                 "csexn7dfjjy1m1gr6s2q2c7nv.htr"},

    {"California Love - 2Pac",				   "csexn7dfjjy1m1gr6s2q2c7nv.htr"},

    // NLE Shotta
    {"Shotta Flow - NLE Shotta",              "bkq7qxmcn0qj20zjtonxy3hal.htr"},
    {"Camelot - NLE Shotta",                  "4yh20mh7bjheazdcsglp38538.htr"},
    {"CAPO - NLE Shotta",                     "2ayrla436gj802mxq2t7z6svi.htr"},
    {"Do It Again - NLE Shotta",              "9p5yqpr2m4bta8utydn9u1293.htr"},

    // Michael Jackson
    {"Billie Jean - Michael Jackson",         "aw537xfhb1xk6v0aebkhcqdx2.htr"},
    {"Beat It - Michael Jackson",             "80svp17jgpnjuc86bkd4j1vnw.htr"},
    {"Smooth Criminal - Michael Jackson",     "4y6xs9lot1hhgpps3p5kwkicu.htr"},

    // Lil Tecca
    {"Ransom - Lil Tecca",                    "0wmkbu9nmkihqvh2aevikz1ox.htr"},
    {"500lbs - Lil Tecca",                    "91gv2mafht6t16h9sb5f7wopw.htr"},
    {"Our Time - Lil Tecca",                  "0sn4qgxbe62aoo1fyg9ckeh4r.htr"},
    {"Lot of Me - Lil Tecca",                 "dmbd8m4j6zgt4umahkzn4d6pk.htr"},
	
	// misc
	{"712pm - Future",															"07waw21ovydufr7rtbtaykyub.htr"},
	{"223s - YNW Melly",														"eazwn17frnt53l55avjvw4zkt.htr"},
	{"Lollipop (Candy Man) [Nightcore] - Aqua",									"d9rgdlxhn1gq4kwts94zc20ra.htr"},
	{"Jamrock - Damian Marley",													"4v27grkovh08p8t8p34lj97kc.htr"},
	{"679 - Fetty Wap (ft Remy Boyz)",											"6ceq614d78ws1ilk2o23he5bi.htr"},
	{"Again - Fetty Wap",														"ebeppl9scj91y556p052em9wa.htr"},
	{"Trap Queen - Fetty Wap",													"c12iyw3dtuqro7pcew72edznr.htr"},
};

const char* prefabList[] = {
	"(FullBodyPuppetProp)",
	"[RootBeer_HackolaConsumableTool]",
	"[RootBeer_PixelPop_ConsumableTool]",
	"[CakePops_CandylandConsumableTool]",
	"[Popcorn_MonsterMunchies_ConsumableTool]",
	"[Microphone_Conference]",
	"[Sandbox_Mirror]",
	"[AudioEffectZone]",
	"[Consumables_Sparkler]",
	"[Consumables_Sparkler]",
	"[Consumables_Donut_BostonCreme]",
	"(HolotarProjector_CV1)",
	"(HolotarProjector_CV2)",
	"[ArenaManager]",
	"[Arena_AutomaticGun]",
	"[Arena_EMP]",
	"[Arena_Grenade]",
	"[Arena_Pistol]",
	"[Arena_PowerWeapon_BeamGun]",
	"[Arena_RailGun]",
	"[Arena_RocketLauncher]",
	"[Arena_Shotgun]",
	"[Arrow]",
	"[Basketball]",
	"[BattleRoyaleManager]",
	"[BowlingManager]",
	"[Bucket]",
	"[CharadesManager]",
	"[CharadesPen]",
	"[Charades_Stage]",
	"[Crossbow]",
	"[Crossbow_Hunter]",
	"[DiscGolfManager]",
	"[DodgeballManager]",
	"[ElectricalPole_Sandbox]",
	"[FlagAndGoal]",
	"[Giftbox]",
	"[Glider]",
	"[Grenade]",
	"[IBeam_10M_Sandbox]",
	"[Longbow]",
	"[LootChest]",
	"[LootChest_SciFi]",
	"[LootChest_Stuntrunner]",
	"[LootChest_Stuntrunner_Store_Smaller]",
	"[MakerPen]",
	"[MakerPen_Giftbox]",
	"[MicrophoneManager]",
	"[Microphone]",
	"[MiniLootChest_SciFi]",
	"[OrientationManager]",
	"[PaddleballBall]",
	"[PaddleballManager]",
	"[PaintballAssaultRifle]",
	"[PaintballGrenadeLauncher]",
	"[PaintballGun]",
	"[PaintballManager]",
	"[PaintballRifleScoped]",
	"[PaintballShield]",
	"[PaintballShotgun]",
	"[Paintball_PaintThrower]",
	"[PingpongBall]",
	"[PoolCue]",
	"[PoolTable]",
	"[ProximityMine]",
	"[QuestMeatSword]",
	"[QuestShield]",
	"[QuestSword]",
	"[Quest_Boulder]",
	"[Quest_Dracula1_1H-Crossbow]",
	"[Quest_Dracula1_BasicBoneMeleeEnemy]",
	"[Quest_Dracula1_BasicChargingWolfEnemy]",
	"[Quest_Dracula1_BasicLungingBatEnemy]",
	"[Quest_Dracula1_BasicRangedBatEnemy]",
	"[Quest_Dracula1_Bat_Plushy]",
	"[Quest_Dracula1_BlunderBuss]",
	"[Quest_Dracula1_BossBatDecoyEnemy]",
	"[Quest_Dracula1_ChestCoins_Large]",
	"[Quest_Dracula1_ChestCoins_Medium]",
	"[Quest_Dracula1_ChestCoins_Small]",
	"[Quest_Dracula1_CollectablePumpkin_Small]",
	"[Quest_Dracula1_Collectable_Large]",
	"[Quest_Dracula1_Collectable_Small]",
	"[Quest_Dracula1_Collectable_Wall]",
	"[Quest_Dracula1_Crossbow_Hunter]",
	"[Quest_Dracula1_DraculaBossBat]",
	"[Quest_Dracula1_DraculaBoss]",
	"[Quest_Dracula1_Flintlock]",
	"[Quest_Dracula1_Ground_Bone_ThrownEnemy]",
	"[Quest_Dracula1_Ground_MusketEnemy]",
	"[Quest_Dracula1_LootChest]",
	"[Quest_Dracula1_Manager]",
	"[Quest_Dracula1_MiniBossBoneMeleeEnemy]",
	"[Quest_Dracula1_MiniBossCoins_Bat]",
	"[Quest_Dracula1_MiniBossCoins_BoneMelee]",
	"[Quest_Dracula1_MiniBossCoins_BoneThrower]",
	"[Quest_Dracula1_MiniBossCoins_Musket]",
	"[Quest_Dracula1_MiniBossCoins_Wolf]",
	"[Quest_Dracula1_MiniBossGroundBoneThrownEnemy]",
	"[Quest_Dracula1_MiniBossGround_Musket]",
	"[Quest_Dracula1_MiniBossLungingWolfEnemy]",
	"[Quest_Dracula1_MiniBossRangedBatEnemy]",
	"[Quest_Dracula1_MiniBossSkeletonBone]",
	"[Quest_Dracula1_PitchFork]",
	"[Quest_Dracula1_Rake]",
	"[Quest_Dracula1_Rope]",
	"[Quest_Dracula1_Shovel]",
	"[Quest_Dracula1_SkeletonBone]",
	"[Quest_Dracula1_StoreLootChest]",
	"[Quest_Goblin1_Manager]",
	"[Quest_Goblin2_Manager]",
	"[Quest_Goblin_BasicFlyingRangedEnemy]",
	"[Quest_Goblin_BasicGroundMeleeEnemy]",
	"[Quest_Goblin_BasicGroundMeleeEnemy_Pike]",
	"[Quest_Goblin_BasicGroundRangedEnemy]",
	"[Quest_Goblin_BogMonster]",
	"[Quest_Goblin_BogMonster_Tentacle]",
	"[Quest_Goblin_EliteFlyingRangedEnemy]",
	"[Quest_Goblin_EliteGroundMeleeEnemy]",
	"[Quest_Goblin_FirePotion]",
	"[Quest_Goblin_FirePowerup]",
	"[Quest_Goblin_KnightChargeEnemy]",
	"[Quest_Goblin_KnightSpinEnemy]",
	"[Quest_Goblin_RotatingBossEnemy]",
	"[Quest_Goblin_VolleyRangedEnemy]",
	"[Quest_Goblin_Wand]",
	"[Quest_Goblin_WitchBoss]",
	"[Quest_Pirate1_BarStool]",
	"[Quest_Pirate1_BeerBottle]",
	"[Quest_Pirate1_BreakableFish]",
	"[Quest_Pirate1_CoconutBomb]",
	"[Quest_Pirate1_CoinStack_Small]",
	"[Quest_Pirate1_Cutlass]",
	"[Quest_Pirate1_Flintlock]",
	"[Quest_Pirate1_FryingPan]",
	"[Quest_Pirate1_Gibbet]",
	"[Quest_Pirate1_LootChest]",
	"[Quest_Pirate1_LostLoot]",
	"[Quest_Pirate1_Manager]",
	"[Quest_Pirate1_Mug]",
	"[Quest_Pirate1_Oar]",
	"[Quest_Pirate1_Plate]",
	"[Quest_Pirate1_PushBroom]",
	"[Quest_Pirate1_RumJug]",
	"[Quest_Pirate1_StoreLootChest]",
	"[Quest_Pirate1_Torch]",
	"[Quest_Pirate_BasicGroundMeleeEnemy]",
	"[Quest_Pirate_BossEnemy]",
	"[Quest_Pirate_CannoneerEnemy]",
	"[Quest_Pirate_Ground_Bottle_ThrownEnemy]",
	"[Quest_Pirate_Ground_Explosive_ThrownEnemy]",
	"[Quest_Pirate_Ground_RangedEnemy]",
	"[Quest_SciFi1_Manager]",
	"[Quest_SciFi_AutomaticGun]",
	"[Quest_SciFi_BasicFlyingRangedEnemy]",
	"[Quest_SciFi_BasicGroundRangedEnemy]",
	"[Quest_SciFi_EliteFlyingRangedEnemy]",
	"[Quest_SciFi_EliteGroundRangedEnemy]",
	"[Quest_Scifi_JumbotronBossEnemy]",
	"[Quest_SciFi_KnightAssassinEnemy]",
	"[Quest_SciFi_Pistol]",
	"[Quest_SciFi_RailGun]",
	"[Quest_SciFi_Shotgun]",
	"[Quest_SciFi_TinyGroundExplosiveEnemy]",
	"[Quest_Witch_Projectile]",
	"[RecRallyManager]",
	"[Sandbox_CodeOfConduct_Poster]",
	"[Sandbox_CouchChair]",
	"[Sandbox_Friendotron]",
	"[Sandbox_Lockers]",
	"[Sandbox_SnowballPile]",
	"[SciFi_Grenade]",
	"[SoccerManager]",
	"[SoccerPowerup_Star]",
	"[Soccer_SpeedPowerup]",
	"[SoloCup]",
	"[Standee_Bear01]",
	"[StNMonsterCostumeDummy]",
	"[StuntRunner_BoostManager]",
	"[StuntRunner_Manager]",
	"[StuntRunner_Wall_Long]",
	"[Trophy_Oscar]",
	"[Vehicle_50sCar]",
	"[Vehicle_RallyBuggy]",
	"[Vehicle_Truck]",
	"[Vehicle_Wolf]",
	"[VendingMachine]",
	"[Whip]"
};