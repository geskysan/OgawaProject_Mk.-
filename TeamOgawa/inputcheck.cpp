#include "inputcheck.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "3Danim.h"
#include "scene2D.h"
#include "2Danim.h"

CInputCheck::CInputCheck()
{
	m_apAnim = NULL;
}

CInputCheck::~CInputCheck()
{

}

HRESULT CInputCheck::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	C3DAnim *m_ap2D = new C3DAnim;
	m_ap2D->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), true, 2, 20, 1);
	m_ap2D->LoadTexture("data/TEXTURE/explosion.png");

	return S_OK;
}

void CInputCheck::Uninit(void)
{
	Release();
}

void CInputCheck::Update(void)
{
	CInputJoypad *pJoypad = CManager::GetInputJoypad();

	CDebugProc::Print("�E�X�e�B�b�N X:%f,Y:%f\n", pJoypad->GetJoyStickR().x, pJoypad->GetJoyStickR().y);
	CDebugProc::Print("���X�e�B�b�N X:%f,Y:%f\n", pJoypad->GetJoyStickL().x, pJoypad->GetJoyStickL().y);

	if (pJoypad->GetKeyPress(CInputJoypad::KEY_CIRCLE))
	{
		CDebugProc::Print("��\n");
	}
	if (pJoypad->GetKeyPress(CInputJoypad::KEY_SQUARE))
	{
		CDebugProc::Print("��\n");
	}
	if (pJoypad->GetKeyPress(CInputJoypad::KEY_CROSS))
	{
		CDebugProc::Print("�~\n");
	}
	if (pJoypad->GetKeyPress(CInputJoypad::KEY_TRIANGLE))
	{
		CDebugProc::Print("��\n");
	}

	if (pJoypad->GetKeyPress(CInputJoypad::KEY_UP))
	{
		CDebugProc::Print("��\n");
	}
	if (pJoypad->GetKeyPress(CInputJoypad::KEY_LEFT))
	{
		CDebugProc::Print("��\n");
	}
	if (pJoypad->GetKeyPress(CInputJoypad::KEY_DOWN))
	{
		CDebugProc::Print("��\n");
	}
	if (pJoypad->GetKeyPress(CInputJoypad::KEY_RIGHT))
	{
		CDebugProc::Print("�E\n");
	}

	if (pJoypad->GetKeyPress(CInputJoypad::KEY_R1))
	{
		CDebugProc::Print("R1\n");
	}
	if (pJoypad->GetKeyPress(CInputJoypad::KEY_R2))
	{
		CDebugProc::Print("R2\n");
	}
	if (pJoypad->GetKeyPress(CInputJoypad::KEY_R3))
	{
		CDebugProc::Print("R3Push\n");
	}

	if (pJoypad->GetKeyPress(CInputJoypad::KEY_L1))
	{
		CDebugProc::Print("L1\n");
	}
	if (pJoypad->GetKeyPress(CInputJoypad::KEY_L2))
	{
		CDebugProc::Print("L2\n");
	}
	if (pJoypad->GetKeyPress(CInputJoypad::KEY_L3))
	{
		CDebugProc::Print("L3Push\n");
	}


	if (pJoypad->GetKeyPress(CInputJoypad::KEY_OPTIONS))
	{
		CDebugProc::Print("�I�v�V����\n");
	}
	if (pJoypad->GetKeyPress(CInputJoypad::KEY_PS))
	{
		CDebugProc::Print("PS\n");
	}
	if (pJoypad->GetKeyPress(CInputJoypad::KEY_SHARE))
	{
		CDebugProc::Print("Share\n");
	}
	if (pJoypad->GetKeyPress(CInputJoypad::KEY_TOUCHPAD))
	{
		CDebugProc::Print("�^�b�`�p�b�h\n");
	}

}

void CInputCheck::Draw(void)
{

}
