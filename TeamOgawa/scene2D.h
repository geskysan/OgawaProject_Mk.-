//2Dオブジェクトの処理	[scene2D.h]
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//------------------------------------------------
//インクルードファイル
//------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------
//マクロ定義
//------------------------------------------------

//頂点フォーマット(頂点座標[2D] / 頂点カラー /  テクスチャ座標)
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define NUM_TEXTURE_MAX	(3)

//------------------------------------------------
//構造体定義
//------------------------------------------------
//上記頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float		rhw;	//座標変数用係数(1.0fで固定)
	D3DCOLOR	col;	//頂点カラー
	D3DXVECTOR2	tex;	//テクスチャ座標
}VERTEX_2D;

//------------------------------------------------
//2Dオブジェクトクラス
//------------------------------------------------
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority = 6, CScene::OBJTYPE objType = CScene::OBJTYPE_2D);
	~CScene2D();

	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot , D3DXVECTOR2 polygonSize);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR2 polygonSize);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }

	void SetVertexPos(D3DXVECTOR3 vtx0, D3DXVECTOR3 vtx1, D3DXVECTOR3 vtx2, D3DXVECTOR3 vtx3);
	void SetVertexCol(D3DXCOLOR col);
	void SetVertexTex(D3DXVECTOR2 tex0, D3DXVECTOR2 tex1, D3DXVECTOR2 tex2, D3DXVECTOR2 tex3);
	void LoadTexture(const char *pTextureName);
	void SetLengthPos(float fLength);
	float GetLength(void) { return m_fLength; }
	bool GetbEnable(void) { return m_bEnable; }
	void SetbEnable(bool bEnable) { m_bEnable = bEnable; }
protected:
	void SetVertexPos(void);
	void SetVertexTex(void);
	D3DXVECTOR2 m_posTex;
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ

	D3DXVECTOR3 m_pos;						// 位置標
	D3DXVECTOR3 m_rot;						// 向き
	float m_fLength;						// 対角線の長さ
	float m_fAngle;							// 対角線の傾き

	bool m_bEnable;

};
#endif // !_SCENE2D_H_