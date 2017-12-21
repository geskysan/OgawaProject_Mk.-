//ゲームメイン処理
#include "gamemain.h"
#include "debugproc.h"
#include "objectsphere.h"

CGamemain::CGamemain()
{
	m_apSphere = NULL;
}

CGamemain::~CGamemain()
{

}

HRESULT CGamemain::Init(void)
{
	m_apSphere = new CObjectSphere;
	m_apSphere->Init(D3DXVECTOR3(0.0f, -1500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3000, 3000, 32, 32,"data/TEXTURE/sky000.jpg");
	
	return S_OK;
}

void CGamemain::Uninit(void)
{
	Release();
}

void CGamemain::Update(void)
{
	CDebugProc::Print("シーン : ゲームメイン\n");
}

void CGamemain::Draw(void)
{

}