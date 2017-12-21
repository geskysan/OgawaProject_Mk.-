#ifndef _OBJECTBLOCK_H_
#define _OBJECTBLOCK_H_

#include "main.h"
#include "scene.h"
#include "object.h"


class CObjectBlock : public CObject
{
public:
	CObjectBlock();
	~CObjectBlock();
	HRESULT Init(D3DXVECTOR3 pos , D3DXVECTOR3 rot,float Width,float Heigth,float Depth);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3 GetBBMin(void) { return m_BBMin; }
	D3DXVECTOR3 GetBBMax(void) { return m_BBMax; }

protected:
	float	m_fWidth;	//横幅の長さ
	float	m_fHeigth;	//縦幅の長さ
	float	m_fDepth;	//奥行きの長さ

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9		m_pTexture;
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;
	D3DXMATRIX m_mtxWorld;

	//バウンディングボックス用
	D3DXVECTOR3 m_BBMin;
	D3DXVECTOR3 m_BBMax;
};

#endif // !_OBJECTBLOCK_H_