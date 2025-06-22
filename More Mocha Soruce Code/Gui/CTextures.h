#pragma once

// DirectX
#include <D3DX11tex.h>

class CTextures
{
public:
	CTextures();
	~CTextures();

	bool Initialize(ID3D11Device* pDevice);
	void Shutdown();

public:
	ID3D11ShaderResourceView* tApiFilled;
	ID3D11ShaderResourceView* tApiOutlines;
	ID3D11ShaderResourceView* tGearFilled;
	ID3D11ShaderResourceView* tGearOutlines;
	ID3D11ShaderResourceView* tItemsOutlines;
	ID3D11ShaderResourceView* tItemsFilled;
	ID3D11ShaderResourceView* tList;
	ID3D11ShaderResourceView* tMedkitFilled;
	ID3D11ShaderResourceView* tMedkitOutlines;
	ID3D11ShaderResourceView* tModulesFilled;
	ID3D11ShaderResourceView* tModulesOutlines;
	ID3D11ShaderResourceView* tToolsFilled;
	ID3D11ShaderResourceView* tToolsOutlines;
	ID3D11ShaderResourceView* tUiFilled;
	ID3D11ShaderResourceView* tUiOutlines;
	ID3D11ShaderResourceView* tUsersFilled;
	ID3D11ShaderResourceView* tUsersOutlines;
	ID3D11ShaderResourceView* tWarnFilled;
	ID3D11ShaderResourceView* tWarnOutlines;
	ID3D11ShaderResourceView* tCoffee;
	ID3D11ShaderResourceView* tCrown;
	ID3D11ShaderResourceView* tExplosion;
	ID3D11ShaderResourceView* tLoading;
	ID3D11ShaderResourceView* tStar;
	ID3D11ShaderResourceView* tCube;
	ID3D11ShaderResourceView* tCubeFilled;
	ID3D11ShaderResourceView* tGun;
	ID3D11ShaderResourceView* tGunFilled;
	ID3D11ShaderResourceView* tPencil;
	ID3D11ShaderResourceView* tPencilFilled;
	ID3D11ShaderResourceView* tTest;
	ID3D11ShaderResourceView* tTestFilled;
	ID3D11ShaderResourceView* tWing;
	ID3D11ShaderResourceView* tWingFilled;

private:
	D3DX11_IMAGE_LOAD_INFO info0;
	ID3DX11ThreadPump* pump0;
};
