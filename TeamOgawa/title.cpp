#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "fade.h"
#include "debugproc.h"

CTitle::CTitle()
{
	m_pBack = NULL;
	m_pTitle = NULL;
	m_pStart = NULL;
	m_pExit = NULL;
	m_bSelect = NULL;
	m_bTimer = NULL;
}

CTitle::~CTitle()
{

}

HRESULT CTitle::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// 背景
	{
		m_pBack = new CScene2D;
		m_pBack->Init(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
		m_pBack->LoadTexture("data/TEXTURE/sky000.jpg");
	}
	// タイトルロゴ
	{
		m_pTitle = new CScene2D;
		m_pTitle->Init(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR2(600.f, 250.f));
		m_pTitle->LoadTexture("data/TEXTURE/title.png");
	}
		return S_OK;
}

void CTitle::Uninit(void)
{
	if (m_pBack)
	{
		m_pBack->Uninit();
		m_pBack = NULL;
	}
	if (m_pTitle)
	{
		m_pTitle->Uninit();
		m_pTitle = NULL;
	}
	if (m_pStart)
	{
		m_pStart->Uninit();
		m_pStart = NULL;
	}
	if (m_pExit)
	{
		m_pExit->Uninit();
		m_pExit = NULL;
	}
	Release();
}

void CTitle::Update(void)
{
	CDebugProc::Print("シーン : タイトル\n");
}

void CTitle::Draw(void)
{

}