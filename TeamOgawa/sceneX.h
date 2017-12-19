//Xファイルオブジェクトの処理	[sceneX.h]
#ifndef _SCENEX_H_
#define _SCENEX_H_

//------------------------------------------------
//インクルードファイル
//------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------
//Xファイルオブジェクト
//------------------------------------------------
class CSceneX : public CScene
{
public:
	CSceneX(int nPriority = 3, CScene::OBJTYPE objtype = CScene::OBJTYPE_X);
	~CSceneX();

	static CSceneX *Create(int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	HRESULT Init(int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(void) { return S_OK; }
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }

	void SetScale(D3DXVECTOR3 scale) { m_scale = scale; }
	D3DXVECTOR3 GetScale(void) { return m_scale; }

	LPD3DXMESH GetMesh(void) { return m_pMesh; }

	void SetType(int nType) { m_nType = nType; }

	void SetbUse(bool bUse) { m_bUse = bUse; }

	void SetTexture(const char *TextureName);
protected:
	LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャへのポインタ
	LPD3DXMESH m_pMesh;					// メッシュ情報へのポインタ
	LPD3DXBUFFER m_pBuffMat;			// マテリアル情報へのポインタ
	DWORD m_nNumMat;					// マテリアル情報の総数

	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス

	D3DXVECTOR3 m_pos;					// の位置
	D3DXVECTOR3 m_rot;					// 現在の向き
	D3DXVECTOR3 m_scale;				//拡大値
	int m_nType;						// 種類
	bool m_bUse;							//描画するかどうか
	static const char *m_apModelName[];

};

#endif // !_SCENEX_H_
