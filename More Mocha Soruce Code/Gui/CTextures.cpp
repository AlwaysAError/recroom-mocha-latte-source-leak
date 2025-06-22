#include "CTextures.h"

#include "../Resources/Textures/image_api_filled.h"
#include "../Resources/Textures/image_api_outlines.h"
#include "../Resources/Textures/image_gear_filled.h"
#include "../Resources/Textures/image_gear_outlines.h"
#include "../Resources/Textures/image_items_outlines.h"
#include "../Resources/Textures/image_items_filled.h"
#include "../Resources/Textures/image_list.h"
#include "../Resources/Textures/image_medkit_filled.h"
#include "../Resources/Textures/image_medkit_outlines.h"
#include "../Resources/Textures/image_modules_filled.h"
#include "../Resources/Textures/image_modules_outlines.h"
#include "../Resources/Textures/image_tools_filled.h"
#include "../Resources/Textures/image_tools_outlines.h"
#include "../Resources/Textures/image_ui_filled.h"
#include "../Resources/Textures/image_ui_outlines.h"
#include "../Resources/Textures/image_users_filled.h"
#include "../Resources/Textures/image_users_outlines.h"
#include "../Resources/Textures/image_warn_filled.h"
#include "../Resources/Textures/image_warn_outlines.h"
#include "../Resources/Textures/image_coffee.h"
#include "../Resources/Textures/image_crown.h"
#include "../Resources/Textures/image_explosion.h"
#include "../Resources/Textures/image_loading.h"
#include "../Resources/Textures/image_star.h"

#include "../Resources/Textures/image_cube.h"
#include "../Resources/Textures/image_cube_filled.h"
#include "../Resources/Textures/image_gun.h"
#include "../Resources/Textures/image_gun_filled.h"
#include "../Resources/Textures/image_pencil.h"
#include "../Resources/Textures/image_pencil_filled.h"
#include "../Resources/Textures/image_test.h"
#include "../Resources/Textures/image_test_filled.h"
#include "../Resources/Textures/image_wing.h"
#include "../Resources/Textures/image_wing_filled.h"

CTextures::CTextures()
{
	tApiFilled = nullptr;
	tApiOutlines = nullptr;
	tGearFilled = nullptr;
	tGearOutlines = nullptr;
	tItemsOutlines = nullptr;
	tItemsFilled = nullptr;
	tList = nullptr;
	tMedkitFilled = nullptr;
	tMedkitOutlines = nullptr;
	tModulesFilled = nullptr;
	tModulesOutlines = nullptr;
	tToolsFilled = nullptr;
	tToolsOutlines = nullptr;
	tUiFilled = nullptr;
	tUiOutlines = nullptr;
	tUsersFilled = nullptr;
	tUsersOutlines = nullptr;
	tWarnFilled = nullptr;
	tWarnOutlines = nullptr;
	tCoffee = nullptr;
	tCrown = nullptr;
	tExplosion = nullptr;
	tLoading = nullptr;
	tStar = nullptr;
	tCube = nullptr;
	tCubeFilled = nullptr;
	tGun = nullptr;
	tGunFilled = nullptr;
	tPencil = nullptr;
	tPencilFilled = nullptr;
	tTest = nullptr;
	tTestFilled = nullptr;
	tWing = nullptr;
	tWingFilled = nullptr;
}

CTextures::~CTextures()
{
}

