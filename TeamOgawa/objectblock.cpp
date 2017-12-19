#include "objectblock.h"
#include "manager.h"
#include "renderer.h"
#include "scene3D.h"
#include "player.h"
#include "debugproc.h"
#include "library.h"

#define BLOCK_VERTEX	(14)
#define BLOCK_PRIM		(12)
#define BLOCK_IDX		(14)
#define NUM_VERTEX		(4)

CObjectBlock::CObjectBlock()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
}

CObjectBlock::~CObjectBlock()
{

}

HRESULT CObjectBlock::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Width, float Heigth,float Depth)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CObject::Init();
	// 位置を設定
	m_pos = pos;

	// 向きを設定
	m_rot = rot;

	//横幅の設定
	m_fWidth = Width;

	//縦幅の設定
	m_fHeigth = Heigth;

	//奥行きの設定
	m_fDepth = Depth;

	float fAngle = SetAngle(m_fWidth, m_fDepth);
	float fLength = SetLength(m_fWidth, m_fDepth);


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		"data/TEXTURE/blocktest.jpg",	// ファイルの名前
		&m_pTexture);				// 読み込むメモリー

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * BLOCK_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuff,				// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}
	
	if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * BLOCK_IDX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL)))
	{
		return E_FAIL;
	}


	VERTEX_3D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//横面部分
	for (int iCntVertex = 0; iCntVertex < 2; iCntVertex++)
	{
		pVtx[0].pos = D3DXVECTOR3(-sinf(fAngle)*fLength, -m_fHeigth *iCntVertex, cosf(fAngle)*fLength);
		pVtx[1].pos = D3DXVECTOR3(sinf(fAngle)*fLength, -m_fHeigth*iCntVertex, cosf(fAngle)*fLength);
		pVtx[2].pos = D3DXVECTOR3(-sinf(fAngle)*fLength, -m_fHeigth*iCntVertex, -cosf(fAngle)*fLength);
		pVtx[3].pos = D3DXVECTOR3(sinf(fAngle)*fLength, -m_fHeigth*iCntVertex, -cosf(fAngle)*fLength);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		float fTex = iCntVertex * 0.1f;
		pVtx[0].tex = D3DXVECTOR2(0.01f, iCntVertex);
		pVtx[1].tex = D3DXVECTOR2(0.49 / 3, iCntVertex);
		pVtx[2].tex = D3DXVECTOR2(0.49f/3 + 0.49/3, iCntVertex);
		pVtx[3].tex = D3DXVECTOR2(0.49f, iCntVertex);

		pVtx += 4;
	}
	//上面部分
		pVtx[0].pos = D3DXVECTOR3(-sinf(fAngle)*fLength, 0.0f, cosf(fAngle)*fLength);
		pVtx[1].pos = D3DXVECTOR3(sinf(fAngle)*fLength, 0.0f, cosf(fAngle)*fLength);
		pVtx[2].pos = D3DXVECTOR3(-sinf(fAngle)*fLength,0.0f, -cosf(fAngle)*fLength);
		pVtx[3].pos = D3DXVECTOR3(sinf(fAngle)*fLength, 0.0f, -cosf(fAngle)*fLength);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);


	m_pVtxBuff->Unlock();

	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	pIdx[0] = 6;
	pIdx[1] = 2;
	pIdx[2] = 7;
	pIdx[3] = 3;
	
	pIdx[4] = 5;
	pIdx[5] = 1;
	pIdx[6] = 4;
	pIdx[7] = 0;
	
	pIdx[8] = 6;
	pIdx[9] = 2;
	
	pIdx[10] = 10;
	pIdx[11] = 8;
	pIdx[12] = 11;
	pIdx[13] = 9;
	m_pIdxBuff->Unlock();
	return S_OK;
}

void CObjectBlock::Uninit(void)
{
	SAFE_RELESE(m_pVtxBuff);
	SAFE_RELESE(m_pTexture);
	SAFE_RELESE(m_pIdxBuff);
	CObject::Uninit();
}

void CObjectBlock::Update(void)
{
	m_BBMin = m_pos + D3DXVECTOR3(-m_fWidth/2, -m_fHeigth,-m_fDepth/2);
	m_BBMax = m_pos + D3DXVECTOR3(m_fWidth/2, 0.0f, m_fDepth/2);
	CObject::Update();
}

void CObjectBlock::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot,mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		BLOCK_VERTEX,
		0,
		BLOCK_PRIM);
}