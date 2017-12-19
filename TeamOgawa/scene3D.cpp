//=============================================================================
//
// 3D�I�u�W�F�N�g�̏��� [scene3D.cpp]
// Author : 
//
//=============================================================================
#include "scene3D.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_WIDTH	(100)	// �e�N�X�`���̕�
#define TEXTURE_HEIGHT	(100)	// �e�N�X�`���̍���

#define	NUM_VERTEX		(4)		// ���_��
#define	NUM_POLYGON		(2)		// �|���S����

//*****************************************************************************
// �\���̒�`
//*****************************************************************************


//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
const char *CScene3D::m_apTextureName[] =
{
	"",
};

//=============================================================================
// CScene3D����
//=============================================================================
CScene3D *CScene3D::Create(int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int iWidth, int iHeight)
{
	CScene3D *pScene3D;

	pScene3D = new CScene3D;
	pScene3D->Init(nType, pos, rot, iWidth, iHeight);

	return pScene3D;
}

//=============================================================================
// CScene3D�R���X�g���N�^
//=============================================================================
CScene3D::CScene3D(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
}

//=============================================================================
// CScene3D�f�X�g���N�^
//=============================================================================
CScene3D::~CScene3D()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScene3D::Init(int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int iWidth = 100, int iHeight = 100)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// �^�C�v��ݒ�
	m_nType = nType;

	// �ʒu��ݒ�
	m_pos = pos;

	// ������ݒ�
	m_rot = rot;

	// �傫����ݒ�
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//�`��̐ݒ�
	m_bEnable = true;

	// �Ίp���̒����E�p�x��ݒ�
	m_fLength = sqrtf((float)(((iWidth / 2.f) * (iWidth / 2.f)) + ((iHeight / 2.f) * (iHeight / 2.f))));
	m_fAngle = atan2f((iWidth / 2.f), (iHeight / 2.f));

	// �e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
	//	m_apTextureName[nType],		// �t�@�C���̖��O
	//	&m_pTexture);				// �ǂݍ��ރ������[

									// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuff,				// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�q
		pVtx[0].pos.x = -sinf(m_fAngle) * m_fLength;
		pVtx[0].pos.y = cosf(m_fAngle) * m_fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = sinf(m_fAngle) * m_fLength;
		pVtx[1].pos.y = cosf(m_fAngle) * m_fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = -sinf(m_fAngle) * m_fLength;
		pVtx[2].pos.y = -cosf(m_fAngle) * m_fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = sinf(m_fAngle) * m_fLength;
		pVtx[3].pos.y = -cosf(m_fAngle) * m_fLength;
		pVtx[3].pos.z = 0.0f;

		// �@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		m_pVtxBuff->Unlock();
	}

	
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScene3D::Uninit(void)
{
	// �e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//	// �I�u�W�F�N�g�����X�g����폜
	//	CScene::UnlinkList();
	// �I�u�W�F�N�g��j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene3D::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene3D::Draw(void)
{
	if (!m_bEnable)
		return;

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxScale, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	
	// �g�k�𔽉f
	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

void CScene3D::LoadTexture(const char *TextureName)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// �^�C�v��ݒ�

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TextureName,		// �t�@�C���̖��O
		&m_pTexture);				// �ǂݍ��ރ������[

}

void CScene3D::SetVertexPos(D3DXVECTOR3 RightUp, D3DXVECTOR3 RightDown, D3DXVECTOR3 LeftUp, D3DXVECTOR3 LeftDown)
{
	VERTEX_3D *pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	pVtx[0].pos = RightUp;
	pVtx[1].pos = LeftUp;
	pVtx[2].pos = RightDown;
	pVtx[3].pos = LeftDown;

	pVtx[0].pos = LeftUp;
	pVtx[1].pos = RightUp;
	pVtx[2].pos = LeftDown;
	pVtx[3].pos = RightDown;

	m_pVtxBuff->Unlock();

}

