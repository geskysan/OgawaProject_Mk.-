//=============================================================================
//
// 3Dオブジェクトの処理 [scene3D.cpp]
// Author : 
//
//=============================================================================
#include "scene3D.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_WIDTH	(100)	// テクスチャの幅
#define TEXTURE_HEIGHT	(100)	// テクスチャの高さ

#define	NUM_VERTEX		(4)		// 頂点数
#define	NUM_POLYGON		(2)		// ポリゴン数

//*****************************************************************************
// 構造体定義
//*****************************************************************************


//*****************************************************************************
// 静的変数
//*****************************************************************************
const char *CScene3D::m_apTextureName[] =
{
	"",
};

//=============================================================================
// CScene3D生成
//=============================================================================
CScene3D *CScene3D::Create(int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int iWidth, int iHeight)
{
	CScene3D *pScene3D;

	pScene3D = new CScene3D;
	pScene3D->Init(nType, pos, rot, iWidth, iHeight);

	return pScene3D;
}

//=============================================================================
// CScene3Dコンストラクタ
//=============================================================================
CScene3D::CScene3D(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
}

//=============================================================================
// CScene3Dデストラクタ
//=============================================================================
CScene3D::~CScene3D()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene3D::Init(int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int iWidth = 100, int iHeight = 100)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// タイプを設定
	m_nType = nType;

	// 位置を設定
	m_pos = pos;

	// 向きを設定
	m_rot = rot;

	// 大きさを設定
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//描画の設定
	m_bEnable = true;

	// 対角線の長さ・角度を設定
	m_fLength = sqrtf((float)(((iWidth / 2.f) * (iWidth / 2.f)) + ((iHeight / 2.f) * (iHeight / 2.f))));
	m_fAngle = atan2f((iWidth / 2.f), (iHeight / 2.f));

	// テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
	//	m_apTextureName[nType],		// ファイルの名前
	//	&m_pTexture);				// 読み込むメモリー

									// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuff,				// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定q
		pVtx[0].pos.x = -sinf(m_fAngle) * m_fLength;
		pVtx[0].pos.y = cosf(m_fAngle) * m_fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = sinf(m_fAngle) * m_fLength;
		pVtx[1].pos.y = cosf(m_fAngle) * m_fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = -sinf(m_fAngle) * m_fLength;
		pVtx[2].pos.y = -cosf(m_fAngle) * m_fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = sinf(m_fAngle) * m_fLength;
		pVtx[3].pos.y = -cosf(m_fAngle) * m_fLength;
		pVtx[3].pos.z = 0.0f;

		// 法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		m_pVtxBuff->Unlock();
	}

	
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScene3D::Uninit(void)
{
	// テクスチャの開放
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// 頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//	// オブジェクトをリストから削除
	//	CScene::UnlinkList();
	// オブジェクトを破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScene3D::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CScene3D::Draw(void)
{
	if (!m_bEnable)
		return;

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxScale, mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	
	// 拡縮を反映
	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをレンダリングパイプラインに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

void CScene3D::LoadTexture(const char *TextureName)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// タイプを設定

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TextureName,		// ファイルの名前
		&m_pTexture);				// 読み込むメモリー

}

void CScene3D::SetVertexPos(D3DXVECTOR3 RightUp, D3DXVECTOR3 RightDown, D3DXVECTOR3 LeftUp, D3DXVECTOR3 LeftDown)
{
	VERTEX_3D *pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	pVtx[0].pos = RightUp;
	pVtx[1].pos = LeftUp;
	pVtx[2].pos = RightDown;
	pVtx[3].pos = LeftDown;

	pVtx[0].pos = LeftUp;
	pVtx[1].pos = RightUp;
	pVtx[2].pos = LeftDown;
	pVtx[3].pos = RightDown;

	m_pVtxBuff->Unlock();

}

