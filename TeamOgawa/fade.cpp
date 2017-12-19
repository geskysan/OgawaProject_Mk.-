//=============================================================================
//
// �t�F�[�h�̏��� [fade.cpp]
// Author : 
//
//=============================================================================
#include "fade.h"
#include "manager.h"
#include "renderer.h"
//#include "input.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************

//=============================================================================
// ����
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
// CFade�R���X�g���N�^
//=============================================================================
CFade::CFade(int nPri) : CScene2D(nPri)
{
	m_bFade = false;
	m_nTimer = 0;
	m_fValueAlpha = 0.0f;
	m_status = STATUS_NONE;
}

//=============================================================================
// CFade�f�X�g���N�^
//=============================================================================
CFade::~CFade()
{
}

//=============================================================================
// ������
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
// �I������
//=============================================================================
void CFade::Uninit(void)
{
	// Scene2D�̊J��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CFade::Update(void)
{
	if (m_bFade)
	{
		// �A���t�@�l�ݒ�
		m_color.a += m_fValueAlpha;
		if (m_color.a > 1.0f) m_color.a = 1.0f;
		if (m_color.a < 0.0f) m_color.a = 0.0f;
		CScene2D::SetVertexCol(m_color);

		m_nTimer--;
		if (m_nTimer <= 0)
		{
			if (m_status == STATUS_FADEOUT)
			{// �t�F�[�h�A�E�g�I��
				m_status = STATUS_FADEOUT_END;
				CManager::SetMode(m_modeNext);
			}
			else if (m_status == STATUS_FADEIN)
			{// �t�F�[�h�C���I��
				m_bFade = false;
				m_status = STATUS_FADEIN_END;
			}
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void CFade::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

	CScene2D::Draw();

	//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
}

//=============================================================================
// �`��
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
