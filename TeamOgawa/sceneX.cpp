//=============================================================================
//
// Xファイルオブジェクトの処理 [sceneX.cpp]
// Author : 
//
//=============================================================================
#include "sceneX.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// 静的変数
//*****************************************************************************
const char *CSceneX::m_apModelName[] =
{
	"data/OBJECT3D/test.x"
};


//=============================================================================
// CSceneX生成
//=============================================================================
CSceneX *CSceneX::Create(int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CSceneX *pSceneX;

	pSceneX = new CSceneX;
	pSceneX->Init(nType, pos, rot);

	return pSceneX;
}

//=============================================================================
// CSceneXコンストラクタ
//=============================================================================
CSceneX::CSceneX(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_pTexture = NULL;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_nNumMat = 0;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_nType = 0;
}

//=============================================================================
// CSceneXデストラクタ
//=============================================================================
CSceneX::~CSceneX()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSceneX::Init(int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// タイプを設定
	m_nType = nType;

	// ポリゴン表示位置の中心座標を設定
	m_pos = pos;

	// ポリゴンの回転角を設定
	m_rot = rot;

	// Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(m_apModelName[nType],
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh)))
	{
		return E_FAIL;
	}

#if 0
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_FILENAME,		// ファイルの名前
		&m_pTexture);			// 読み込むメモリー
#endif

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSceneX::Uninit(void)
{
	if (m_pTexture)
	{// テクスチャの開放
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	if (m_pBuffMat)
	{// マテリアルの開放
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	if (m_pMesh)
	{// メッシュの開放
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//	// オブジェクトをリストから削除
	//	CScene::UnlinkList();
	// オブジェクトを破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CSceneX::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CSceneX::Draw(void)
{
	/*if (!m_bUse || !m_pMesh)
		return;*/
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxScale, mtxRot, mtxTranslate;
	D3DMATERIAL9 matDef;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 拡大を反映
	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.x, m_scale.x);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	D3DXMATERIAL *pD3DXMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{

		// マテリアルの設定
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, m_pTexture);

		// 描画
		m_pMesh->DrawSubset(nCntMat);

	}

	// マテリアルを元に戻す
	pDevice->SetMaterial(&matDef);
}

void CSceneX::SetTexture(const char *TextureName)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TextureName,		// ファイルの名前
		&m_pTexture);			// 読み込むメモリー

}