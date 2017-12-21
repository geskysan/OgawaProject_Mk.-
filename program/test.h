#ifndef _TEST_H_
#define _TEST_H_

#include "main.h"
#include "scene.h"

class CPlayer;
class CObjectBlock;
class CObjectSphere;
class CObjectManager;
class C2DAnim;
class CObjectMoveBlock;
class CEnemy;

#define MAX_MOVE	3
class CTest : public CScene
{
public:
	CTest();
	~CTest();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos) {}
	D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }

	void SetRotation(D3DXVECTOR3 rot) {}
	D3DXVECTOR3 GetRotation(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }


private:
	CPlayer *m_pPlayer;
	CObjectBlock *m_pObj;
	CObjectSphere *m_pSphere;
	CObjectManager *m_pObjectManager;
	D3DXVECTOR3 rot;
	CObjectMoveBlock *m_pMoveBlock[MAX_MOVE];
	C2DAnim *m_p2DAnim;
	CEnemy *m_pEnemy;
};
#endif // !_ENDING_H_