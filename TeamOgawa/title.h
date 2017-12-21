#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "scene.h"

class CScene2D;
class C2DAnim;
class CTitle : public CScene
{
public:
	CTitle();
	~CTitle();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos) {}
	D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }

	void SetRotation(D3DXVECTOR3 rot) {}
	D3DXVECTOR3 GetRotation(void) { return D3DXVECTOR3(0.f, 0.f, 0.f); }

private:
	CScene2D *m_pBack;
	CScene2D *m_pTitle;
	CScene2D *m_pStart;
	CScene2D *m_pExit;
	float m_fTitlePos;
	float m_SelectPos;
	bool m_bSelect;
	bool m_bTimer;
};
#endif // !_TITLE_H_