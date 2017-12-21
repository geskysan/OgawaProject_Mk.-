//�}�l�[�W���[�̏���	[manager.cpp]
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

//------------------------------------------------
//�}�N����`
//------------------------------------------------

//------------------------------------------------
//�ÓI�ϐ�
//------------------------------------------------
CManager::MODE CManager::m_mode;
CRenderer *CManager::m_pRenderer = NULL;
CCamera *CManager::m_pCamera = NULL;
CInputCheck *CManager::m_pInputCheck = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputJoypad *CManager::m_pInputJoypad = NULL;
#ifdef _DEBUG
CDebugProc *CManager::m_pDebugProc = NULL;
#endif // _DEBUG
//------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------
CManager::CManager()
{

}

//------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------
CManager::~CManager()
{

}

//------------------------------------------------
//����������
//------------------------------------------------
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//�����_�����O�����̏���������
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	//�J���������̏���������
	m_pCamera = new CCamera;
	m_pCamera->Init();

	//�L�[�{�[�h����̏���������
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	//�W���C�p�b�h����̏���������
	m_pInputJoypad = new CInputJoypad;
	m_pInputJoypad->Init(hInstance, hWnd);

	MODE mode;
	mode = MODE::MODE_INPUTCHECK;

#ifdef _DEBUG
	m_pDebugProc = new CDebugProc;
	m_pDebugProc->Init();
#endif // _DEBUG

	SetMode(mode);

	return S_OK;
}

//------------------------------------------------
//�I������
//------------------------------------------------
void CManager::Uninit(void)
{
	//�����_�����O�����̏I������
	SAFE_UNINIT_DELETE(m_pRenderer);
	//�J���������̏I������
	SAFE_UNINIT_DELETE(m_pCamera);
	//�L�[�{�[�h���쏈���̏I������
	SAFE_UNINIT_DELETE(m_pInputKeyboard);
	//�W���C�p�b�h���쏈���̏I������
	SAFE_UNINIT_DELETE(m_pInputJoypad);

	//�`��ΏۃI�u�W�F�N�g�̔j��
	CScene::ReleaseAll();

#ifdef _DEBUG

	SAFE_UNINIT_DELETE(m_pDebugProc);

#endif //_DEBUG
}

//------------------------------------------------
//�X�V����
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
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	//�I�u�W�F�N�g�̕`�揈��
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
	}

	switch (mode)
	{
	case MODE_INPUTCHECK:
		m_pInputCheck = new CInputCheck();
		m_pInputCheck->Init();
		break;
	}

	m_mode = mode;
}
CManager::MODE CManager::GetMode(void) 
{
	return m_mode;
}


