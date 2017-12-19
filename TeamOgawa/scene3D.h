//3Dオブジェクトの処理	[scene3D.h]
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//------------------------------------------------
//インクルードファイル
//------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------
//マクロ定義
//------------------------------------------------
//頂点フォーマット(頂点座標 / 法線 / 頂点カラー / テクスチャ座標)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//------------------------------------------------
//構造体定義
//------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;	//法線
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
}VERTEX_3D;

//------------------------------------------------
//3Dオブジェクトクラス
//------------------------------------------------
class CScene3D : public CScene
{
public:
	CScene3D(int nPriority = 3, CScene::OBJTYPE objtype = CScene::OBJTYPE_3D);
	~CScene3D();

	static CScene3D *Create(int nType,D3DXVECTOR3 pos, D3DXVECTOR3 rot, int iWidht, int iHeight);
	
	HRESULT Init(int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int iWidth, int Height);
	HRESULT Init(void) { return S_OK; }
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	void LoadTexture(const char *TextureName);
	void SetType(int nType) { m_nType = nType; }

	void SetVertexPos(D3DXVECTOR3 RightUp, D3DXVECTOR3 RightDown, D3DXVECTOR3 LeftUp, D3DXVECTOR3 LeftDown);
	void SetEnable(bool bUse) { m_bEnable = bUse; }
	bool GetEnable(void) { return m_bEnable; }
protected:
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ

	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス

	D3DXVECTOR3 m_pos;						// 位置
	D3DXVECTOR3 m_rot;						// 向き
	D3DXVECTOR3 m_scale;					// 大き
	float m_fLength;						// 対角線の長さ
	float m_fAngle;							// 対角線の角度

	int m_nType;							// 種類

	bool m_bEnable;							//描画の切り替え
	static const char *m_apTextureName[];

};
#endif // !_SCENE3D_H_