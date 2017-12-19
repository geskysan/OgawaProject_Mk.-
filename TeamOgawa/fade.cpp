//=============================================================================
//
// フェードの処理 [fade.cpp]
// Author : 
//
//=============================================================================
#include "fade.h"
#include "manager.h"
#include "renderer.h"
//#include "input.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的変数
//*****************************************************************************

//=============================================================================
// 生成
//=============================================================================
CFade *CFade::Create(void)
{
	CFade *pFade;

	pFade = new CFade;
	pFade->Init();
	pFade->SetObjType(CScene::OBJTYPE_FADE);

	return pFade;
}

//=============================================================================
// CFadeコンストラクタ
//=============================================================================
CFade::CFade(int nPri) : CScene2D(nPri)
{
	m_bFade = false;
	m_nTimer = 0;
	m_fValueAlpha = 0.0f;
	m_status = STATUS_NONE;
}

//=============================================================================
// CFadeデストラクタ
//=============================================================================
CFade::~CFade()
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CFade::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CScene2D::Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXVECTOR2(0,0));

	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	CScene2D::SetVertexCol(m_color);
	CScene2D::SetVertexPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	m_bFade = false;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CFade::Uninit(void)
{
	// Scene2Dの開放
	CScene2D::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CFade::Update(void)
{
	if (m_bFade)
	{
		// アルファ値設定
		m_color.a += m_fValueAlpha;
		if (m_color.a > 1.0f) m_color.a = 1.0f;
		if (m_color.a < 0.0f) m_color.a = 0.0f;
		CScene2D::SetVertexCol(m_color);

		m_nTimer--;
		if (m_nTimer <= 0)
		{
			if (m_status == STATUS_FADEOUT)
			{// フェードアウト終了
				m_status = STATUS_FADEOUT_END;
				CManager::SetMode(m_modeNext);
			}
			else if (m_status == STATUS_FADEIN)
			{// フェードイン終了
				m_bFade = false;
				m_status = STATUS_FADEIN_END;
			}
		}
	}
}

//=============================================================================
// 描画
//=============================================================================
void CFade::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

	CScene2D::Draw();

	//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
}

//=============================================================================
// 描画
//=============================================================================
void CFade::Start(STATUS status, int nTimer, CManager::MODE modeNext)
{
	if (status == STATUS_FADEOUT)
	{
		m_fValueAlpha = (1.0f / nTimer);
	}
	else
	{
		m_fValueAlpha = -(1.0f / nTimer);
	}

	m_bFade = true;
	m_nTimer = nTimer;
	m_status = status;
	m_modeNext = modeNext;
}
