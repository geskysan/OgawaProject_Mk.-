#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include "main.h"
#include "scene.h"

#define NUM_OBJECT_X 20
#define NUM_OBJECT_Y 20
class CObjectBlock;
class CPlayer;
class CObjectManager : public CScene
{
public:
	CObjectManager();
	~CObjectManager();
	HRESULT Init(const char *FileName);
	void Uninit();
	void Update();
	void Draw();
	void Collision(CPlayer *pPlayer);
	void SetPosition(D3DXVECTOR3 pos) {}
	D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }

	void SetRotation(D3DXVECTOR3 rot) {}
	D3DXVECTOR3 GetRotation(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }

	typedef enum
	{
		OBJECT_NONE = 0,
		OBJECT_BLOCK,
		OBJECT_MAX,
	}OBJECT_TYPE;
private:
	CObjectBlock *m_apObject[NUM_OBJECT_X][NUM_OBJECT_Y];
};
#endif // !_OBJECTMANAGER_H_