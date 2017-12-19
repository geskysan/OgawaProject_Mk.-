//2D�I�u�W�F�N�g�̏���	[scene2D.cpp]
#include "scene2D.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"

//------------------------------------------------
//�}�N����`
//------------------------------------------------
#define	NUM_VERTEX			(4)		// ���_��
#define	NUM_POLYGON			(2)		// �|���S����

//------------------------------------------------
//CScene2D����
//------------------------------------------------
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR2 polygonSize)
{
	CScene2D *pScene2D;

	pScene2D = new CScene2D;
	pScene2D->Init( pos, rot, polygonSize);

	return pScene2D;
}

//------------------------------------------------
//CScene2D�R���X�g���N�^
//------------------------------------------------
CScene2D::CScene2D(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;

}

//------------------------------------------------
//CScene2D�f�X�g���N�^
//------------------------------------------------
CScene2D::~CScene2D()
{
}

//------------------------------------------------
//����������
//------------------------------------------------
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR2 polygonSize)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �|���S���\���ʒu�̒��S���W��ݒ�
	m_pos = pos;
	m_bEnable = true;
	// �|���S���̉�]�p��ݒ�
	m_rot = rot;
	m_posTex = D3DXVECTOR2(0.f, 0.f);
	m_fLength = SetLength(polygonSize.x, polygonSize.y);
	m_fAngle = SetAngle(polygonSize.x, polygonSize.y);

									// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuff,				// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

																	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g�厞�̕�Ԑݒ�
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k�����̕�Ԑݒ�
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���t�l�̌J��Ԃ��ݒ�
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���u�l�̌J��Ԃ��ݒ�

																		// �e�N�X�`���X�e�[�W�X�e�[�g�p�����[�^�̐ݒ�
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = m_pos.x - sinf(m_fAngle - m_rot.z) * m_fLength;
		pVtx[0].pos.y = m_pos.y - cosf(m_fAngle - m_rot.z) * m_fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = m_pos.x + sinf(m_fAngle + m_rot.z) * m_fLength;
		pVtx[1].pos.y = m_pos.y - cosf(m_fAngle + m_rot.z) * m_fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = m_pos.x - sinf(m_fAngle + m_rot.z) * m_fLength;
		pVtx[2].pos.y = m_pos.y + cosf(m_fAngle + m_rot.z) * m_fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = m_pos.x + sinf(m_fAngle - m_rot.z) * m_fLength;
		pVtx[3].pos.y = m_pos.y + cosf(m_fAngle - m_rot.z) * m_fLength;
		pVtx[3].pos.z = 0.0f;

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

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

//------------------------------------------------
//�I������
//------------------------------------------------
void CScene2D::Uninit(void)
{
	// �e�N�X�`���̊J��
	if (m_pTexture)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//	// �I�u�W�F�N�g�����X�g����폜
	//	CScene::UnlinkList();
	// �I�u�W�F�N�g��j��
	Release();
}

//------------------------------------------------
//�X�V����
//------------------------------------------------
void CScene2D::Update(void)
{

}

//------------------------------------------------
//�`�揈��
//------------------------------------------------
void CScene2D::Draw(void)
{

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	if (m_bEnable)
	{
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}
//------------------------------------------------
//���_�̐ݒ�
//------------------------------------------------
void CScene2D::SetVertexPos(void)
{
	VERTEX_2D *pVtx;

	// ���_�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_pos.x - sinf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[0].pos.y = m_pos.y - cosf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[1].pos.y = m_pos.y - cosf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x - sinf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	// ���_���A�����b�N
	m_pVtxBuff->Unlock();
}

//------------------------------------------------
//�摜�̓ǂݍ���
//------------------------------------------------
void CScene2D::LoadTexture(const char *pTextureName) {
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (!m_pTexture)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
			pTextureName,		// �t�@�C���̖��O
			&m_pTexture);		// �ǂݍ��ރ������[
	}

}

//------------------------------------------------
//���_���W�̐ݒ�
//------------------------------------------------
void CScene2D::SetVertexPos(D3DXVECTOR3 vtx0, D3DXVECTOR3 vtx1, D3DXVECTOR3 vtx2, D3DXVECTOR3 vtx3)
{
	VERTEX_2D *pVtx;

	// ���_�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = m_pos + vtx0;
	pVtx[1].pos = m_pos + vtx1;
	pVtx[2].pos = m_pos + vtx2;
	pVtx[3].pos = m_pos + vtx3;

	// ���_���A�����b�N
	m_pVtxBuff->Unlock();
}

//------------------------------------------------
//���_�J���[�̐ݒ�
//------------------------------------------------
void CScene2D::SetVertexCol(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;

	// ���_�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = col;

	// ���_���A�����b�N
	m_pVtxBuff->Unlock();
}

//------------------------------------------------
//�e�N�X�`�����W�̐ݒ�
//------------------------------------------------
void CScene2D::SetVertexTex(void)
{
	VERTEX_2D *pVtx;

	// ���_�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(m_posTex.x, m_posTex.y);
	pVtx[1].tex = D3DXVECTOR2(m_posTex.x + 1.0f, m_posTex.y);
	pVtx[2].tex = D3DXVECTOR2(m_posTex.x, m_posTex.y + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_posTex.x + 1.0f, m_posTex.y + 1.0f);

	// ���_���A�����b�N
	m_pVtxBuff->Unlock();
}

//------------------------------------------------
//�e�N�X�`�����W�̐ݒ�
//------------------------------------------------
void CScene2D::SetVertexTex(D3DXVECTOR2 tex0, D3DXVECTOR2 tex1, D3DXVECTOR2 tex2, D3DXVECTOR2 tex3)
{
	VERTEX_2D *pVtx;

	// ���_�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = tex0;
	pVtx[1].tex = tex1;
	pVtx[2].tex = tex2;
	pVtx[3].tex = tex3;

	// ���_���A�����b�N
	m_pVtxBuff->Unlock();
}

//------------------------------------------------
//�Ίp���̌X���̐ݒ�
//------------------------------------------------
void CScene2D::SetLengthPos(float fLength)
{
	m_fLength = fLength;
	VERTEX_2D *pVtx;

	// ���_�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].pos.x = m_pos.x - sinf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[0].pos.y = m_pos.y - cosf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[1].pos.y = m_pos.y - cosf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x - sinf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	// ���_���A�����b�N
	m_pVtxBuff->Unlock();


}

//------------------------------------------------
//�ʒu���W�̐ݒ�
//------------------------------------------------
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{

	VERTEX_2D *pVtx;
	// ���_�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	pVtx[0].pos += m_pos - pos;
	pVtx[1].pos += m_pos - pos;
	pVtx[2].pos += m_pos - pos;
	pVtx[3].pos += m_pos - pos;

	// ���_���A�����b�N
	m_pVtxBuff->Unlock();
	m_pos = pos;

}
