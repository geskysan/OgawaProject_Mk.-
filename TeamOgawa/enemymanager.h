#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_

#define MAX_ENEMY	10
#include "scene.h"

class CEnemy;

class CEnemyManager : public CScene
{
public:
	CEnemyManager();
	~CEnemyManager();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CEnemy *m_apEnemy[MAX_ENEMY];

};
#endif	//_ENEMYMANAGER_H_