#include "objectblock.h"
#include "manager.h"
#include "renderer.h"
#include "scene3D.h"
#include "player.h"
#include "debugproc.h"
#include "library.h"

#define BLOCK_VERTEX	(14)
#define BLOCK_PRIM		(12)
#define BLOCK_IDX		(14)
#define NUM_VERTEX		(4)

CObjectBlock::CObjectBlock()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
}

CObjectBlock::~CObjectBlock()
{

}

HRESULT CObjectBlock::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Width, float Heigth,float Depth)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CObject::Init();
	// �ʒu��ݒ�
	m_pos = pos;

	// ������ݒ�
	m_rot = rot;

	//�����̐ݒ�
	m_fWidth = Width;

	//�c���̐ݒ�
	m_fHeigth = Heigth;

	//���s���̐ݒ�
	m_fDepth = Depth;

	float fAngle = SetAngle(m_fWidth, m_fDepth);
	float fLength = SetLength(m_fWidth, m_fDepth);


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/blocktest.jpg",	// �t�@�C���̖��O
		&m_pTexture);				// �ǂݍ��ރ������[

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * BLOCK_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuff,				// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}
	
	if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * BLOCK_IDX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL)))
	{
		return E_FAIL;
	}


	VERTEX_3D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���ʕ���
	for (int iCntVertex = 0; iCntVertex < 2; iCntVertex++)
	{
		pVtx[0].pos = D3DXVECTOR3(-sinf(fAngle)*fLength, -m_fHeigth *iCntVertex, cosf(fAngle)*fLength);
		pVtx[1].pos = D3DXVECTOR3(sinf(fAngle)*fLength, -m_fHeigth*iCntVertex, cosf(fAngle)*fLength);
		pVtx[2].pos = D3DXVECTOR3(-sinf(fAngle)*fLength, -m_fHeigth*iCntVertex, -cosf(fAngle)*fLength);
		pVtx[3].pos = D3DXVECTOR3(sinf(fAngle)*fLength, -m_fHeigth*iCntVertex, -cosf(fAngle)*fLength);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		float fTex = iCntVertex * 0.1f;
		pVtx[0].tex = D3DXVECTOR2(0.01f, iCntVertex);
		pVtx[1].tex = D3DXVECTOR2(0.49 / 3, iCntVertex);
		pVtx[2].tex = D3DXVECTOR2(0.49f/3 + 0.49/3, iCntVertex);
		pVtx[3].tex = D3DXVECTOR2(0.49f, iCntVertex);

		pVtx += 4;
	}
	//��ʕ���
		pVtx[0].pos = D3DXVECTOR3(-sinf(fAngle)*fLength, 0.0f, cosf(fAngle)*fLength);
		pVtx[1].pos = D3DXVECTOR3(sinf(fAngle)*fLength, 0.0f, cosf(fAngle)*fLength);
		pVtx[2].pos = D3DXVECTOR3(-sinf(fAngle)*fLength,0.0f, -cosf(fAngle)*fLength);
		pVtx[3].pos = D3DXVECTOR3(sinf(fAngle)*fLength, 0.0f, -cosf(fAngle)*fLength);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);


	m_pVtxBuff->Unlock();

	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	pIdx[0] = 6;
	pIdx[1] = 2;
	pIdx[2] = 7;
	pIdx[3] = 3;
	
	pIdx[4] = 5;
	pIdx[5] = 1;
	pIdx[6] = 4;
	pIdx[7] = 0;
	
	pIdx[8] = 6;
	pIdx[9] = 2;
	
	pIdx[10] = 10;
	pIdx[11] = 8;
	pIdx[12] = 11;
	pIdx[13] = 9;
	m_pIdxBuff->Unlock();
	return S_OK;
}

void CObjectBlock::Uninit(void)
{
	SAFE_RELESE(m_pVtxBuff);
	SAFE_RELESE(m_pTexture);
	SAFE_RELESE(m_pIdxBuff);
	CObject::Uninit();
}

void CObjectBlock::Update(void)
{
	m_BBMin = m_pos + D3DXVECTOR3(-m_fWidth/2, -m_fHeigth,-m_fDepth/2);
	m_BBMax = m_pos + D3DXVECTOR3(m_fWidth/2, 0.0f, m_fDepth/2);
	CObject::Update();
}

void CObjectBlock::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot,mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		BLOCK_VERTEX,
		0,
		BLOCK_PRIM);
}