bool CTextures::Initialize(ID3D11Device* pDevice)
{
    // Result of the Initialization.
    bool result = true;

    // Setup textures.
	D3DX11CreateShaderResourceViewFromMemory(pDevice, api_filled_bytes, sizeof(api_filled_bytes), &info0, pump0, &tApiFilled, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, api_outlines_bytes, sizeof(api_outlines_bytes), &info0, pump0, &tApiOutlines, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, gear_filled_bytes, sizeof(gear_filled_bytes), &info0, pump0, &tGearFilled, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, gear_outlines_bytes, sizeof(gear_outlines_bytes), &info0, pump0, &tGearOutlines, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, items_outlines_bytes, sizeof(items_outlines_bytes), &info0, pump0, &tItemsOutlines, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, items_filled_bytes, sizeof(items_filled_bytes), &info0, pump0, &tItemsFilled, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, list_bytes, sizeof(list_bytes), &info0, pump0, &tList, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, medkit_filled_bytes, sizeof(medkit_filled_bytes), &info0, pump0, &tMedkitFilled, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, medkit_outlines_bytes, sizeof(medkit_outlines_bytes), &info0, pump0, &tMedkitOutlines, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, modules_filled_bytes, sizeof(modules_filled_bytes), &info0, pump0, &tModulesFilled, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, modules_outlines_bytes, sizeof(modules_outlines_bytes), &info0, pump0, &tModulesOutlines, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, tools_filled_bytes, sizeof(tools_filled_bytes), &info0, pump0, &tToolsFilled, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, tools_outlines_bytes, sizeof(tools_outlines_bytes), &info0, pump0, &tToolsOutlines, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, ui_filled_bytes, sizeof(ui_filled_bytes), &info0, pump0, &tUiFilled, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, ui_outlines_bytes, sizeof(ui_outlines_bytes), &info0, pump0, &tUiOutlines, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, users_filled_bytes, sizeof(users_filled_bytes), &info0, pump0, &tUsersFilled, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, users_outlines_bytes, sizeof(users_outlines_bytes), &info0, pump0, &tUsersOutlines, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, warn_filled_bytes, sizeof(warn_filled_bytes), &info0, pump0, &tWarnFilled, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, warn_outlines_bytes, sizeof(warn_outlines_bytes), &info0, pump0, &tWarnOutlines, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, coffee_bytes, sizeof(coffee_bytes), &info0, pump0, &tCoffee, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, crown_bytes, sizeof(crown_bytes), &info0, pump0, &tCrown, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, explosion_bytes, sizeof(explosion_bytes), &info0, pump0, &tExplosion, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, loading_bytes, sizeof(loading_bytes), &info0, pump0, &tLoading, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, star_bytes, sizeof(star_bytes), &info0, pump0, &tStar, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, cube_bytes, sizeof(cube_bytes), &info0, pump0, &tCube, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, cube_filled_bytes, sizeof(gun_filled_bytes), &info0, pump0, &tCubeFilled, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, gun_bytes, sizeof(gun_bytes), &info0, pump0, &tGun, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, gun_filled_bytes, sizeof(gun_filled_bytes), &info0, pump0, &tGunFilled, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, pencil_bytes, sizeof(pencil_bytes), &info0, pump0, &tPencil, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, pencil_filled_bytes, sizeof(pencil_filled_bytes), &info0, pump0, &tPencilFilled, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, test_bytes, sizeof(test_bytes), &info0, pump0, &tTest, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, test_filled_bytes, sizeof(test_filled_bytes), &info0, pump0, &tTestFilled, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, wing_bytes, sizeof(wing_bytes), &info0, pump0, &tWing, 0);
	D3DX11CreateShaderResourceViewFromMemory(pDevice, wing_filled_bytes, sizeof(wing_filled_bytes), &info0, pump0, &tWingFilled, 0);

    return result;
}

void CTextures::Shutdown()
{
	tApiFilled->Release();
	tApiFilled = nullptr;
	tApiOutlines->Release();
	tApiOutlines = nullptr;
	tGearFilled->Release();
	tGearFilled = nullptr;
	tGearOutlines->Release();
	tGearOutlines = nullptr;
	tItemsOutlines->Release();
	tItemsOutlines = nullptr;
	tItemsFilled->Release();
	tItemsFilled = nullptr;
	tList->Release();
	tList = nullptr;
	tMedkitFilled->Release();
	tMedkitFilled = nullptr;
	tMedkitOutlines->Release();
	tMedkitOutlines = nullptr;
	tModulesFilled->Release();
	tModulesFilled = nullptr;
	tModulesOutlines->Release();
	tModulesOutlines = nullptr;
	tToolsFilled->Release();
	tToolsFilled = nullptr;
	tToolsOutlines->Release();
	tToolsOutlines = nullptr;
	tUiFilled->Release();
	tUiFilled = nullptr;
	tUiOutlines->Release();
	tUiOutlines = nullptr;
	tUsersFilled->Release();
	tUsersFilled = nullptr;
	tUsersOutlines->Release();
	tUsersOutlines = nullptr;
	tWarnFilled->Release();
	tWarnFilled = nullptr;
	tWarnOutlines->Release();
	tWarnOutlines = nullptr;
	tCoffee->Release();
	tCoffee = nullptr;
	tCrown->Release();
	tCrown = nullptr;
	tExplosion->Release();
	tExplosion = nullptr;
	tLoading->Release();
	tLoading = nullptr;
	tStar->Release();
	tStar = nullptr;
	tCube->Release();
	tCube = nullptr;
	tCubeFilled->Release();
	tCubeFilled = nullptr;
	tGun->Release();
	tGun = nullptr;
	tGunFilled->Release();
	tGunFilled = nullptr;
	tPencil->Release();
	tPencil = nullptr;
	tPencilFilled->Release();
	tPencilFilled = nullptr;
	tTest->Release();
	tTest = nullptr;
	tTestFilled->Release();
	tTestFilled = nullptr;
	tWing->Release();
	tWing = nullptr;
	tWingFilled->Release();
	tWingFilled = nullptr;
}

