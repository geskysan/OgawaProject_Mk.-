//���C�g�̏���	[light.cpp]

//------------------------------------------------
//�C���N���[�h�t�@�C��
//------------------------------------------------
#include "light.h"
#include "manager.h"
#include "renderer.h"

//------------------------------------------------
//CLight�R���X�g���N�^
//------------------------------------------------
CLight::CLight()
{

}

//------------------------------------------------
//CLight�f�X�g���N�^
//------------------------------------------------
CLight::~CLight()
{

}


//------------------------------------------------
//CLight����������
//------------------------------------------------
HRESULT CLight::Init(void)
{
	SetLight();
	return S_OK;
}

//------------------------------------------------
//CLight�I������
//------------------------------------------------
void CLight::Uninit(void)
{

}
//------------------------------------------------
//CLight�X�V����
//------------------------------------------------
void CLight::Update(void)
{

}

//------------------------------------------------
//���C�g�̐ݒ�
//------------------------------------------------
void CLight::SetLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXVECTOR3 vecDir;

	//���C�g0
	{
		// D3DLIGHT9�\���̂�0�ŃN���A����
		ZeroMemory(&m_aLight[0], sizeof(D3DLIGHT9));

		// ���C�g�̃^�C�v�̐ݒ�
		m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

		// �g�U��
		m_aLight[0].Diffuse.r = 10.0f;
		m_aLight[0].Diffuse.g = 10.0f;
		m_aLight[0].Diffuse.b = 10.0f;

		// ����
		m_aLight[0].Ambient.r = 10.50f;
		m_aLight[0].Ambient.g = 10.50f;
		m_aLight[0].Ambient.b = 10.50f;

		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(0.20f, -0.60f, 0.80f);
		D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[0].Direction, &vecDir);

		// ���C�g�������_�����O�p�C�v���C���ɐݒ�
		pDevice->SetLight(0, &m_aLight[0]);

		// ���C�g�̐ݒ�
		pDevice->LightEnable(0, TRUE);
	}
	//���C�g1
	{
		// D3DLIGHT9�\���̂�0�ŃN���A����
		ZeroMemory(&m_aLight[1], sizeof(D3DLIGHT9));

		// ���C�g�̃^�C�v�̐ݒ�
		m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

		// �g�U��
		m_aLight[1].Diffuse.r = 0.25f;
		m_aLight[1].Diffuse.g = 0.25f;
		m_aLight[1].Diffuse.b = 0.25f;

		// ����
		m_aLight[1].Ambient.r = 0.20f;
		m_aLight[1].Ambient.g = 0.20f;
		m_aLight[1].Ambient.b = 0.20f;

		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(-0.20f, 1.00f, -0.50f);
		D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[1].Direction, &vecDir);

		// ���C�g�������_�����O�p�C�v���C���ɐݒ�
		pDevice->SetLight(1, &m_aLight[1]);

		// ���C�g�̐ݒ�
		pDevice->LightEnable(1, TRUE);
	}
	//���C�g2
	{
		// D3DLIGHT9�\���̂�0�ŃN���A����
		ZeroMemory(&m_aLight[2], sizeof(D3DLIGHT9));

		// ���C�g�̃^�C�v�̐ݒ�
		m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;

		// �g�U��
		m_aLight[2].Diffuse.r = 10.0f;
		m_aLight[2].Diffuse.g = 10.0f;
		m_aLight[2].Diffuse.b = 10.0f;

		// ����
		m_aLight[2].Ambient.r = 10.50f;
		m_aLight[2].Ambient.g = 10.50f;
		m_aLight[2].Ambient.b = 10.50f;

		// ���C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(-0.20f, -0.60f, -0.80f);
		D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[2].Direction, &vecDir);

		// ���C�g�������_�����O�p�C�v���C���ɐݒ�
		pDevice->SetLight(2, &m_aLight[2]);

		// ���C�g�̐ݒ�
		pDevice->LightEnable(2, TRUE);
	}
	// ���C�e�B���O���[�h
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}