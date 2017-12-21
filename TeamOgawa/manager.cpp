//マネージャーの処理	[manager.cpp]
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "sound.h"
#include "test.h"
#include "fade.h"
#include "input.h"
#include "light.h"
#include "camera.h"
#include "inputcheck.h"
#include "gamemain.h"
#include "title.h"

//------------------------------------------------
//マクロ定義
//------------------------------------------------

//------------------------------------------------
//静的変数
//------------------------------------------------
CManager::MODE CManager::m_mode;
CRenderer *CManager::m_pRenderer = NULL;
CCamera *CManager::m_pCamera = NULL;
CInputCheck *CManager::m_pInputCheck = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputJoypad *CManager::m_pInputJoypad = NULL;
CTitle *CManager::m_pTitle = NULL;
CGamemain *CManager::m_pGameMain = NULL;
CLight *CManager::m_pLight = NULL;
CSound *CManager::m_pSound = NULL;
#ifdef _DEBUG
CDebugProc *CManager::m_pDebugProc = NULL;
#endif // _DEBUG
//------------------------------------------------
//コンストラクタ
//------------------------------------------------
CManager::CManager()
{

}

//------------------------------------------------
//デストラクタ
//------------------------------------------------
CManager::~CManager()
{

}

//------------------------------------------------
//初期化処理
//------------------------------------------------
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//レンダリング処理の初期化処理
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	//カメラ処理の初期化処理
	m_pCamera = new CCamera;
	m_pCamera->Init();

	//キーボード操作の初期化処理
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	//ジョイパッド操作の初期化処理
	m_pInputJoypad = new CInputJoypad;
	m_pInputJoypad->Init(hInstance, hWnd);

	//ライトの初期化処理
	m_pLight = new CLight;
	m_pLight->Init();

	//サウンドの初期化処理
	m_pSound = new CSound;
	m_pSound->Init(hWnd);
	
	MODE mode;
	mode = MODE::MODE_TITLE;

#ifdef _DEBUG
	m_pDebugProc = new CDebugProc;
	m_pDebugProc->Init();
#endif // _DEBUG

	SetMode(mode);

	return S_OK;
}

//------------------------------------------------
//終了処理
//------------------------------------------------
void CManager::Uninit(void)
{
	//レンダリング処理の終了処理
	SAFE_UNINIT_DELETE(m_pRenderer);
	//カメラ処理の終了処理
	SAFE_UNINIT_DELETE(m_pCamera);
	//キーボード操作処理の終了処理
	SAFE_UNINIT_DELETE(m_pInputKeyboard);
	//ジョイパッド操作処理の終了処理
	SAFE_UNINIT_DELETE(m_pInputJoypad);
	//サウンド処理の終了処理
	SAFE_UNINIT_DELETE(m_pSound);

	//描画対象オブジェクトの破棄
	CScene::ReleaseAll();

#ifdef _DEBUG

	SAFE_UNINIT_DELETE(m_pDebugProc);

#endif //_DEBUG
}

//------------------------------------------------
//更新処理
//------------------------------------------------
void CManager::Update(void)
{
	if(m_pCamera)
	m_pCamera->Update();

	if (m_pInputJoypad)
		m_pInputJoypad->Update();

	if (m_pInputKeyboard)
		m_pInputKeyboard->Update();

	if (m_pRenderer)
	{
		m_pRenderer->Update();
	}
#ifdef _DEBUG
		
#endif // _DEBUG
}
//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	//オブジェクトの描画処理
	if (m_pRenderer)
	{
		m_pRenderer->Draw();
	}
}
void CManager::SetMode(MODE mode) {
	switch (m_mode)
	{
	case MODE_INPUTCHECK:
		if (m_pInputCheck)
		{
			m_pInputCheck->Uninit();
			m_pInputCheck = NULL;
		}
		break;
	case MODE_TITLE:
		if (m_pTitle)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;
	case MODE_GAMEMAIN:
		if (m_pGameMain)
		{
			m_pGameMain->Uninit();
			m_pGameMain = NULL;
		}
		break;
	}

	switch (mode)
	{
	case MODE_INPUTCHECK:
		m_pInputCheck = new CInputCheck();
		m_pInputCheck->Init();
		break;
	case MODE_TITLE:
		m_pTitle = new CTitle();
		m_pTitle->Init();
		break;
	case MODE_GAMEMAIN:
		m_pGameMain = new CGamemain();
		m_pGameMain->Init();
		break;
	}

	m_mode = mode;
}
CManager::MODE CManager::GetMode(void) 
{
	return m_mode;
}


