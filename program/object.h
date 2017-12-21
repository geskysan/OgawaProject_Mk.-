#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include "scene.h"
class CPlayer;
class CObject : public CScene
{
public:
	CObject();
	~CObject();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	virtual void RotationMode(bool bRotMode,D3DXVECTOR3 RotMove);

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }

protected:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	
	bool m_bRotMode;

	D3DXVECTOR3 m_RotMove;
};
#endif // !_OBJECT_H_