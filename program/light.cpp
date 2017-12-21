//ライトの処理	[light.cpp]

//------------------------------------------------
//インクルードファイル
//------------------------------------------------
#include "light.h"
#include "manager.h"
#include "renderer.h"

//------------------------------------------------
//CLightコンストラクタ
//------------------------------------------------
CLight::CLight()
{

}

//------------------------------------------------
//CLightデストラクタ
//------------------------------------------------
CLight::~CLight()
{

}


//------------------------------------------------
//CLight初期化処理
//------------------------------------------------
HRESULT CLight::Init(void)
{
	SetLight();
	return S_OK;
}

//------------------------------------------------
//CLight終了処理
//------------------------------------------------
void CLight::Uninit(void)
{

}
//------------------------------------------------
//CLight更新処理
//------------------------------------------------
void CLight::Update(void)
{

}

//------------------------------------------------
//ライトの設定
//------------------------------------------------
void CLight::SetLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXVECTOR3 vecDir;

	//ライト0
	{
		// D3DLIGHT9構造体を0でクリアする
		ZeroMemory(&m_aLight[0], sizeof(D3DLIGHT9));

		// ライトのタイプの設定
		m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

		// 拡散光
		m_aLight[0].Diffuse.r = 10.0f;
		m_aLight[0].Diffuse.g = 10.0f;
		m_aLight[0].Diffuse.b = 10.0f;

		// 環境光
		m_aLight[0].Ambient.r = 10.50f;
		m_aLight[0].Ambient.g = 10.50f;
		m_aLight[0].Ambient.b = 10.50f;

		// ライトの方向の設定
		vecDir = D3DXVECTOR3(0.20f, -0.60f, 0.80f);
		D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[0].Direction, &vecDir);

		// ライトをレンダリングパイプラインに設定
		pDevice->SetLight(0, &m_aLight[0]);

		// ライトの設定
		pDevice->LightEnable(0, TRUE);
	}
	//ライト1
	{
		// D3DLIGHT9構造体を0でクリアする
		ZeroMemory(&m_aLight[1], sizeof(D3DLIGHT9));

		// ライトのタイプの設定
		m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

		// 拡散光
		m_aLight[1].Diffuse.r = 0.25f;
		m_aLight[1].Diffuse.g = 0.25f;
		m_aLight[1].Diffuse.b = 0.25f;

		// 環境光
		m_aLight[1].Ambient.r = 0.20f;
		m_aLight[1].Ambient.g = 0.20f;
		m_aLight[1].Ambient.b = 0.20f;

		// ライトの方向の設定
		vecDir = D3DXVECTOR3(-0.20f, 1.00f, -0.50f);
		D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[1].Direction, &vecDir);

		// ライトをレンダリングパイプラインに設定
		pDevice->SetLight(1, &m_aLight[1]);

		// ライトの設定
		pDevice->LightEnable(1, TRUE);
	}
	//ライト2
	{
		// D3DLIGHT9構造体を0でクリアする
		ZeroMemory(&m_aLight[2], sizeof(D3DLIGHT9));

		// ライトのタイプの設定
		m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;

		// 拡散光
		m_aLight[2].Diffuse.r = 10.0f;
		m_aLight[2].Diffuse.g = 10.0f;
		m_aLight[2].Diffuse.b = 10.0f;

		// 環境光
		m_aLight[2].Ambient.r = 10.50f;
		m_aLight[2].Ambient.g = 10.50f;
		m_aLight[2].Ambient.b = 10.50f;

		// ライトの方向の設定
		vecDir = D3DXVECTOR3(-0.20f, -0.60f, -0.80f);
		D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[2].Direction, &vecDir);

		// ライトをレンダリングパイプラインに設定
		pDevice->SetLight(2, &m_aLight[2]);

		// ライトの設定
		pDevice->LightEnable(2, TRUE);
	}
	// ライティングモード
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}