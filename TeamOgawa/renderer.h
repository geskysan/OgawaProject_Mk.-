//�����_�����O����	[renderer.h]
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

//------------------------------------------------
// �`��N���X
//------------------------------------------------
class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }

private:
	LPDIRECT3D9 m_pD3D;					// Direct3D �I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice;		// Device�I�u�W�F�N�g(�`��ɕK�v)
};

#endif