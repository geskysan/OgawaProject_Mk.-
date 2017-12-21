//îºãÖëÃÇÃèàóù
#ifndef _OBJECTSPHERE_H_
#define _OBJECTSPHERE_H_

#include "main.h"
#include "scene.h"
#include "object.h"

class CObjectSphere : public CObject
{
public:
	CObjectSphere();
	~CObjectSphere();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float fLength,float fRadius,int iPolygonX,int iPolygonZ,const char *FileName);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void InitTop(LPDIRECT3DDEVICE9 pDevice);
	void DrawTop(LPDIRECT3DDEVICE9 pDevice);

	void SetSphere(D3DXVECTOR3 pos);

	bool Collision(CPlayer *pPlayer) { return false; }
private:
	float	m_fLength;
	float	m_fRadius;

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffTop;
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuffTop;

	int m_iIdxNum;
	int m_iVertexNum;
	int m_iPolygonNum;
	int m_iPolygon_X;
	int m_iPolygon_Z;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9		m_pTexture;
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;
	D3DXMATRIX m_mtxWorld;
};

#endif // !_OBJECTSPHERE_H_