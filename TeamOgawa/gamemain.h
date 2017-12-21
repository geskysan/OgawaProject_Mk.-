#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

#include "main.h"
#include "scene.h"

class CObjectSphere;
class CGamemain : public CScene
{
public:
	CGamemain();
	~CGamemain();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	void SetPosition(D3DXVECTOR3 pos) {}
	D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }

	void SetRotation(D3DXVECTOR3 rot) {}
	D3DXVECTOR3 GetRotation(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }

private:
	CObjectSphere *m_apSphere;
};
#endif // !_GAMEMAIN_H_