//2Dオブジェクトの処理	[scene2D.cpp]
#include "scene2D.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"

//------------------------------------------------
//マクロ定義
//------------------------------------------------
#define	NUM_VERTEX			(4)		// 頂点数
#define	NUM_POLYGON			(2)		// ポリゴン数

//------------------------------------------------
//CScene2D生成
//------------------------------------------------
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR2 polygonSize)
{
	CScene2D *pScene2D;

	pScene2D = new CScene2D;
	pScene2D->Init( pos, rot, polygonSize);

	return pScene2D;
}

//------------------------------------------------
//CScene2Dコンストラクタ
//------------------------------------------------
CScene2D::CScene2D(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;

}

//------------------------------------------------
//CScene2Dデストラクタ
//------------------------------------------------
CScene2D::~CScene2D()
{
}

//------------------------------------------------
//初期化処理
//------------------------------------------------
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR2 polygonSize)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ポリゴン表示位置の中心座標を設定
	m_pos = pos;
	m_bEnable = true;
	// ポリゴンの回転角を設定
	m_rot = rot;
	m_posTex = D3DXVECTOR2(0.f, 0.f);
	m_fLength = SetLength(polygonSize.x, polygonSize.y);
	m_fAngle = SetAngle(polygonSize.x, polygonSize.y);

									// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuff,				// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
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

																		// テクスチャステージステートパラメータの設定
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].pos.x = m_pos.x - sinf(m_fAngle - m_rot.z) * m_fLength;
		pVtx[0].pos.y = m_pos.y - cosf(m_fAngle - m_rot.z) * m_fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = m_pos.x + sinf(m_fAngle + m_rot.z) * m_fLength;
		pVtx[1].pos.y = m_pos.y - cosf(m_fAngle + m_rot.z) * m_fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = m_pos.x - sinf(m_fAngle + m_rot.z) * m_fLength;
		pVtx[2].pos.y = m_pos.y + cosf(m_fAngle + m_rot.z) * m_fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = m_pos.x + sinf(m_fAngle - m_rot.z) * m_fLength;
		pVtx[3].pos.y = m_pos.y + cosf(m_fAngle - m_rot.z) * m_fLength;
		pVtx[3].pos.z = 0.0f;

		// テクスチャのパースペクティブコレクト用
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

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

//------------------------------------------------
//終了処理
//------------------------------------------------
void CScene2D::Uninit(void)
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

//------------------------------------------------
//更新処理
//------------------------------------------------
void CScene2D::Update(void)
{

}

//------------------------------------------------
//描画処理
//------------------------------------------------
void CScene2D::Draw(void)
{

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	if (m_bEnable)
	{
		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}
//------------------------------------------------
//頂点の設定
//------------------------------------------------
void CScene2D::SetVertexPos(void)
{
	VERTEX_2D *pVtx;

	// 頂点をロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_pos.x - sinf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[0].pos.y = m_pos.y - cosf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[1].pos.y = m_pos.y - cosf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x - sinf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	// 頂点をアンロック
	m_pVtxBuff->Unlock();
}

//------------------------------------------------
//画像の読み込み
//------------------------------------------------
void CScene2D::LoadTexture(const char *pTextureName) {
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (!m_pTexture)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
			pTextureName,		// ファイルの名前
			&m_pTexture);		// 読み込むメモリー
	}

}

//------------------------------------------------
//頂点座標の設定
//------------------------------------------------
void CScene2D::SetVertexPos(D3DXVECTOR3 vtx0, D3DXVECTOR3 vtx1, D3DXVECTOR3 vtx2, D3DXVECTOR3 vtx3)
{
	VERTEX_2D *pVtx;

	// 頂点をロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = m_pos + vtx0;
	pVtx[1].pos = m_pos + vtx1;
	pVtx[2].pos = m_pos + vtx2;
	pVtx[3].pos = m_pos + vtx3;

	// 頂点をアンロック
	m_pVtxBuff->Unlock();
}

//------------------------------------------------
//頂点カラーの設定
//------------------------------------------------
void CScene2D::SetVertexCol(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;

	// 頂点をロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = col;

	// 頂点をアンロック
	m_pVtxBuff->Unlock();
}

//------------------------------------------------
//テクスチャ座標の設定
//------------------------------------------------
void CScene2D::SetVertexTex(void)
{
	VERTEX_2D *pVtx;

	// 頂点をロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(m_posTex.x, m_posTex.y);
	pVtx[1].tex = D3DXVECTOR2(m_posTex.x + 1.0f, m_posTex.y);
	pVtx[2].tex = D3DXVECTOR2(m_posTex.x, m_posTex.y + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_posTex.x + 1.0f, m_posTex.y + 1.0f);

	// 頂点をアンロック
	m_pVtxBuff->Unlock();
}

//------------------------------------------------
//テクスチャ座標の設定
//------------------------------------------------
void CScene2D::SetVertexTex(D3DXVECTOR2 tex0, D3DXVECTOR2 tex1, D3DXVECTOR2 tex2, D3DXVECTOR2 tex3)
{
	VERTEX_2D *pVtx;

	// 頂点をロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = tex0;
	pVtx[1].tex = tex1;
	pVtx[2].tex = tex2;
	pVtx[3].tex = tex3;

	// 頂点をアンロック
	m_pVtxBuff->Unlock();
}

//------------------------------------------------
//対角線の傾きの設定
//------------------------------------------------
void CScene2D::SetLengthPos(float fLength)
{
	m_fLength = fLength;
	VERTEX_2D *pVtx;

	// 頂点をロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].pos.x = m_pos.x - sinf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[0].pos.y = m_pos.y - cosf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[1].pos.y = m_pos.y - cosf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x - sinf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	// 頂点をアンロック
	m_pVtxBuff->Unlock();


}

//------------------------------------------------
//位置座標の設定
//------------------------------------------------
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{

	VERTEX_2D *pVtx;
	// 頂点をロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	pVtx[0].pos += m_pos - pos;
	pVtx[1].pos += m_pos - pos;
	pVtx[2].pos += m_pos - pos;
	pVtx[3].pos += m_pos - pos;

	// 頂点をアンロック
	m_pVtxBuff->Unlock();
	m_pos = pos;

}
