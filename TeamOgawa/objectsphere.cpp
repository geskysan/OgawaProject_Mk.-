#include "objectsphere.h"
#include "manager.h"
#include "renderer.h"
#include "scene3D.h"
#include "player.h"
#include "debugproc.h"

CObjectSphere::CObjectSphere()
{
	m_pVtxBuff = NULL;
	m_pTexture = NULL;
	m_pIdxBuff = NULL;
	m_pVtxBuffTop = NULL;
	m_pIdxBuffTop = NULL;
}

CObjectSphere::~CObjectSphere()
{

}

HRESULT CObjectSphere::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fLength, float fRadius, int iPolygonX, int iPolygonZ, const char *FileName)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �ʒu��ݒ�
	m_pos = pos;

	// ������ݒ�
	m_rot = rot;

	//���a�̐ݒ�
	m_fRadius = fRadius;

	//�����̐ݒ�
	m_fLength = fLength;

	//iPolygonX = 4;
	//iPolygonZ = 4;

	m_iPolygon_X = iPolygonX;
	m_iPolygon_Z = iPolygonZ;
	
	m_iIdxNum = iPolygonX*(iPolygonZ * 2) + (iPolygonZ * 4) - 2;
	m_iVertexNum = (iPolygonX + 1)*(iPolygonZ + 1);
	m_iPolygonNum = m_iIdxNum - 2;
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		FileName,
		&m_pTexture);

	//�I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_iVertexNum,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD)*m_iIdxNum,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�𐶐�
	VERTEX_3D *pVtx;

	//���_����ݒ�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int iCntV = 0; iCntV <= iPolygonZ; iCntV++)
	{
		for (int iCntH = 0; iCntH <= iPolygonX; iCntH++)
		{
			float fAngle = -D3DX_PI*2.0f*((float)iCntH / iPolygonX - 1);
			float fAngleH = (float)iCntV / (float)(iPolygonZ - 1);

			float fRadius = cosf(fAngleH) * m_fLength;

			pVtx[0].pos.x = sinf(fAngle)*fRadius;
			pVtx[0].pos.y = sinf(fAngleH)*m_fLength;
			pVtx[0].pos.z = cosf(fAngle)*fRadius;

			pVtx[0].nor = D3DXVECTOR3(1.0, 1.0f, 1.0f);
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[0].tex = D3DXVECTOR2((float)iCntH / iPolygonX, ((float)(iPolygonZ-iCntV ) / (iPolygonZ+2))+0.01f);
			pVtx++;
		}
	}
	m_pVtxBuff->Unlock();

	WORD *pIdx;
	int iX = iPolygonX + 1;
	int iNext = 1;
	int iCount = 0;

	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	for (int iCntIdx = 0; iCntIdx < m_iIdxNum; iCntIdx += 2)
	{
		if ((iX + iCount) % (iX * 2) == 0)
		{
			pIdx[iCntIdx] = pIdx[iCntIdx - 1];
			pIdx[iCntIdx + 1] = pIdx[iCntIdx] + iPolygonX + 2;
			iNext++;
			iCount = 0;
			continue;
		}
		pIdx[iCntIdx] = iNext * iX + iCount;
		pIdx[iCntIdx + 1] = pIdx[iCntIdx] - iX;
		iCount++;
	}
	m_pIdxBuff->Unlock();

	InitTop(pDevice);

	RotationMode(true, D3DXVECTOR3(0.0f, 0.0002f, 0.0f));
	return S_OK;
}

void CObjectSphere::Uninit(void)
{
	SAFE_RELESE(m_pVtxBuff);
	SAFE_RELESE(m_pTexture);
	SAFE_RELESE(m_pIdxBuff);
	SAFE_RELESE(m_pIdxBuffTop);
	SAFE_RELESE(m_pVtxBuffTop);
	Release();
}

void CObjectSphere::Update(void)
{
	CObject::Update();
}

void CObjectSphere::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

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
		m_iVertexNum,
		0,
		m_iPolygonNum);

	DrawTop(pDevice);

}

void CObjectSphere::InitTop(LPDIRECT3DDEVICE9 pDevice)
{


	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (m_iPolygon_X +1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffTop,
		NULL);

	VERTEX_3D *pVtx;

	//���_����ݒ�
	m_pVtxBuffTop->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = 0.0f;
	pVtx[0].pos.y = m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[0].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[0].tex = D3DXVECTOR2(0.5f, 0.003f);

	for (int iCntVertex = 0; iCntVertex < m_iPolygon_X ; iCntVertex++)
	{
		pVtx++;

		float fAngle = -D3DX_PI *2.0f * ((float)iCntVertex /( m_iPolygon_X));
		float fAngleH = ((float)m_iPolygon_Z /( m_iPolygon_Z - 1));

		float fRadius = cosf(fAngleH)*m_fLength;

		pVtx[0].pos.x = sinf(fAngle)*fRadius;
		pVtx[0].pos.y = sinf(fAngleH)*m_fLength;
		pVtx[0].pos.z = cosf(fAngle)*fRadius;

		pVtx[0].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.01f);
	}
	m_pVtxBuffTop->Unlock();
	pDevice->CreateIndexBuffer(sizeof(WORD)*(m_iPolygon_X + 2),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuffTop,
		NULL);
	WORD *pIdx;
	m_pIdxBuffTop->Lock(0, 0, (void**)&pIdx, 0);
	for (int iCntIdx = 0; iCntIdx <= m_iPolygon_X; iCntIdx++)
	{
		pIdx[iCntIdx] = iCntIdx;
	}
	pIdx[m_iPolygon_X + 1] = 1;
	pIdx[m_iPolygon_X + 2] = 0;

	m_pIdxBuffTop->Unlock();
}

void CObjectSphere::DrawTop(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̐ݒ�
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
		m_pVtxBuffTop,
		0,
		sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuffTop);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN,
		0,
		0,
		m_iPolygon_X + 1,
		0,
		m_iPolygon_X);
}

void CObjectSphere::SetSphere(D3DXVECTOR3 pos)
{
	m_pos.x = pos.x;
	m_pos.z = pos.z;
}
