#ifndef _INPUTCHECK_H_
#define _INPUTCHECK_H_

#include "scene.h"
#include "main.h"

class CInputCheck : public CScene
{
public:
	CInputCheck();
	~CInputCheck();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos) {}
	D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }

	void SetRotation(D3DXVECTOR3 rot) {}
	D3DXVECTOR3 GetRotation(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }

};
#endif // !_INPUTCHECK_H_