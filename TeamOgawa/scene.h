//描画対象オブジェクトの処理	[scene.h]
#ifndef _SCENE_H_
#define _SCENE_H_

//------------------------------------------------
//インクルードファイル
//------------------------------------------------
#include "main.h"

//------------------------------------------------
//マクロ定義
//------------------------------------------------
#define NUM_PRIORITY	(7)	//描画優先度枠数
//------------------------------------------------
//描画対象オブジェクトクラス
//------------------------------------------------
class CScene
{
public:
	//オブジェクトタイプ
	typedef enum
	{
		OBJTYPE_NONE=0,
		OBJTYPE_2D,
		OBJTYPE_3D,
		OBJTYPE_X,
		OBJTYPE_BILLBOARD,
		OBJTYPE_FADE,
		OBJTYPE_PLAYER,
		OBJTYPE_MAX,
	}OBJTYPE;

	CScene(int nPriority = 3, OBJTYPE objType = OBJTYPE_NONE);
	virtual ~CScene();

	virtual HRESULT Init(void) { return S_OK; }
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	void LinkList(int nPriority);
	void UnlinkList(void);
	void Release(void);

	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);

	static void InitList(void);
	static void UninitList(void);

	virtual void SetPosition(D3DXVECTOR3 pos) = 0;
	virtual D3DXVECTOR3 GetPosition(void) = 0;

	virtual void SetRotation(D3DXVECTOR3 rot) = 0;
	virtual D3DXVECTOR3 GetRotation(void) = 0;

	virtual void SetMove(float x, float y, float z) {}
	virtual D3DXVECTOR3 GetMove(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }

	void SetObjType(OBJTYPE objType) { m_objType = objType; }
	OBJTYPE GetObjType(void) { return m_objType; }

	static CScene *GetListTop(int nPriority = 3);
	CScene *GetNext() { return m_pNext; }

	virtual D3DXVECTOR3 GetPositionMin(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	virtual D3DXVECTOR3 GetPositionMax(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }

private:
	// リスト用
	static CScene *m_apTop[NUM_PRIORITY];	// リストの先頭位置へのポインタ
	static CScene *m_apCur[NUM_PRIORITY];	// リストの現在位置へのポインタ
	CScene *m_pPrev;						// 前のオブジェへのポインタ
	CScene *m_pNext;						// 次のオブジェへのポインタ

	int m_nPriority;						// プライオリティ番号

	OBJTYPE m_objType;						// オブジェクトタイプ
	bool m_bDelete;

};
#endif // !_SCENE_H_