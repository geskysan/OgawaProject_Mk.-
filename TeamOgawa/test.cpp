#include "test.h"
#include "manager.h"
#include "renderer.h"
#include "sceneX.h"
#include "sound.h"
#include "debugproc.h"
#include "scenebillboard.h"
#include "player.h"
#include "objectblock.h"
#include "objectsphere.h"
#include "objectmanager.h"
#include "object.h"
#include "2Danim.h"
#include "input.h"
#include "objectmoveblock.h"
#include "enemy.h"

CTest::CTest()
{
	m_pSphere = NULL;
	m_pObj = NULL;
	m_pPlayer = NULL;
	m_p2DAnim = NULL;
	m_pObjectManager = NULL;
	m_pEnemy = NULL;
	for (int iCnt = 0; iCnt < MAX_MOVE; iCnt++)
		m_pMoveBlock[iCnt] = NULL;
}

CTest::~CTest()
{

}

HRESULT CTest::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	m_pSphere = new CObjectSphere;
	m_pSphere->Init(D3DXVECTOR3(0, -2300, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3000, 3000,32, 32);

	m_pObjectManager = new CObjectManager;
	m_pObjectManager->Init("MAP/TESTSTAGE/test.csv");

	m_pEnemy = new CEnemy;
	m_pEnemy->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::ENEMY_TYPE_1);

	for (int iCnt = 0; iCnt < MAX_MOVE; iCnt++)
	{
		m_pMoveBlock[iCnt] = new CObjectMoveBlock;
		m_pMoveBlock[iCnt]->InitSetRotate(D3DXVECTOR3(-300.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 50.0f), iCnt *( D3DX_PI*2) / MAX_MOVE, 0.01f, 250.0f);
	//	m_pMoveBlock[iCnt]->InitSetRepete(D3DXVECTOR3(-50 * iCnt, iCnt*10, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 50.0f), D3DXVECTOR3(0.0f, -0.2f, 0.0f), 2220);
	}
	m_pPlayer = new CPlayer;
	m_pPlayer->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

void CTest::Uninit(void)
{
	SAFE_UNINIT(m_p2DAnim);
	SAFE_UNINIT(m_pPlayer);
	SAFE_UNINIT(m_pObj);
	SAFE_UNINIT(m_pSphere);
	SAFE_UNINIT(m_pObjectManager);
	for (int iCnt = 0; iCnt < MAX_MOVE; iCnt++)
		SAFE_UNINIT(m_pMoveBlock[iCnt]);
	Release();

}

void CTest::Update(void)
{	

	m_pObjectManager->Collision(m_pPlayer);
//	m_pPlayer->CollisionBlock(m_pMoveBlock);
	m_pEnemy->Collision(m_pPlayer);
	for (int iCnt = 0; iCnt < MAX_MOVE; iCnt++)
	m_pMoveBlock[iCnt]->Collision(m_pPlayer);
	m_pPlayer->KeyControl();
	m_pSphere->SetSphere(m_pPlayer->GetPosition());
	CDebugProc::Print("シーン:デバッグ\n");
}

void CTest::Draw(void)
{
	D3DXVECTOR3 pos;
}