//=============================================================================
//
// ビルボードオブジェクトの処理 [sceneBillboard.h]
// Author : 
//
//=============================================================================
#ifndef _SCENEBILLBOARD_H_
#define _SCENEBILLBOARD_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 頂点フォーマット( 頂点座標 / 法線 / 頂点カラー / テクスチャ座標 )
#define	FVF_VERTEX_BILLBOARD	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
// 上記頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 nor;	// 法線
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_BILLBOARD;

//*********************************************************
// Billboardオブジェクトクラス
//*********************************************************
class CSceneBillboard : public CScene
{
public:
	CSceneBillboard(int nPriority = 4, CScene::OBJTYPE objType = CScene::OBJTYPE_BILLBOARD);
	~CSceneBillboard();

	HRESULT Init(int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR2 textureSize);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }

	void SetType(int nType) { m_nType = nType; }

	void SetVtx(float fLength);
	void SetTex(D3DXVECTOR2 tex0, D3DXVECTOR2 tex1, D3DXVECTOR2 tex2, D3DXVECTOR2 tex3);
	void SetColAlpha(float fAlpha);
	void LoadTexture(const char *pTextureName);
protected:
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ

	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス

	D3DXVECTOR3 m_pos;						// 位置
	D3DXVECTOR3 m_rot;						// 向き
	float m_fLength;						// 対角線の長さ
	float m_fAngle;							// 対角線の角度

	int m_nType;							// 種類
};

#endif
