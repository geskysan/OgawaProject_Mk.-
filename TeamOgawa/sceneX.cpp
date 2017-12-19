//=============================================================================
//
// X�t�@�C���I�u�W�F�N�g�̏��� [sceneX.cpp]
// Author : 
//
//=============================================================================
#include "sceneX.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
const char *CSceneX::m_apModelName[] =
{
	"data/OBJECT3D/test.x"
};


//=============================================================================
// CSceneX����
//=============================================================================
CSceneX *CSceneX::Create(int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CSceneX *pSceneX;

	pSceneX = new CSceneX;
	pSceneX->Init(nType, pos, rot);

	return pSceneX;
}

//=============================================================================
// CSceneX�R���X�g���N�^
//=============================================================================
CSceneX::CSceneX(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_pTexture = NULL;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_nNumMat = 0;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_nType = 0;
}

//=============================================================================
// CSceneX�f�X�g���N�^
//=============================================================================
CSceneX::~CSceneX()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSceneX::Init(int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �^�C�v��ݒ�
	m_nType = nType;

	// �|���S���\���ʒu�̒��S���W��ݒ�
	m_pos = pos;

	// �|���S���̉�]�p��ݒ�
	m_rot = rot;

	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(m_apModelName[nType],
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh)))
	{
		return E_FAIL;
	}

#if 0
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FILENAME,		// �t�@�C���̖��O
		&m_pTexture);			// �ǂݍ��ރ������[
#endif

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSceneX::Uninit(void)
{
	if (m_pTexture)
	{// �e�N�X�`���̊J��
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	if (m_pBuffMat)
	{// �}�e���A���̊J��
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	if (m_pMesh)
	{// ���b�V���̊J��
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//	// �I�u�W�F�N�g�����X�g����폜
	//	CScene::UnlinkList();
	// �I�u�W�F�N�g��j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CSceneX::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CSceneX::Draw(void)
{
	/*if (!m_bUse || !m_pMesh)
		return;*/
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxScale, mtxRot, mtxTranslate;
	D3DMATERIAL9 matDef;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �g��𔽉f
	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.x, m_scale.x);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	D3DXMATERIAL *pD3DXMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{

		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture);

		// �`��
		m_pMesh->DrawSubset(nCntMat);

	}

	// �}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);
}

void CSceneX::SetTexture(const char *TextureName)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TextureName,		// �t�@�C���̖��O
		&m_pTexture);			// �ǂݍ��ރ������[

}