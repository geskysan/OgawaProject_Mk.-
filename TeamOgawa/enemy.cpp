//“G‚Ìˆ—	[enemy.cpp]
#include "enemy.h"
#include "player.h"
#include "debugproc.h"
#include "library.h"
#define ENEMY_SIZE_X 30
#define ENEMY_SIZE_Y 30
CEnemy::CEnemy()
{

}

CEnemy::~CEnemy()
{

}

HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ENEMY_TYPE EnemyType)
{
	CScene3D::Init(0, pos, rot, ENEMY_SIZE_X, ENEMY_SIZE_Y);
	CScene3D::LoadTexture("data/TEXTURE/enemy000.png");

	CScene3D::SetVertexPos(D3DXVECTOR3(ENEMY_SIZE_X / 2, ENEMY_SIZE_Y, 0),
		D3DXVECTOR3(ENEMY_SIZE_X / 2, 0, 0),
		D3DXVECTOR3(-ENEMY_SIZE_X / 2, ENEMY_SIZE_Y, 0),
		D3DXVECTOR3(-ENEMY_SIZE_X / 2, 0, 0));

	return S_OK;
}

void CEnemy::Uninit(void)
{
	CScene3D::Uninit();
}

void CEnemy::Update(void)
{
	m_BBMin = m_pos + D3DXVECTOR3(-ENEMY_SIZE_X / 2, 0.0f, 20.0f);
	m_BBMax = m_pos + D3DXVECTOR3(ENEMY_SIZE_X / 2, ENEMY_SIZE_Y, 20.0f);

}

void CEnemy::Draw(void)
{
	CScene3D::Draw();
}

void CEnemy::Collision(CPlayer *pPlayer)
{
	D3DXVECTOR3 PlayerMin = pPlayer->GetBBMin();
	D3DXVECTOR3 PlayerMax = pPlayer->GetBBMax();
	if (CollisionAABB2D(m_BBMin, m_BBMax, PlayerMin, PlayerMax))
	{
		CDebugProc::Print("‰´‚ÌƒEƒ‹ƒg‚Ì‚¨‚©‚°\n");
	}

}
