//敵の処理	[enemy.h]
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "scene3D.h"
class CPlayer;

class CEnemy : public CScene3D
{
public:
	typedef enum
	{
		ENEMY_TYPE_NONE = 0,
		ENEMY_TYPE_1,
		ENEMY_TYPE_2,
		ENEMY_TYPE_MAX,
	}ENEMY_TYPE;
	
	CEnemy();
	~CEnemy();
	
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot ,ENEMY_TYPE EnemyType);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Collision(CPlayer *pPlayer);

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void SetPostion(D3DXVECTOR3 pos) { m_pos = pos; }

	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }

	D3DXVECTOR3 GetBBMin(void) { return m_BBMin; }
	D3DXVECTOR3 GetBBMax(void) { return m_BBMax; }
private:
	//バウンディングボックス用
	D3DXVECTOR3 m_BBMin;
	D3DXVECTOR3 m_BBMax;

};
#endif //!_ENEMY_H_