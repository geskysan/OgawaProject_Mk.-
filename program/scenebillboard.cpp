//=============================================================================
//
// Billboardオブジェクトの処理 [sceneBillboard.cpp]
// Author : 
//
//=============================================================================
#include "sceneBillboard.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "library.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_VERTEX			(4)		// 頂点数
#define	NUM_POLYGON			(2)		// ポリゴン数

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//=============================================================================
// CSceneBillboardコンストラクタ
//=============================================================================
CSceneBillboard::CSceneBillboard(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nType = 0;
}

//=============================================================================
// CSceneBillboardデストラクタ
//=============================================================================
CSceneBillboard::~CSceneBillboard()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSceneBillboard::Init(int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot,  D3DXVECTOR2 textureSize)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// タイプを設定
	m_nType = nType;

	// ポリゴンの位置を設定
	m_pos = pos;

	// ポリゴンの向きを設定
	m_rot = rot;

	// ポリゴンの対角線の長さを設定
	m_fLength = SetLength(textureSize.x, textureSize.y);
	// ポリゴンの対角線の角度を設定
	m_fAngle = atan2f(textureSize.x, textureSize.y);

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_BILLBOARD) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,					// 頂点バッファの使用法　
		FVF_VERTEX_BILLBOARD,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuff,						// 頂点バッファインターフェースへのポインタ
		NULL)))								// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_BILLBOARD *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
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
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

																	// サンプラーステートパラメータの設定
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大時の補間設定
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小時の補間設定
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャＵ値の繰り返し設定
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャＶ値の繰り返し設定

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSceneBillboard::Uninit(void)
{
	// テクスチャの開放
	if (m_pTexture)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// 頂点バッファの開放
	if (m_pVtxBuff)
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
void CSceneBillboard::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CSceneBillboard::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxScale, mtxRot, mtxTranslate, mtxView;
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
#if 1
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;
#else
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;
#endif

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをレンダリングパイプラインに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_BILLBOARD));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_BILLBOARD);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

}

//=============================================================================
// テクスチャ座標設定
//=============================================================================
void CSceneBillboard::SetTex(D3DXVECTOR2 tex0, D3DXVECTOR2 tex1, D3DXVECTOR2 tex2, D3DXVECTOR2 tex3)
{
	{//頂点バッファの中身を埋める
		VERTEX_BILLBOARD *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// テクスチャ座標の設定
		pVtx[0].tex = tex0;
		pVtx[1].tex = tex1;
		pVtx[2].tex = tex2;
		pVtx[3].tex = tex3;

		// 頂点データをアンロックする
		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
// テクスチャ座標設定
//=============================================================================
void CSceneBillboard::SetVtx(float fLength)
{
	{//頂点バッファの中身を埋める
		VERTEX_BILLBOARD *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].pos.x = -sinf(m_fAngle) * fLength;
		pVtx[0].pos.y = cosf(m_fAngle) * fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = sinf(m_fAngle) * fLength;
		pVtx[1].pos.y = cosf(m_fAngle) * fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = -sinf(m_fAngle) * fLength;
		pVtx[2].pos.y = -cosf(m_fAngle) * fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = sinf(m_fAngle) * fLength;
		pVtx[3].pos.y = -cosf(m_fAngle) * fLength;
		pVtx[3].pos.z = 0.0f;

		// 頂点データをアンロックする
		m_pVtxBuff->Unlock();
	}
}

void CSceneBillboard::SetColAlpha(float fAlpha)
{
	VERTEX_BILLBOARD *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);

	m_pVtxBuff->Unlock();
}
void CSceneBillboard::LoadTexture(const char *pTextureName)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		pTextureName,										// ファイルの名前
		&m_pTexture);										// 読み込むメモリー

}
